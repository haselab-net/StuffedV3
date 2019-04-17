#include "ws_form.h"
#include "ws_http.h"
#include <ctype.h>
#include <fstream>
#include <string>
#include <logging.h>
#include <GeneralUtils.h>

static char tag[] = "ws_form";

//-------------------------------------------------------------------
//	SRFormHandeler
//
SRFormHandler SRFormHandler::theFormHandler;
std::vector<SRFormBase*> SRFormHandler::forms;

static void handlerStatic(HttpRequest* pRequest, HttpResponse* pResponse){
    for(SRFormBase* form : SRFormHandler::theFormHandler.forms){
        if ( (form->method==NULL || pRequest->getMethod().compare(form->method) == 0) 
			&& pRequest->getPath().compare(form->path) == 0 ){
            form->handler(*pRequest, *pResponse);
        }
    }
}
void SRFormHandler::registerToServer(HttpServer* s){
	//ESP_LOGD(tag, "SRFormHandler::registerToServer");
    for(SRFormBase* form : theFormHandler.forms){
		if (form->method){
	        s->addPathHandler(form->method, form->path, handlerStatic);
		}else{
	        s->addPathHandler("GET", form->path, handlerStatic);
	        s->addPathHandler("POST", form->path, handlerStatic);
		}
		//ESP_LOGD(tag, "Add form: method:%s, path:%s", form->method, form->path);
    }
}
void SRFormHandler::addForm(SRFormBase* f){
	forms.push_back(f);
}

SRFormHandler::SRFormHandler(){
}

//-------------------------------------------------------------------
//	SRFormReplace
//
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

	ESP_LOGI(tag, "hanlder(): Opening file: %s", fileName.c_str());
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
	std::string repeat;
	int inParen = 0;
	int nRepeat = -1;
	int repeatCount = 0;
	/*	The grammer
		$key $(key) are replaced based on replaces.
		$num[text$] will repeat $num times. $num must be replaced into number.		
	*/
	while (!ifStream.eof()) {
		ifStream.read((char*) pData, pHttpServer->getFileBufferSize());
		int dataLen = ifStream.gcount();
		int sentPos = 0;
		for(int pos=0; pos != dataLen; pos++){
			if (keyLen >= 0){
				if (isalnum(pData[pos]) || pData[pos] == '_'){
					key[keyLen] = pData[pos];
					keyLen++;
				}else if (keyLen == 0 && pData[pos] == '$'){	//	$$ = $
					response.sendData((uint8_t*) "$", 1);
				}else if (pData[pos] == '['){	//	repeat start
					key[keyLen] = 0;
					repeatCount = 0;
					for(Replace& r : replaces){
						if (r.from.compare(key) == 0){
							//ESP_LOGD(tag, "Repeat: %s -> %s", r.from.c_str(), r.to.c_str());
							nRepeat = atoi(r.to.c_str());
							if (nRepeat >= 0) goto foundNum;
						}
					}
					ESP_LOGE(tag, "Repeat count must be set.");
					foundNum:
					//ESP_LOGD(tag, "SRFormReplace: Repeat %d.", nRepeat);
					//	Shift buffer and read from file;
					dataLen -= pos+1;
					memmove(pData, pData + pos+1, dataLen);
					pos = 0;
					sentPos = 0;
					if (!ifStream.eof()){
						ifStream.read((char*) pData + dataLen, pHttpServer->getFileBufferSize() - dataLen);
						dataLen += ifStream.gcount();
					}
					keyLen = -1;
					if (nRepeat == 0){	//	skip to $]
						for(;pos < dataLen-1; ++pos){
							if (pData[pos] == '$' && pData[pos+1] == ']'){
								nRepeat = -1;
								pos ++;
								break;
							}
						}
						if (nRepeat == 0){
							ESP_LOGE(tag, "Can not find corresponding '$]'");
							nRepeat = -1;
						}
					}
				}else if (pData[pos] == ']'){	//	repeat close
					keyLen = -1;
					if (repeatCount < nRepeat-1){	//	repeat
						pos = sentPos = 0;
						repeatCount ++;
					}else{						//	end
						nRepeat = -1;
						repeatCount = 0;
						sentPos = pos+1;
					}
				}else if (pData[pos] == '('){
					inParen++;
				}else{
					key[keyLen] = '\0';
					//ESP_LOGD(tag, "Got key:%s.", key);
					if (inParen && pData[pos] == ')'){	
						inParen--;
						if (inParen < 0){
							inParen = 0;
							ESP_LOGE(tag, "SRFormReplace: parentheses error in %s.", key);
						}
						pos ++;						//skip and stop;
					}else if (nRepeat > 0 && pData[pos] == '*'){	//	add repeatCount to key
						sprintf(key+strlen(key), "%d", repeatCount);
						//ESP_LOGD(tag, "repeatCount added. key:%s.", key);
						pos ++;
					}
					//	replace key
					for(Replace& r: replaces){
						if (r.from.compare(key) == 0){
							response.sendData((uint8_t*) r.to.c_str(), r.to.length());
							//ESP_LOGD(tag, "SRFormReplace: key='%s' is replaced to %s.", r.from.c_str(), r.to.c_str());	
							goto foundKey;
						}
					}
					//	not found
					ESP_LOGE(tag, "SRFormReplace: Undefined key='%s' is used in %s.", key, fileName.c_str());	
				foundKey:
					keyLen = -1;
					sentPos = pos;
				}
			}else{	//	not in key
				if (pData[pos] == '$'){
					keyLen = 0;
					response.sendData(pData + sentPos, pos-sentPos);
				}
			}
		}	//	for dataLen
		if (nRepeat != -1){
			ESP_LOGE(tag, "Corresponding '$]' is needed.");
		}
		if (keyLen == -1){
			response.sendData(pData + sentPos, dataLen);
		}
	}
	delete[] pData;
	ifStream.close();
	response.close();
}
