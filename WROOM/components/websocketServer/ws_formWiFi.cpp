#include "ws_form.h"
#include "ws_http.h"
#include "SRWifi.h"
#include "ws_urlParser.h"
#include <ctype.h>
#include <fstream>
#include <string>
#include <logging.h>
#include <GeneralUtils.h>
#include <esp_wifi.h>

static char tag[] = "ws_form";
inline std::string str(int i){
    char buf[11];
    sprintf(buf, "%d", i);
    return std::string(buf);
}
inline std::string str(esp_ip4_addr_t ip){
    char buf[12+3+1];
    sprintf(buf, "%d.%d.%d.%d", 0xFF&(ip.addr), 0xFF&(ip.addr>>8), 0xFF&(ip.addr>>16), 0xFF&(ip.addr>>24));
    return std::string(buf);
}

static void pushIpStatus(std::vector<SRReplace::Replace>& replaces){
    if (SRWiFi::wifi.state == SRWiFi::WIFI_STA_GOT_IP){
        replaces.push_back(SRReplace::Replace("noip", ""));
        replaces.push_back(SRReplace::Replace("gotip", "YES"));
        replaces.push_back(SRReplace::Replace("ip", str(SRWiFi::wifi.ipInfo.ip)));
        replaces.push_back(SRReplace::Replace("mask", str(SRWiFi::wifi.ipInfo.netmask)));                
        replaces.push_back(SRReplace::Replace("gw", str(SRWiFi::wifi.ipInfo.gw)));                
        replaces.push_back(SRReplace::Replace("state", "got ip address from DHCP"));
    }else{
        replaces.push_back(SRReplace::Replace("noip", "YES"));
        replaces.push_back(SRReplace::Replace("gotip", ""));
        replaces.push_back(SRReplace::Replace("ip", ""));                
        replaces.push_back(SRReplace::Replace("mask", ""));                
        replaces.push_back(SRReplace::Replace("gw", ""));                
        if(SRWiFi::wifi.state == SRWiFi::WIFI_STA_CONNECTED){
            replaces.push_back(SRReplace::Replace("state", "connected and waiting DHCP"));
        }else if (SRWiFi::wifi.state == SRWiFi::WIFI_STA_CONNECTING){
            replaces.push_back(SRReplace::Replace("state", "connecting"));
        }else if(SRWiFi::wifi.state == SRWiFi::WIFI_STA_DISCONNECTED){
            replaces.push_back(SRReplace::Replace("state", "disconnected"));
        }
    }
}

class SRFormDelete:public SRFormBase, public SRReplace{
public:
    SRFormDelete(){
        method = NULL;
        path = "/delete.html";
    }
	virtual void handler(HttpRequest& request, HttpResponse& response){
        std::string body = request.getBody();
        ESP_LOGD(tag, "body:%s", body.c_str());

        urlParser up(body);
        std::string ssid = up.getDecodedString("selected");
        std::vector<SRReplace::Replace> replaces;
        int nDeleted = 0;
        if (up.getDecodedString("all").length()){
            SRWiFi::wifiNvs->erase("lastAP");
            for(int i=0; i<SRWiFi::N_AP_RECORD_MAX; ++i){
                char ssidKey[] = "ssid0"; ssidKey[4] = '0'+i;
                if (SRWiFi::wifiNvs->get(ssidKey, ssid) == ESP_OK){
                    SRWiFi::wifiNvs->erase(ssidKey);
                    char passKey[] = "pass0"; passKey[4] = '0'+i;
                    SRWiFi::wifiNvs->erase(passKey);
                    char from[] = "ssidDel0";
                    from[7] = '0' + nDeleted;
                    replaces.push_back(Replace(from, ssid));
                    nDeleted ++;
                }
            }
        }else if (ssid.length()){
            //  disconnect if WiFi AP's ssid == ssid
            if (SRWiFi::wifi.getStaSSID() == ssid){
                SRWiFi::wifi.disconnect();
            }
            int lastAP = 0;
            SRWiFi::wifiNvs->get("lastAP", lastAP);
            for(int i=0; i<SRWiFi::N_AP_RECORD_MAX; ++i){
                char ssidKey[] = "ssid0"; ssidKey[4] = '0'+i;
                std::string rec;
                SRWiFi::wifiNvs->get(ssidKey, rec);
                if (rec == ssid){
                    char from[] = "ssidDel0";
                    from[7] = '0' + nDeleted;
                    replaces.push_back(Replace(from, ssid));
                    nDeleted ++;
                    SRWiFi::wifiNvs->erase(ssidKey);
                    char passKey[] = "pass0"; passKey[4] = '0'+i;
                    SRWiFi::wifiNvs->erase(passKey);
                    if (lastAP == i){
                        int i = lastAP-1;
                        while(i!=lastAP){
                            if (i < 0) i = SRWiFi::N_AP_RECORD_MAX-1;
                            ssidKey[4] = '0' + i;
                            SRWiFi::wifiNvs->get(ssidKey, rec);
                            if (rec.length()) {
                                lastAP = i;
                                SRWiFi::wifiNvs->get("lastAP", lastAP);
                                break;
                            }
                            i--;
                        }
                    }
                    break;
                }
            }
        }
        replaces.push_back(Replace("nDel", str(nDeleted)));

        int nRec = 0;
        int lastAP = 0;
        if (SRWiFi::wifiNvs->get("lastAP", lastAP) == ESP_OK){
            ESP_LOGI(tag, "lastAP %d", lastAP);
            if (lastAP < 0) lastAP = 0;
            if (lastAP >= SRWiFi::N_AP_RECORD_MAX) lastAP = SRWiFi::N_AP_RECORD_MAX-1;
            int i=lastAP;
            std::string ssid;
            do{
                char ssidKey[] = "ssid0"; ssidKey[4] = '0'+i;
                if (SRWiFi::wifiNvs->get(ssidKey, ssid) == ESP_OK){
                    ssidKey[4] = '0' + nRec;
                    replaces.push_back(Replace(ssidKey, ssid));
                    nRec ++;
                }
                i--;
                if (i<0) i = SRWiFi::N_AP_RECORD_MAX-1;
            }while(i!=lastAP);
        }
        replaces.push_back(Replace("nRec", str(nRec)));
        handle(request, response, replaces);
        SRWiFi::wifiNvs->commit();
    }
} srFormDelete;



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
        if (up.getDecodedString("typed").length() > 0){
            ssid = up.getDecodedString("ssid");
        }else{
            ssid = up.getDecodedString("selected");
        }
        if (ssid.length() == 0){
            //  redirect to index.html
            response.setStatus(303, "See Other");
            response.addHeader("Location","/index.html");
    		response.close();
            return;
        }
        std::vector<SRReplace::Replace> replaces;
        replaces.push_back(Replace("ssid", ssid));
        handle(request, response, replaces);
    }
} srFormPassword;

class SRFormConnect:public SRReplace, public SRFormBase{
public:
    std::string ssid;
    std::string pass;
    SRFormConnect(){
        method = NULL;
        path = "/connect.html";
    }
	virtual void handler(HttpRequest& request, HttpResponse& response){
        std::string body = request.getBody();
        urlParser up(body);
        if (up.getDecodedString("apSwitch").length()){
            if (SRWiFi::wifi.isAP()){
                SRWiFi::wifi.stopAP();
            }else {
                SRWiFi::wifi.startAP();
            }
        }
        if (up.getDecodedString("submit").length()){
            ssid = up.getDecodedString("ssid");
            pass = up.getDecodedString("pw");
        }
        ESP_LOGD(tag, "body:%s", body.c_str());
        ESP_LOGD(tag, "wifi.state:%d", SRWiFi::wifi.state);
        if (ssid.length() == 0){
            //  redirect to index.html
            response.setStatus(303, "See Other");
            response.addHeader("Location","/index.html");
    		response.close();
            return;
        }
        if (SRWiFi::wifi.state == SRWiFi::WIFI_STA_DISCONNECTED){
            ESP_LOGD(tag, "Connecting to ssid:%s with password:%s", ssid.c_str(), pass.c_str());
            SRWiFi::wifi.connect(ssid, pass);
        }
        std::vector<SRReplace::Replace> replaces;
        replaces.push_back(Replace("ssid", ssid));
        pushIpStatus(replaces);
        if (SRWiFi::wifi.isAP()){
            replaces.push_back(Replace("apStart", "1"));
            replaces.push_back(Replace("apStop", ""));
        }else{
            replaces.push_back(Replace("apStop", "1"));
            replaces.push_back(Replace("apStart", ""));
        }
        handle(request, response, replaces);
    }
} srFormConnect;

class SRFormMain:public SRFormBase, public SRReplace{
public:
    SRFormMain(const char* p){
        method = NULL;
        path = p;
    }
	virtual void handler(HttpRequest& request, HttpResponse& response){
        std::string body = request.getBody();
        ESP_LOGD(tag, "body:%s", body.c_str());
        std::vector<SRReplace::Replace> replaces;
        if (SRWiFi::wifi.state == SRWiFi::Status::WIFI_STA_DISCONNECTED){
            //  list the wifi AP and ask to choose one.
            replaces.push_back(Replace("nAP", str(SRWiFi::wifi.scannedAPs.size())));
            for(int i=0; i!=SRWiFi::wifi.scannedAPs.size(); ++i){
                WiFiAPRecord& ap = SRWiFi::wifi.scannedAPs[i];
                int power = 100+ap.rssi;
                if (power < 0) power = 0;
                replaces.push_back(Replace("ssid" + str(i), ap.ssid));
                replaces.push_back(Replace("rssi" + str(i), str(power)));
                replaces.push_back(Replace("auth" + str(i), ap.authMode==WIFI_AUTH_OPEN? "🔘" : "🔐"));
            }
            handle(request, response, replaces);
            SRWiFi::wifi.startScan();
        }else{
            //  Connected or connecting, show status and ask to canel
            srFormConnect.ssid = SRWiFi::wifi.getStaSSID();
            srFormConnect.pass =  SRWiFi::wifi.getStaPassword();
            response.setStatus(303, "See Other");
            response.addHeader("Location","/connect.html");
    		response.close();
        }
    }
} srFormRoot("/"), srFormIndex("/index.html");


void addWifiForm(){
    SRFormHandler::addForm(&srFormDelete);
    SRFormHandler::addForm(&srFormRoot);
    SRFormHandler::addForm(&srFormIndex);
    SRFormHandler::addForm(&srFormPassword);
    SRFormHandler::addForm(&srFormConnect);
}
