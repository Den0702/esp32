#include "Arduino.h"
#include "Embedis.h"
#include "device/eeprom.h"
#include "setting.h"
Embedis embedis(Serial);
#include "log.h"
  void setup() {
    Serial.begin(SETTING::SERIAL_BADURATE);
    DEVICE::EePROM::setup();
  }
  void loop(){
    embedis.process();
  }
