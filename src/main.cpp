#include "Arduino.h"
#include "Embedis.h"
#include "interface/eeprom.h"

#include "setting.h"

#include "devices/thermometer.h"

#include "interface/wifi.h"
#include "interface/mdns.h"
#include "interface/telnet.h"
#include "interface/mqtt1.h"
Embedis embedis(Serial);
#include "interface/ntp.h"
#include "log.h"
#include "TemperatureRegulator.h"
#include "command.h"
const uint8_t COOLING_RELAY_PIN_NUMBER = 1;
const bool COOLING_RELAY_DEFAULT_STATE = false;
const uint8_t HEATING_RELAY_PIN_NUMBER = 2;
const bool HEATING_RELAY_DEFAULT_STATE = false;

TemepratureRegulator tankTemepratureRegulator(
  HEATING_RELAY_PIN_NUMBER,
  HEATING_RELAY_DEFAULT_STATE,
  COOLING_RELAY_PIN_NUMBER,
  COOLING_RELAY_DEFAULT_STATE);

  void setup() {
    randomSeed(analogRead(0));
    delay(random(100, 5000));
    Serial.begin(SETTING::SERIAL_BADURATE());
    setup_eeprom();
    setup_command();

    setup_thermometer();


  }



  
  void loop(){
    setup_wifi();
    setup_ntp();

    setup_mdns();
    setup_telnet();
    // setup_mqtt();
    MQTT::setup();


    loop_telnet();
    // loop_thermometer();
    loop_ntp();
    // loop_mqtt();
    MQTT::loop();
    //
    // tankTemepratureRegulator.setSetpoint(SETTING::TANK::DEMANDED_TEMPERATURE());
    // tankTemepratureRegulator.update(getTankTemperature());
    // tankTemepratureRegulator.loop();
    embedis.process();
  }
