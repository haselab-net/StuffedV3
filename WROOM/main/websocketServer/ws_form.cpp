#include "ws_form.h"

SRRequestHandler SRRequestHandler::theRequestHandler;
void SRRequestHandler::handlerStatic(HttpRequest* pRequest, HttpResponse* pResponse){
    theRequestHandler.handler(pRequest, pResponse);
}
void SRRequestHandler::handler(HttpRequest* pRequest, HttpResponse* pResponse){

}
void SRRequestHandler::Register(HttpServer* s){
//    s->addPathHandler(method, path, handler);
}
