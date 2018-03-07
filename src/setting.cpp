#include "setting.h"
#include "Embedis.h"
#include "Arduino.h"
namespace SETTING{
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
}
