#include "setting.h"
#include "Embedis.h"
#include "Arduino.h"
#include <WiFi.h>
#include "log.h"

namespace SETTING{
  String getSettingValue(String key, String val){
    String str;
    if(!Embedis::get(key, str)) {
      // std::LOG::LOG("[INFO] - Not defined " + key + " using default value!");
      return val;
    }
    return str;
  }
  uint SERIAL_BADURATE(){
    return 112500;
  }

  namespace DEVICE{
    String ID(){
      uint64_t id = ESP.getEfuseMac();
      char tmp_h[9];
      char tmp_l[9];
      sprintf(tmp_h, "%08X", (uint32_t)(id>>32));
      sprintf(tmp_l, "%08X", (uint32_t)(id));
      return String(tmp_h) + String(tmp_l);
    }
  }
  namespace LOG{
    String LEVEL(){
      return "ALL";
    }
  }

  namespace WIFI {
    String SSID(){
      return getSettingValue(WIFI_SSID, "iothub");
    }
    String PASSWORD(){
      return getSettingValue(WIFI_PASSWORD, "iothub");
    }
  }

  namespace TELNET{
    String PASSWORD(){
      return getSettingValue(TELNET_PASSWORD, "iothub");
    }
  }

  namespace MDNS{
    String HOSTNAME(){
      return DEVICE::ID();
    }
  }
  namespace MQTT{
    String CLIENT(){
      return "plysiu";
    }
  }
  namespace TANK{
    float DEMANDED_TEMPERATURE(){
      return getSettingValue(TANK_DEMANDED_TEMPERATURE, "8").toFloat();
    }
  }
}
