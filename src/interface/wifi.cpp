#include "wifi.h"
#include "setting.h"
#include <WiFi.h>
#include "log.h"
#include <Embedis.h>


void event_wifi(WiFiEvent_t event){
  switch(event) {
    case SYSTEM_EVENT_AP_STACONNECTED:
      LOG::DEBUG("WIFI - AP STACONNECTED");
      break;
    case SYSTEM_EVENT_AP_START:
      LOG::DEBUG("WIFI - AP START");
      break;
    case SYSTEM_EVENT_AP_STOP:
      LOG::DEBUG("WIFI - AP STOP");
      break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
      LOG::DEBUG("WIFI - AP STADISCONNECTED");
      break;
    case SYSTEM_EVENT_STA_START:
      LOG::DEBUG("WIFI - STA START");
      break;
    case SYSTEM_EVENT_STA_STOP:
      LOG::DEBUG("WIFI - STA STOP");
      break;
    case SYSTEM_EVENT_STA_LOST_IP:
      LOG::DEBUG("WIFI - STA LOST IP");
      break;
    case SYSTEM_EVENT_WIFI_READY:
      LOG::DEBUG("WIFI - WIFI READY");
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      LOG::DEBUG("WIFI - ETH GOT IP");
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      LOG::DEBUG("WIFI - STA GOT IP");
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      LOG::DEBUG("WIFI - STA DISCONNECTED");
      break;
  }
}
bool WIFI_SETUP = false;
void setup_wifi(){
  if(WIFI_SETUP){
    return;
  }

  WiFi.disconnect();
  WiFi.stopSmartConfig();
  WiFi.softAP(SETTING::DEVICE::ID().c_str());


  WiFi.onEvent(event_wifi);
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.setAutoReconnect(true);
  WiFi.softAPsetHostname(SETTING::DEVICE::ID().c_str());
  WiFi.setHostname(SETTING::DEVICE::ID().c_str());

  WiFi.setAutoConnect(true);
  WiFi.begin(SETTING::WIFI::SSID().c_str(), SETTING::WIFI::PASSWORD().c_str());
  WIFI_SETUP = true;
}
