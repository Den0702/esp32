#include "setting.h"
#include "Embedis.h"
#include "Arduino.h"
#include <WiFi.h>
#include "log.h"
namespace SETTING{
  String getSettingValue(String key, String val){
    String str;
    if(!Embedis::get(key, str)) {
      LOGGER::DEBUG("EMBEDIS - Not defined key: " + key + " using default value: " + val);
      return val;
    }
    return str;
  }
  uint SERIAL_BADURATE(){
    return 112500;
  }


  namespace DEVICE{
    String ID(){
      delay(2);
      uint64_t id = ESP.getEfuseMac();
      char tmp_h[9];
      char tmp_l[9];
      sprintf(tmp_h, "%08X", (uint32_t)(id>>32));
      sprintf(tmp_l, "%08X", (uint32_t)(id));
      delay(2);

      return String(tmp_h) + String(tmp_l);
    }
  }
  namespace LOG{
    uint8_t LEVEL(){
      String str;
      if(!Embedis::get(EMBEDIS::LOG_LEVEL, str)) {
        return LOGGER::LEVEL::DEBUG;
      }
      return str.toInt();
    }
  }
  namespace WIFI {
    namespace AP{
      String SSID(){
        return "IOTHUB" + getSettingValue(EMBEDIS::WIFI_AP_SSID, SETTING::DEVICE::ID());
      }
      String PASSWORD(){
        return "iothub";
        return getSettingValue(EMBEDIS::WIFI_AP_PASSWORD, "iothub");
      }
      String HOSTNAME(){
        return "IOTHUB" + SETTING::DEVICE::ID();
      }
    }
    namespace STA{
      String SSID(){
        return getSettingValue(EMBEDIS::WIFI_STA_SSID, "iothub");
      }
      String PASSWORD(){
        return getSettingValue(EMBEDIS::WIFI_STA_PASSWORD, "iothub");
      }
      String HOSTNAME(){
        return SETTING::DEVICE::ID();
      }
    }
  }
  namespace TELNET{
    String PASSWORD(){
      return getSettingValue(EMBEDIS::TELNET_PASSWORD, "iothub");
    }
  }
  namespace MDNS{
    String HOSTNAME(){
      return DEVICE::ID();
    }
  }
  namespace MQTT{
    String TOPIC(){
      return DEVICE::ID();
    }
    String CLIENT(){
      return DEVICE::ID();
    }
    String LOGIN(){
      return DEVICE::ID();
    }
    String PASSWORD(){
      return DEVICE::ID();
    }
  }
  namespace TANK{
    /**
    * @TODO ADD CONST DEFAULT VALUE
    */
    float DEMANDED_TEMPERATURE(){

      String str;
      if(!Embedis::get(EMBEDIS::DEMANDED_TANK_TEMPERATURE, str)) {
        return DEFAULT_DEMANDED_TEMPERATURE;
      }
      return str.toFloat();
    }
  }
}
