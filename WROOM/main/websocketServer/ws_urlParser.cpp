#include "ws_urlParser.h"

urlParser::urlParser(std::string url) {
    std::size_t pos = 0, last_pos = 0;

    while(pos!=string::npos){
        pos = url.find("=", last_pos);
        string key = url.substr(last_pos, pos-last_pos);
        last_pos = pos+1;
        pos = url.find("&", last_pos);
        string content = url.substr(last_pos, pos-last_pos);
        last_pos = pos+1;
        pairs.insert(pair<string, string>(key, content));
    }
}

std::string urlParser::getString(std::string key) {
    return pairs[key];
} 