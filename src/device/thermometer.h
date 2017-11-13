#ifndef DEVICE_THERMOMETER_H
#define DEVICE_THERMOMETER_H
#include <Arduino.h>
namespace DEVICE{
  namespace THERMOMETER{
    const uint8_t ONE_WIRE_BUS = 3;

    void setup();
    void loop();
    double getTankTemperature();
    double getIncommingMediumTemperature();
    double getOutcommingMediumTemperature();
  }
}
#endif
