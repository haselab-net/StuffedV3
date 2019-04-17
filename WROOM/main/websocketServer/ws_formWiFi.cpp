#include "ws_form.h"
#include "ws_http.h"
#include "ws_wifi.h"
#include "ws_urlParser.h"
#include <ctype.h>
#include <fstream>
#include <string>
#include <logging.h>
#include <GeneralUtils.h>

static char tag[] = "ws_form";
inline std::string str(int i){
    char buf[10];
    sprintf(buf, "%d", i);
    return std::string(buf);
}
inline std::string str(ip4_addr_t ip){
    char buf[10];
    sprintf(buf, "%d.%d.%d.%d", 0xFF&(ip.addr), 0xFF&(ip.addr>>8), 0xFF&(ip.addr>>16), 0xFF&(ip.addr>>24));
    return std::string(buf);
}

class SRFormMain:public SRFormBase, public SRReplace{
public:
    SRFormMain(){
        method = NULL;
        path = "/";
    }
	virtual void handler(HttpRequest& request, HttpResponse& response){
        std::string body = request.getBody();
        ESP_LOGD(tag, "body:%s", body.c_str());

        std::vector<WiFiAPRecord> aps = SRWiFi::wifi.stopScan();
        std::vector<SRReplace::Replace> replaces;
        replaces.push_back(Replace("nAP", str(aps.size())));
        for(int i=0; i!=aps.size(); ++i){
            WiFiAPRecord& ap = aps[i];
            int power = 100+ap.m_rssi;
            if (power < 0) power = 0;
            replaces.push_back(Replace("ssid" + str(i), ap.m_ssid));
            replaces.push_back(Replace("rssi" + str(i), str(power)));
            replaces.push_back(Replace("auth" + str(i), ap.m_authMode==WIFI_AUTH_OPEN? "🔘" : "🔐"));
        }
        handle(request, response, replaces);
        SRWiFi::wifi.startScan();
    }
} srFormMain;

class SRFormPassword:public SRReplace, public SRFormBase{
public:
    SRFormPassword(){
        method = NULL;
        path = "/password.html";
    }
	virtual void handler(HttpRequest& request, HttpResponse& response){
        std::string body = request.getBody();
        urlParser up(body);
        std::string ssid;
        if (up.getString("typed").length() > 0){
            ssid = up.getString("ssid");
        }else{
            ssid = up.getString("selected");
        }
        ESP_LOGD(tag, "body:%s", body.c_str());
        ESP_LOGD(tag, "ssid:%s", ssid.c_str());
        std::vector<SRReplace::Replace> replaces;
        replaces.push_back(Replace("ssid", ssid));
        handle(request, response, replaces);
    }
} srFormPassword;

class SRFormConnect:public SRReplace, public SRFormBase{
public:
    std::string ssid;
    std::string pass;
    bool bConnecting;
    SRFormConnect(){
        method = NULL;
        path = "/connect.html";
    }
	virtual void handler(HttpRequest& request, HttpResponse& response){
        std::string body = request.getBody();
        urlParser up(body);
        if (up.getString("submit").length()){
            ssid = up.getString("ssid");
            pass = up.getString("pw");
            SRWiFi::wifiNvs.set("ssid", ssid);
            SRWiFi::wifiNvs.set("password", pass);
        }
        ESP_LOGD(tag, "body:%s", body.c_str());
        ESP_LOGD(tag, "wifi.state:%d", SRWiFi::wifi.state);
        std::vector<SRReplace::Replace> replaces;
        switch(SRWiFi::wifi.state){
        case SRWiFi::WIFI_STA_DISCONNECTED:
            SRWiFi::wifi.connectAP(ssid, pass);
        case SRWiFi::WIFI_STA_CONNECTING:
        case SRWiFi::WIFI_STA_CONNECTED:
            replaces.push_back(Replace("ip", ""));                
            replaces.push_back(Replace("netmask", ""));                
            replaces.push_back(Replace("gw", ""));                
            replaces.push_back(Replace("state", "connecting"));
            break;
        case SRWiFi::WIFI_STA_GOT_IP:
            replaces.push_back(Replace("ip", str(SRWiFi::wifi.ipInfo.ip)));                
            replaces.push_back(Replace("netmask", str(SRWiFi::wifi.ipInfo.netmask)));                
            replaces.push_back(Replace("gw", str(SRWiFi::wifi.ipInfo.gw)));                
            replaces.push_back(Replace("state", "connected"));
            break;
        }
        replaces.push_back(Replace("ssid", ssid));
        handle(request, response, replaces);
    }
} srFormConnect;

void addWifiForm(){
    SRFormHandler::addForm(&srFormMain);
    SRFormHandler::addForm(&srFormPassword);
    SRFormHandler::addForm(&srFormConnect);
    ESP_LOGI(tag, "addWifiForm()");
}
