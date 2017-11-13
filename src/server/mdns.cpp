#include "mdns.h"
#include "setting.h"
#include <WiFi.h>

#include <ESPmDNS.h>
#include "telnet.h"
#include "log.h"
namespace SERVER{
  namespace mDNS{
    bool SETUP = false;
    void setup(){
      if(!WiFi.isConnected()){
        return;
      }
      if(SETUP){
        return;
      }
      String hostname = SETTING::MDNS::HOSTNAME();
      hostname.toLowerCase();
      LOGGER::DEBUG("MDNS - STARTING");
      MDNS.begin(hostname.c_str());
      MDNS.addService("_telnet","_tcp", SERVER::TELNET::PORT);
      LOGGER::DEBUG("MDNS - UP AND RUNNING");
      SETUP = true;
    }

    void loop(){
      if(!SETUP){
        setup();
      }
    }
  }
}
