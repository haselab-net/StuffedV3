#pragma once
#include "HttpServer.h"
#include "HttpResponse.h"
#include <vector>
#include <regex>

class SRFormBase{
public:
	std::regex path;	//	if request path and method match, this form is used.
	const char* method;
	virtual void handler(HttpRequest& request, HttpResponse& response)=0;
};

class SRRequestHandler {
	SRRequestHandler();
public:
	static SRRequestHandler theRequestHandler;
	std::vector<SRFormBase*> forms;
	void Register(HttpServer* s);
};

class SRFormReplace: public SRFormBase{
public:
	struct Replace{
		std::string from;
		std::string to;
	};
	std::vector<Replace> replaces;
	virtual void handler(HttpRequest& request, HttpResponse& response);
};
