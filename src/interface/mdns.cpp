#include "mdns.h"
#include "setting.h"
#include <WiFi.h>

#include <ESPmDNS.h>
#include "log.h"
bool MDNS_SETUP = false;
void setup_mdns(){
  if(!WiFi.isConnected()){
    return;
  }
  if(MDNS_SETUP){
    return;
  }
  String hostname = SETTING::MDNS::HOSTNAME();
  hostname.toLowerCase();
  LOG::DEBUG("MDNS - STARTING");
  MDNS.begin(hostname.c_str());
  MDNS.addService("_telnet","_tcp", 23);
  LOG::DEBUG("MDNS - UP AND RUNNING");
  MDNS_SETUP = true;
}
