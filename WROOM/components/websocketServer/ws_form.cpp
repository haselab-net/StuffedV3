#include "ws_form.h"
#include "ws_http.h"
#include <ctype.h>
#include <fstream>
#include <string>
#include <logging.h>
#include <GeneralUtils.h>
#include <espfsStream.h>

LOG_TAG("SRForm");

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
//	SRReplace
//
void SRReplace::handle(HttpRequest& request, HttpResponse& response, std::vector<Replace>& replaces){
	std::vector<Replace> filenameReplaces;
	handle(request, response, replaces, filenameReplaces);
}
void SRReplace::handle(HttpRequest& request, HttpResponse& response, std::vector<Replace>& replaces, std::vector<Replace>& filenameReplaces){
	LOGI("Receive a request on wifi. Free heap: %i\n", esp_get_free_heap_size());

	// do not respond when heap is not enough
	uint32_t remainingHeapSize = esp_get_free_heap_size();
	if (remainingHeapSize < 25000) {
		LOGE("Free heap size is lower than 25000");
		response.setStatus(429, "Too many requests");
		response.addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
		response.sendData("	\
			Free heap size is lower than 20000 \n \
			Try this: \n \
			1. Wait for a while and refresh page again. Then wait for response. \n \
			2. If your Nuibot is running in synchronization mode or offline mode, switch to development mode.");
		response.close();
		return;
	}

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
	for(Replace& fr: filenameReplaces){
		for(std::string::size_type pos = fileName.find(fr.from, 0); pos != std::string::npos; pos = fileName.find(fr.from, pos)){
			fileName.replace(pos, fr.from.length(), fr.to);
			pos += fr.to.length();
		}
	}
	//	accept laguage check
	std::string lang = request.getHeader("accept-language");
	int spos = fileName.rfind("/");
	int ppos = fileName.rfind(".");
	if (ppos == std::string::npos || (spos != std::string::npos && ppos < spos)){
		ppos = fileName.length();
	}
	std::string fileNameLang;
	std::istream* iStream = NULL;
	int start = 0;
	for(int i=0; i<lang.length(); ++i){
		if (lang[i] == ';'){
			for(;i<lang.length() && lang[i] != ','; ++i);
			++i;
			start = i;
		}
		if (lang[i] == ','){
			fileNameLang = fileName;
			fileNameLang.insert(ppos, ".");
			fileNameLang.insert(ppos+1, lang, start, i);
			ESP_LOGD(tag, "Try to open file name with language %s", fileNameLang.c_str());
			iStream = espfsIstream(fileNameLang.c_str());
			break;
		}
	}
	if (!iStream){
		fileNameLang = fileName;
		iStream = espfsIstream(fileNameLang.c_str());
	}
	ESP_LOGD(tag, "hanlder(): Opening file: %s", fileNameLang.c_str());

	// If we failed to open the requested file, then it probably didn't exist so return a not found.
	if (!iStream) {
		LOGE("Unable to open file %s for reading", fileNameLang.c_str());
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
	// std::string repeat; //REVIEW seems not used
	int inParen = 0;
	int nRepeat = -1;
	int repeatCount = 0;
	/*	The grammer
		$key $(key) are replaced based on replaces.
		$num[text$] will repeat $num times. $num must be replaced into number.
	*/
	while (!iStream->eof()) {
		iStream->read((char*) pData, pHttpServer->getFileBufferSize());
		int dataLen = iStream->gcount();
		int sentPos = 0;
		for(int pos=0; pos != dataLen; pos++){
			if (keyLen >= 0){
				if (isalnum(pData[pos]) || pData[pos] == '_'){
					key[keyLen] = pData[pos];
					keyLen++;
				}else if (keyLen == 0 && pData[pos] == '$'){	//	$$ = $
					response.sendData((uint8_t*) "$", 1);
				}else if (pData[pos] == '[' || pData[pos] == '?'){	//	repeat or if start
					bool bIf = false;
					if (pData[pos] == '?') bIf = true;
					key[keyLen] = 0;
					repeatCount = 0;
					for(Replace& r : replaces){
						if (r.from.compare(key) == 0){
							//ESP_LOGD(tag, "Repeat: %s -> %s", r.from.c_str(), r.to.c_str());
							nRepeat = -1;
							if (isdigit(r.to.c_str()[0])){
								nRepeat = atoi(r.to.c_str());
							}
							if (bIf){
								if (nRepeat > 0) nRepeat = 1;
								if (nRepeat < 0){
									if (r.to.length()) nRepeat = 1;
									else nRepeat = 0;
								}
							}
							if (nRepeat >= 0) goto foundNum;
						}
					}
					if (bIf){
						nRepeat = 0;
						goto foundNum;
					}
					LOGE("Repeat count must be set.");
					foundNum:
					//ESP_LOGD(tag, "SRReplace: Repeat %d.", nRepeat);
					//	Shift buffer and read from file;
					dataLen -= pos + (bIf ? 2 : 1);
					if (dataLen > 0){
						memmove(pData, pData + pos+(bIf ? 2 : 1), dataLen);
					}
					pos = 0;
					sentPos = 0;
					if (!iStream->eof()){
						iStream->read((char*) pData + dataLen, pHttpServer->getFileBufferSize() - dataLen);
						dataLen += iStream->gcount();
					}
					keyLen = -1;
					if (nRepeat == 0){	//	skip to $]
						for(;pos < dataLen-1; ++pos){
							if (pData[pos] == '$' && pData[pos+1] == ']'){
								nRepeat = -1;
								pos +=2;
								sentPos = pos;
								break;
							}
						}
						if (nRepeat == 0){
							LOGE("Can not find corresponding '$]'");
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
							LOGE("SRReplace: parentheses error in %s.", key);
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
							//ESP_LOGD(tag, "SRReplace: key='%s' is replaced to %s.", r.from.c_str(), r.to.c_str());
							goto foundKey;
						}
					}
					//	not found
					LOGE("SRReplace: Undefined key='%s' is used in %s.", key, fileNameLang.c_str());
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
			LOGE("Corresponding '$]' is needed.");
		}
		if (keyLen == -1){
			response.sendData(pData + sentPos, dataLen-sentPos);
		}
	}
	delete[] pData;
	delete iStream;
	response.close();
}
