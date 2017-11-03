#include "./thermometer.h"
#include "Arduino.h"
#include "../log.h"
#include <OneWire.h>
#include <DallasTemperature.h>
const uint8_t ONE_WIRE_BUS = 3;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature thermometers(&oneWire);
DeviceAddress tankThermometer,
 incommingMediumThermometer,
 outcommingMediumThermometer;
void setup_thermometer(){
  thermometers.begin();
  if(!thermometers.getAddress(tankThermometer, 0)){
    LOG::LOG("Unable to find tank thermometer");
  }
  if(!thermometers.getAddress(incommingMediumThermometer, 1)){
    LOG::LOG("Unable to find incomming medium thermometer");
  }
  if(!thermometers.getAddress(outcommingMediumThermometer, 2)){
    LOG::LOG("Unable to find outcomming medium thermometer");
  }
}
void loop_thermometer(){
  return thermometers.requestTemperatures();
}
double getTankTemperature(){
  if(thermometers.getDeviceCount() >0)
    return thermometers.getTempC(tankThermometer);
  else
    return -500;
}
double getIncommingMediumTemperature(){
  if(thermometers.getDeviceCount() >0)
    return thermometers.getTempC(incommingMediumThermometer);
  else
    return -500;
}
double getOutcommingMediumTemperature(){
  if(thermometers.getDeviceCount() >0)
    return thermometers.getTempC(outcommingMediumThermometer);
  else
    return -500;
}
