#include "log.h"
#include "Embedis.h"
#include "interface/ntp.h"
#include "setting.h"
namespace LOG{
    namespace LEVEL{
        const uint8_t ERROR =3;
        const uint8_t INFO = 2;
        const uint8_t DEBUG = 1;
    }
    void LOG(const String& message) {
        static bool inSetup = true;
        if (inSetup) {
            if (!message.length()) {
                inSetup = false;
                return;
            }
            Serial.println(getTime() + ": " + message);
        }

        Embedis::publish("LOG", getTime() + ": " + message);
    }
    void DEBUG(const String& message){
        // if(2 == LEVEL::DEBUG){
            LOG("[ DEBUG ] " + message);
        // }
    }

    void ERROR(const String& message){
        // if(2 == LEVEL::DEBUG){
            LOG("[ ERROR ] " + message);
        // }
    }
}
