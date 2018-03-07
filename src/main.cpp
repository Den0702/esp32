#include "Arduino.h"
#include "Embedis.h"
#include "device/eeprom.h"
#include "setting.h"
Embedis embedis(Serial);
#include "log.h"
#include "command.h"
  void setup() {
    Serial.begin(SETTING::SERIAL_BADURATE);
    DEVICE::EePROM::setup();
    setup_command();
  }
  void loop(){
    embedis.process();
  }
