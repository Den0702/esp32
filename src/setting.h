#ifndef SETTING_H
#define SETTING_H
#include "Embedis.h"
#include "Arduino.h"
namespace SETTING{

  const uint SERIAL_BADURATE = 112500;
  namespace LOG{
    uint8_t LEVEL();
  }
  namespace EMBEDIS{
    const String WIFI_AP_SSID = F("WIFI_AP_SSID");
    const String WIFI_AP_PASSWORD = F("WIFI_AP_PASSWORD");
    const String WIFI_STA_SSID = F("WIFI_STA_SSID");
    const String WIFI_STA_PASSWORD = F("WIFI_STA_PASSWORD");
    const String TELNET_PASSWORD = F("TELNET_PASSWORD");
    const String LOG_LEVEL = F("LOG_LEVEL");
    const String NTP_TIMEZONE = F("NTP_TIMEZONE");
  }
  namespace DEVICE{
    const uint MODEL = 0;
    const uint FIRMWARE_VERSION = 0;
    String ID();
  }
  namespace WIFI {
    namespace AP{
      String SSID();
      String PASSWORD();
      String HOSTNAME();
    }
    namespace STA{
      String SSID();
      String PASSWORD();
      String HOSTNAME();
    }
  }
  namespace TELNET{
    String PASSWORD();
  }
  namespace MDNS{
    String HOSTNAME();
  }
  namespace NTP{
    const bool DEFAULT_TIMEZONE =0;
    const uint UPDATE_INTERVAL = 60000;

  }
}
#endif
