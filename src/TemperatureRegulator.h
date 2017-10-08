#ifndef TEMPERATURE_REGULATOR
#define TEMPERATURE_REGULATOR
#include "Arduino.h"
#include "Relay.h"
#include <PID_v1.h>

class TemepratureRegulator{
public:

  Relay* heatingValve;
  Relay* coolingValve;
  PID* pid;

  const uint64_t windowSize = 5000;
  unsigned long windowStartTime;

  double setpoint,
  input,
  output, currentTemperature;

  uint8_t _heatingValvePinNumber;
  bool _heatingValveDefaultState;
  uint8_t _coolingValvePinNumber;
  bool _coolingValveDefaultState;

  TemepratureRegulator(uint8_t heatingValvePinNumber,
    bool heatingValveDefaultState,
    uint8_t coolingValvePinNumber,
    bool coolingValveDefaultState);
  void updateTemperature(double temeprature);
  void setTemperatureToMaintain(double temeprature);
  void loop();
};
#endif
