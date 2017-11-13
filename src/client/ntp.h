#ifndef CLIENT_NTP_H
#define CLIENT_NTP_H
#include "Arduino.h"
#include <NTPClient.h>

namespace CLIENT{
  namespace NTP{

    class MyNTP:public NTPClient{
    public:
      MyNTP(UDP& udp, const char* poolServerName, int timeOffset, int updateInterval);
      String getFormattedTime();

    };
    void setup();
    void loop();
    String getTime();
    unsigned long getEpochTime();
  }
}
#endif
