#include "log.h"
#include "Embedis.h"
#include "./client/ntp.h"
#include "setting.h"
namespace LOGGER{
  void LOG(const String& message) {
    static bool inSetup = true;
    if (inSetup) {
      if (!message.length()) {
        inSetup = false;
        return;
      }
      Serial.println(CLIENT::NTP::getTime() + ": " + message);
    }
    Embedis::publish("LOG", CLIENT::NTP::getTime() + ": " + message);
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
