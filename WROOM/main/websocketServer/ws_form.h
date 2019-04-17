#pragma once
#include "HttpServer.h"
#include "HttpResponse.h"
#include <vector>
#include <regex>

class SRFormBase{
public:
	const char* path;	//	if request path and method match, this form is used.
	const char* method;
	virtual void handler(HttpRequest& request, HttpResponse& response)=0;
};

class SRFormHandler {
	SRFormHandler();
public:
	static std::vector<SRFormBase*> forms;
	static SRFormHandler theFormHandler;
	static void registerToServer(HttpServer* s);
	static void addForm(SRFormBase* form);
};

class SRFormReplace: public SRFormBase{
public:
	struct Replace{
		std::string from;
		std::string to;
		Replace(std::string f, std::string t): from(f), to(t){}
	};
	std::vector<Replace> replaces;
	virtual void handler(HttpRequest& request, HttpResponse& response);
};
