#include "ws_urlParser.h"
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>

char *url_encode(const char *str);
char *url_decode(const char *str);

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

std::string urlParser::getDecodedString(std::string key) {
    char* dec = url_decode(pairs[key].c_str());
    std::string rv(dec);
    free(dec);
    return rv;
} 

/* Converts a hex character to its integer value */
char from_hex(char ch) {
  return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

/* Converts an integer value to its hex character*/
char to_hex(char code) {
  static char hex[] = "0123456789abcdef";
  return hex[code & 15];
}

/* Returns a url-encoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_encode(const char *str) {
  const char* pstr = str;
  char *buf = (char*)malloc(strlen(str) * 3 + 1), *pbuf = buf;
  while (*pstr) {
    if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~') 
      *pbuf++ = *pstr;
    else if (*pstr == ' ') 
      *pbuf++ = '+';
    else 
      *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}

/* Returns a url-decoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_decode(const char *str) {
  const char *pstr = str;
  char *buf = (char*)malloc(strlen(str) + 1), *pbuf = buf;
  while (*pstr) {
    if (*pstr == '%') {
      if (pstr[1] && pstr[2]) {
        *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
        pstr += 2;
      }
    } else if (*pstr == '+') { 
      *pbuf++ = ' ';
    } else {
      *pbuf++ = *pstr;
    }
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}