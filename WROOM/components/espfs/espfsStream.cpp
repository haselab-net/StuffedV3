#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <esp_spi_flash.h>
#include <esp_log.h>
#include <esp_err.h>
#include <iostream>

extern "C" {
    #include "espfsformat.h"
    #include "espfs.h"
}

#include "espfsStream.h"
#include "sdkconfig.h"

static char tag[] = "espfs";

class espFsStreambuf: public std::streambuf{
    protected:
    size_t flashAddress;
    int len;
    char buf[256];
    public:
    espFsStreambuf() = delete;
    espFsStreambuf(size_t fa, int l):flashAddress(fa), len(l){
        setp(buf, buf+ sizeof(buf));
    }
    virtual ~espFsStreambuf(){
        sync();
        if (len){
            ESP_LOGE(tag, "Clean area remains %d bytes.", len);
        }
    }
    virtual int overflow( int p_iChar = EOF ){
        size_t writeLen = pptr()-pbase();
        if (writeLen > len){
            ESP_LOGE(tag, "Try to write a data longer than the file length.");
            writeLen = len;
            return traits_type::eof();
        }
        len -= writeLen;
		spi_flash_write(flashAddress, pbase(), writeLen);	//	write whole buffer into flash.
        flashAddress += pptr()-pbase();
        if (traits_type::eq_int_type(p_iChar, traits_type::eof())){
            //  put overflowed character in the buffer.
            buf[0] = traits_type::to_char_type(p_iChar);
            setp(buf+1, buf+ sizeof(buf)-1);
            return 1; 
        }else{
            setp(buf, buf+ sizeof(buf));
            return 0;
        }
    }
    virtual int sync(){
        overflow();
        return 0;   // success
    }
};

class espOstream:public std::ostream{
public:
    espOstream(std::streambuf* b):std::ostream(b){
    }
    virtual ~espOstream(){
        delete rdbuf();
    }
};

std::ostream* espFsAddFileByStream(const char* fname, int len){
    size_t adr = espFsAddCleanArea(fname, len);
    if (adr){
        return new espOstream(new espFsStreambuf(adr, len));
    }
    return NULL;
}