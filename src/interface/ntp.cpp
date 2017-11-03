#include "ntp.h"
#include <WiFi.h>
#include <NTPClient.h>
#include "../log.h"

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
bool NTP_SETUP = false;
void setup_ntp(){
  if(WiFi.isConnected()){
    return;
  }
  if(NTP_SETUP){
    return;
  }
  LOG::DEBUG("NTP starting");
  timeClient.begin();
  LOG::DEBUG("NTP up and running");

  NTP_SETUP = true;
}

uint64_t previousMillisNTP = 0;        // will store last time LED was updated
uint intervalNTP = 10000;           // interval at which to blink (milliseconds)
void loop_ntp() {
  if(!WiFi.isConnected()){
    return;
  }
  uint64_t currentMillis = millis();
  if (currentMillis - previousMillisNTP >= intervalNTP) {
    previousMillisNTP = currentMillis;
    timeClient.update();
    LOG::DEBUG("NTP time updated");

  }
}

String getTime(){
    return timeClient.getFormattedTime();
}
