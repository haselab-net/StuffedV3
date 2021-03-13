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

class SRReplace{
public:
	struct Replace{
		std::string from;
		std::string to;
		Replace(std::string f, std::string t): from(f), to(t){}
	};
	//	Response based on file correspond to url and replace contents.
	void handle(HttpRequest& request, HttpResponse& response, std::vector<Replace>& replaces);
	/*	Response based on file replaced by replaces.
	 	Filename is found from URL but replaced by filenameReplace.
		Language extension is added after the filename is replaced. */
	void handle(HttpRequest& request, HttpResponse& response, std::vector<Replace>& replaces, std::vector<Replace>& filenameReplace);
};
