#include "command.h"
#include "Arduino.h"
#include <Embedis.h>
#include "setting.h"
#include <WiFi.h>
#include "log.h"
void setup_command(){
  Embedis::command("RESTART", [](Embedis* e) {
    ESP.restart();
  });
  Embedis::command("SYSTEMINFO", [](Embedis* e) {
    LOGGER::LOG("WIFI - ACCESS POINT");
    LOGGER::LOG("HOSTNAME:   " + String(WiFi.softAPgetHostname()));
    // LOGGER::LOG("STATIONS:   " + WiFi.softAPgetStationNum());
    // LOGGER::LOG("IP:         " + WiFi.softAPIP());
    // LOGGER::LOG("MAC ADRESS: " + WiFi.softAPmacAddress());

    LOGGER::LOG("WIFI - STATION");
    LOGGER::LOG("HOSTNAME:    " + String(WiFi.getHostname()));
    LOGGER::LOG("BSSID:       " + WiFi.BSSIDstr());
    LOGGER::LOG("CHANNEL:     " + WiFi.channel());
    LOGGER::LOG("SSID:        " + WiFi.SSID());
    LOGGER::LOG("IP:          " + WiFi.localIP().toString());
    LOGGER::LOG("MAC ADDRESS: " + WiFi.macAddress());
    LOGGER::LOG("SUBNET MASK: " + WiFi.subnetMask().toString());
    LOGGER::LOG("GATEWAY:     " + WiFi.gatewayIP().toString());

    LOGGER::LOG("TELNET");

    LOGGER::LOG("LOG");
    LOGGER::LOG("LEVEL:       " + SETTING::LOG::LEVEL());


    long days=0;
    long hours=0;
    long mins=0;
    long secs=0;
    secs = millis()/1000;
    mins=secs/60;
    hours=mins/60;
    days=hours/24;
    secs=secs-(mins*60);
    mins=mins-(hours*60);
    hours=hours-(days*24);
    LOGGER::LOG("UPTIME:      " + String(days) +  ":days " + String(hours) + ":hours " + String(mins) + ":minutes " + String(secs) + ":seconds");
    /**
    * @TODO add uptime
    */
    e->response(Embedis::OK);
  });
}
