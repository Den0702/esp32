#include "ntp.h"

#include "Arduino.h"
#include <WiFi.h>
#include <NTPClient.h>
#include "../log.h"
#include <time.h>
#include "setting.h"
namespace CLIENT{
  namespace NTP{
    MyNTP::MyNTP(UDP& udp, const char* poolServerName, int timeOffset, int updateInterval): NTPClient(udp, poolServerName,timeOffset, updateInterval){
    }
    String MyNTP::getFormattedTime() {
      time_t rawtime = this->getEpochTime();
      struct tm * ti;
      ti = localtime (&rawtime);
      time_t year = ti->tm_year + 1900;
      String yearStr = String(year);
      time_t month = ti->tm_mon + 1;
      String monthStr = month < 10 ? "0" + String(month) : String(month);
      time_t day = ti->tm_mday;
      String dayStr = day < 10 ? "0" + String(day) : String(day);
      time_t hours = ti->tm_hour;
      String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);
      time_t minutes = ti->tm_min;
      String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);
      time_t seconds = ti->tm_sec;
      String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);
      return yearStr + "-" + monthStr + "-" + dayStr + " " +
      hoursStr + ":" + minuteStr + ":" + secondStr;
    };

    WiFiUDP socket;
    MyNTP client(socket, "pool.ntp.org", SETTING::NTP::DEFAULT_TIMEZONE, SETTING::NTP::UPDATE_INTERVAL);
    bool SETUP = false;
    void setup(){
      if(!WiFi.isConnected()){
        return;
      }
      if(SETUP){
        return;
      }
      LOGGER::DEBUG("NTP starting");
      client.begin();
      client.update();
      LOGGER::DEBUG("NTP up and running");
      SETUP = true;
    }
    void loop() {
      if(!WiFi.isConnected()){
        return;
      }
      if(!SETUP){
        setup();
        return;
      }
    }
    String getTime(){
      return client.getFormattedTime();
    }

    unsigned long getEpochTime(){
      return client.getEpochTime();
    }
  }
}
