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
    const String DEMANDED_TANK_TEMPERATURE = F("DEMANDED_TANK_TEMPERATURE");
    const String NTP_TIMEZONE = F("NTP_TIMEZONE");
  }
  namespace DEVICE{
    const uint MODEL = 0;
    const uint FIRMWARE_VERSION = 0;
    const uint8_t COOLING_RELAY_PIN_NUMBER = 1;
    const bool COOLING_RELAY_DEFAULT_STATE = false;
    const uint8_t HEATING_RELAY_PIN_NUMBER = 2;
    const bool HEATING_RELAY_DEFAULT_STATE = false;
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
  namespace MQTT{
    String TOPIC();
    const uint PUBLISH_INTERVAL = 10000;
    const String HOST = F("iteam.uek.krakow.pl");
    const uint16_t PORT = 1883;
    String LOGIN();
    String PASSWORD();
    String CLIENT();
  }
  namespace NTP{
    const bool DEFAULT_TIMEZONE =0;
    const uint UPDATE_INTERVAL = 60000;

  }
  namespace TANK{
    const float DEFAULT_DEMANDED_TEMPERATURE = 8;
    float DEMANDED_TEMPERATURE();
  }
}
#endif
