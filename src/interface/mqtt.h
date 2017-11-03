#ifndef INTERFACE_MQTT_H
#define INTERFACE_MQTT_H
#include "Arduino.h"
void callbackForDemandedInsideTankTemperature(double value);
void logPublication(bool result, double value, String topic);
void logPublication(bool result, bool value, String topic);
void setup_mqtt();
void loop_mqtt();
void publishInsideTankTemperature();
void publishInMediumTemperature();
void publishOutMediumTemperature();
void publishHeatingMediumValve();
void publishCoolingMediumValve();
#endif
