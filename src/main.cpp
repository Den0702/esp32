#include "Arduino.h"
#include "Embedis.h"
#include "device/eeprom.h"
#include "setting.h"
#include "device/thermometer.h"
#include "device/wifi.h"
#include "server/mdns.h"
#include "server/telnet.h"
#include "client/mqtt.h"
Embedis embedis(Serial);
#include "client/ntp.h"
#include "log.h"
#include "TemperatureRegulator.h"
#include "command.h"
  void setup() {
    Serial.begin(SETTING::SERIAL_BADURATE());
    DEVICE::EePROM::setup();
    setup_command();
    DEVICE::WIFI::setup();
    CLIENT::NTP::setup();
  }
  TemepratureRegulator tankTemepratureRegulator(
    SETTING::DEVICE::HEATING_RELAY_PIN_NUMBER,
    SETTING::DEVICE::HEATING_RELAY_DEFAULT_STATE,
    SETTING::DEVICE::COOLING_RELAY_PIN_NUMBER,
    SETTING::DEVICE::COOLING_RELAY_DEFAULT_STATE);
  void loop(){
    // DEVICE::THERMOMETER::loop();
    CLIENT::NTP::loop();
    CLIENT::MQTT::loop();
    SERVER::mDNS::loop();
    SERVER::TELNET::loop();
    // tankTemepratureRegulator.setSetpoint(SETTING::TANK::DEMANDED_TEMPERATURE());
    // tankTemepratureRegulator.update(DEVICE::THERMOMETER::getTankTemperature());
    // tankTemepratureRegulator.loop();
    embedis.process();
  }
