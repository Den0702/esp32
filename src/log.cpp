#include "log.h"
#include "Embedis.h"
#include "setting.h"
namespace LOGGER{
  void LOG(const String& message) {
    static bool inSetup = true;
    if (inSetup) {
      if (!message.length()) {
        inSetup = false;
        return;
      }
      Serial.println(message);
    }
    Embedis::publish("LOG", message);
  }

  /**
  * @TODO uruchomić LOG LEVEL
  */
  void DEBUG(const String& message){
    if(SETTING::LOG::LEVEL() >= LEVEL::DEBUG){
      LOG("[ DEBUG ] " + message);
    }
  }

  void ERROR(const String& message){
    if(SETTING::LOG::LEVEL() >= LEVEL::ERROR){
      LOG("[ ERROR ] " + message);
    }
  }
}
