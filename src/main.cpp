#include "Arduino.h"
#include "Embedis.h"
#include "device/eeprom.h"
#include "setting.h"
#include "device/wifi.h"
#include "server/telnet.h"
Embedis embedis(Serial);
#include "client/ntp.h"
#include "log.h"
#include "command.h"
  void setup() {
    Serial.begin(SETTING::SERIAL_BADURATE);
    DEVICE::EePROM::setup();
    setup_command();
    DEVICE::WIFI::setup();
    CLIENT::NTP::setup();
  }
  void loop(){
    CLIENT::NTP::loop();
    SERVER::TELNET::loop();
    embedis.process();
  }
