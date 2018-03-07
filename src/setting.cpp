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
}
