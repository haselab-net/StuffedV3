#pragma once
#include "HttpServer.h"
#include "HttpResponse.h"

class SRFormBase{
public:
	std::regex path;
	const char* type;
};

class SRRequestHandler {
	SRRequestHandler();
	static void handlerStatic(HttpRequest* pRequest, HttpResponse* pResponse);
public:
	static SRRequestHandler theRequestHandler;
	std::vector<SRFormBase*> forms;
	void handler(HttpRequest* pRequest, HttpResponse* pResponse);
	void Register(HttpServer* s);
};
