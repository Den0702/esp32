#include "TemperatureRegulator.h"
#include "log.h"
/********************************************************
 * PID RelayOutput Example
 * Same as basic example, except that this time, the output
 * is going to a digital pin which (we presume) is controlling
 * a relay.  the pid is designed to Output an analog value,
 * but the relay can only be On/Off.
 *
 *   to connect them together we use "time proportioning
 * control"  it's essentially a really slow version of PWM.
 * first we decide on a window size (5000mS say.) we then
 * set the pid to adjust its output between 0 and that window
 * size.  lastly, we add some logic that translates the PID
 * output into "Relay On Time" with the remainder of the
 * window being "Relay Off Time"
 ********************************************************/
TemepratureRegulator::TemepratureRegulator(uint8_t heatingRelayPinNumber,
  bool heatingRelayDefaultState,
  uint8_t coolingRelayPinNumber,
  bool coolingRelayDefaultState):
  heatingRelayPinNumber(heatingRelayPinNumber),
  heatingRelayDefaultState(heatingRelayDefaultState),
  coolingRelayPinNumber(coolingRelayPinNumber),
  coolingRelayDefaultState(coolingRelayDefaultState) {
  heatingRelay = new Relay(heatingRelayPinNumber,
     heatingRelayDefaultState);
  coolingRelay = new Relay(coolingRelayPinNumber,
     coolingRelayDefaultState);
  pid = new PID(&input, &output, &setpoint, 2, 5, 1, DIRECT);
  pid->SetOutputLimits(0, windowSize);
  pid->SetMode(AUTOMATIC);
  windowStartTime = millis();
}
void TemepratureRegulator::update(double temperature){
  currentTemperature = temperature;
}
void TemepratureRegulator::setSetpoint(double temperature){
  setpoint = temperature;
}
void TemepratureRegulator::loop(){
  pid->Compute();
  if(millis() - windowStartTime > windowSize){
    windowStartTime += windowSize;
  }
  if(output < millis() - windowStartTime) {
    if(setpoint < currentTemperature){
      coolingRelay->turnOn();
      heatingRelay->turnOff();
    }
    if(setpoint > currentTemperature){
      coolingRelay->turnOff();
      heatingRelay->turnOn();
    }
  } else {
  }
}
