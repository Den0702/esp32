#include "./thermometer.h"
#include "Arduino.h"
#include "../log.h"
#include <OneWire.h>
#include <DallasTemperature.h>

namespace DEVICE{
  namespace THERMOMETER{
    bool SETUP = false;
    OneWire oneWire(ONE_WIRE_BUS);
    DallasTemperature thermometers(&oneWire);
    DeviceAddress tankThermometer,
    incommingMediumThermometer,
    outcommingMediumThermometer;
    void setup(){
      if(!SETUP){
        thermometers.begin();
        if(!thermometers.getAddress(tankThermometer, 0)){
          LOGGER::LOG("Unable to find tank thermometer");
        }
        if(!thermometers.getAddress(incommingMediumThermometer, 1)){
          LOGGER::LOG("Unable to find incomming medium thermometer");
        }
        if(!thermometers.getAddress(outcommingMediumThermometer, 2)){
          LOGGER::LOG("Unable to find outcomming medium thermometer");
        }
        SETUP = true;
      }
    }
    void loop(){
      if(!SETUP){
        setup();
      }
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
  }
}
