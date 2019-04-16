#include "ws_form.h"
#include "ws_http.h"
#include <ctype.h>
#include <fstream>
#include <logging.h>
#include <GeneralUtils.h>

static char tag[] = "ws";

SRRequestHandler SRRequestHandler::theRequestHandler;
static void handlerStatic(HttpRequest* pRequest, HttpResponse* pResponse){
    for(SRFormBase* form : SRRequestHandler::theRequestHandler.forms){
        if (form->method == pRequest->getMethod() && std::regex_match(pRequest->getPath(), form->path)){
            form->handler(*pRequest, *pResponse);
        }
    }
}
void SRRequestHandler::Register(HttpServer* s){
    for(SRFormBase* form : theRequestHandler.forms){
        s->addPathHandler(form->method, &form->path, handlerStatic);
    }
}

void SRFormReplace::handler(HttpRequest& request, HttpResponse& response){
    // Serve up the content from the file on the file system ... if found ...
    std::string fileName = pHttpServer->getRootPath() + request.getPath(); // Build the absolute file name to read.
    // If the file name ends with a '/' then remove it ... we are normalizing to NO trailing slashes.
    if (GeneralUtils::endsWith(fileName, '/')) {
        fileName = fileName.substr(0, fileName.length() - 1);
    }
    //	In case a server address without path is requested, append /index.html
    if (request.getPath().length() == 1 && request.getPath().back() == '/'){
        fileName.append("/index.html");
    }

	ESP_LOGI(tag, "Opening file: %s", fileName.c_str());
	std::ifstream ifStream;
	ifStream.open(fileName, std::ifstream::in | std::ifstream::binary);      // Attempt to open the file for reading.

	// If we failed to open the requested file, then it probably didn't exist so return a not found.
	if (!ifStream.is_open()) {
		ESP_LOGE(tag, "Unable to open file %s for reading", fileName.c_str());
		response.setStatus(HttpResponse::HTTP_STATUS_NOT_FOUND, "Not Found");
		response.addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
		response.sendData("Not Found");
		response.close();
		return; // Since we failed to open the file, no further work to be done.
	}

	// We now have an open file and want to push the content of that file through to the browser.
	// because of defect #252 we have to do some pretty important re-work here.  Specifically, we can't host the whole file in
	// RAM at one time.  Instead what we have to do is ensure that we only have enough data in RAM to be sent.

	response.setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
	uint8_t *pData = new uint8_t[pHttpServer->getFileBufferSize()];
	int keyLen = -1;
	char key[64];	//	keyword
	int inParen = 0;
	while (!ifStream.eof()) {
		ifStream.read((char*) pData, pHttpServer->getFileBufferSize());
		int sentPos = 0;
		for(int pos=0; pos != ifStream.gcount(); pos++){
			if (keyLen >= 0){
				if (isalnum(pData[pos]) || pData[pos] == '_'){
					key[keyLen] = pData[pos];
					keyLen++;
				}else if (keyLen == 0 && pData[pos] == '$'){	//	$$ = $
					response.sendData((uint8_t*) "$", 1);
				}else if (pData[pos] == '('){
					inParen ++;
				}else{
					if (inParen && pData[pos] == ')'){	
						pos ++;						//skip and stop;
					}
					//	replace key
					for(Replace& r: replaces){
						if (r.from.compare(0, std::string::npos, key, keyLen) == 0){
							response.sendData((uint8_t*) r.to.c_str(), r.to.length());
							goto found;
						}
					}
					//	not found
					key[keyLen] = '\0';
					ESP_LOGE(tag, "SRFormReplace: Undefined key='%s' is used in %s.", key, fileName.c_str());	
				found:
					keyLen = -1;
					sentPos = pos;
				}
			}else if (pData[pos] == '$'){
				keyLen = 0;
				response.sendData(pData + sentPos, pos-1);
			}
		}
		if (keyLen == -1){
			response.sendData(pData + sentPos, ifStream.gcount());
		}
	}
	delete[] pData;
	ifStream.close();
	response.close();
}
