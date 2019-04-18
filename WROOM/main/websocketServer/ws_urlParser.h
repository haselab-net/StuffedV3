#ifndef WEBSOCKET_WS_URLPARSER_H_
#define WEBSOCKET_WS_URLPARSER_H_

#include <iostream>
#include <map>

using namespace std;

class urlParser {
    private:
        map<string, string> pairs;
    public: 
        urlParser(std::string url);

        std::string getString(std::string key);
        std::string getDecodedString(std::string key);
};

#endif