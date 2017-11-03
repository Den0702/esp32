#ifndef TEMPERATURE_REGULATOR
#define TEMPERATURE_REGULATOR
#include "Arduino.h"
#include "Relay.h"
#include <PID_v1.h>

class TemepratureRegulator{
private:
  uint8_t heatingRelayPinNumber;
  bool heatingRelayDefaultState;
  uint8_t coolingRelayPinNumber;
  bool coolingRelayDefaultState;
  Relay* heatingRelay;
  Relay* coolingRelay;
  PID* pid;
  uint64_t windowSize = 5000;
  unsigned long windowStartTime;
  double setpoint,
  input,
  output,
  currentTemperature;

public:
  TemepratureRegulator(uint8_t heatingRelayPinNumber,
    bool heatingRelayDefaultState,
    uint8_t coolingRelayPinNumber,
    bool coolingRelayDefaultState);
  void update(double temeprature);
  void setSetpoint(double temeprature);
  void loop();
};
#endif
