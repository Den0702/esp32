#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Embedis.h"
Embedis embedis(Serial);

#include "commands.h"
#include "log.h"
#include "TemperatureRegulator.h"
const uint8_t ONE_WIRE_BUS = 3;
const uint64_t SERIAL_BADURATE = 115200;
const uint8_t COOLING_VALVE_PIN_NUMBER = 1;
const bool COOLING_VALVE_DEFAULT_STATE = false;
const uint8_t HEATING_VALVE_PIN_NUMBER = 2;
const bool HEATING_VALVE_DEFAULT_STATE = false;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature thermometers(&oneWire);
DeviceAddress tankThermometer,
 incommingMediumThermometer,
 outcommingMediumThermometer;
TemepratureRegulator tankTemepratureRegulator(
  HEATING_VALVE_PIN_NUMBER,
  HEATING_VALVE_DEFAULT_STATE,
  COOLING_VALVE_PIN_NUMBER,
  COOLING_VALVE_DEFAULT_STATE);
void setup() {
  setup_commands();
  Serial.begin(SERIAL_BADURATE);
  thermometers.begin();
  if(!thermometers.getAddress(tankThermometer, 0)){
    LOG("Unable to find tank thermometer");
  }
  if(!thermometers.getAddress(incommingMediumThermometer, 1)){
    LOG("Unable to find incomming medium thermometer");
  }
  if(!thermometers.getAddress(outcommingMediumThermometer, 2)){
    LOG("Unable to find outcomming medium thermometer");
  }
}
void loop(){
  tankTemepratureRegulator.setTemperatureToMaintain(getRequestedTankThermometerTemperature());
  tankTemepratureRegulator.updateTemperature(thermometers.getTempC(tankThermometer));
  tankTemepratureRegulator.loop();
  embedis.process();
}
