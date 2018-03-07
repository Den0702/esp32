#include "wifi.h"
#include "setting.h"
#include <WiFi.h>
#include "log.h"
#include <Embedis.h>

namespace DEVICE{
  namespace WIFI{
    void event(WiFiEvent_t event){
      switch(event) {
        case SYSTEM_EVENT_AP_STACONNECTED:
        LOGGER::DEBUG("WIFI - AP STACONNECTED");
        break;
        case SYSTEM_EVENT_AP_START:
        LOGGER::DEBUG("WIFI - AP START");
        break;
        case SYSTEM_EVENT_AP_STOP:
        LOGGER::DEBUG("WIFI - AP STOP");
        break;
        case SYSTEM_EVENT_AP_STADISCONNECTED:
        LOGGER::DEBUG("WIFI - AP STADISCONNECTED");
        break;
        case SYSTEM_EVENT_STA_START:
        LOGGER::DEBUG("WIFI - STA START");
        break;
        case SYSTEM_EVENT_STA_STOP:
        LOGGER::DEBUG("WIFI - STA STOP");
        break;
        case SYSTEM_EVENT_STA_LOST_IP:
        LOGGER::DEBUG("WIFI - STA LOST IP");
        break;
        case SYSTEM_EVENT_WIFI_READY:
        LOGGER::DEBUG("WIFI - WIFI READY");
        break;
        case SYSTEM_EVENT_ETH_GOT_IP:
        LOGGER::DEBUG("WIFI - ETH GOT IP");
        break;
        case SYSTEM_EVENT_STA_GOT_IP:
        LOGGER::DEBUG("WIFI - STA GOT IP");
        break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
        LOGGER::DEBUG("WIFI - STA DISCONNECTED");
        break;
      }
    }
    bool SETUP = false;
    const char *ssid = "ESP32ap";
const char *password = "12345678";
    void setup(){
      if(SETUP){
        return;
      }
      WiFi.mode(WIFI_MODE_APSTA);
      WiFi.onEvent(event);

      WiFi.begin(SETTING::WIFI::STA::SSID().c_str(), SETTING::WIFI::STA::PASSWORD().c_str());
      WiFi.softAP(ssid, password);

      WiFi.setAutoConnect(true);
      WiFi.setAutoReconnect(true);

      SETUP = true;
    }
  }
}
