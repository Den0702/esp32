#include "Arduino.h"
#include "Embedis.h"
#include "device/eeprom.h"
#include "setting.h"
#include "device/wifi.h"
#include "server/mdns.h"
#include "server/telnet.h"
#include "client/mqtt.h"
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
    // CLIENT::MQTT::loop();
    SERVER::mDNS::loop();
    SERVER::TELNET::loop();
    embedis.process();
  }
