#include "log.h"
#include "Embedis.h"
void LOG(const String& message) {
    static bool inSetup = true;
    if (inSetup) {
        if (!message.length()) {
            inSetup = false;
            return;
        }
        Serial.println(message);
    }
    Embedis::publish("log", message);
}
