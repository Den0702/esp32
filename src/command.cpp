#include "command.h"
#include "Arduino.h"
#include <Embedis.h>
#include <WiFi.h>
#include "log.h"
void setup_command(){
  Embedis::command("RESTART", [](Embedis* e) {
    ESP.restart();
  });
  Embedis::command("WIFI_STATUS", [](Embedis* e) {
    LOG::LOG("WIFI - HOST: " + String(WiFi.getHostname()));
    LOG::LOG("WIFI - MAC: " + WiFi.macAddress());
    LOG::LOG("WIFI - IP: " + WiFi.localIP().toString() );
    LOG::LOG("WIFI - SUBNETMASK: " + WiFi.subnetMask().toString());
    LOG::LOG("WIFI - GATEWAY: " + WiFi.gatewayIP().toString());
    e->response(Embedis::OK);
  });
}
