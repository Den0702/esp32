#ifndef CLIENT_MQTT_H
#define CLIENT_MQTT_H
#include "Arduino.h"
namespace CLIENT{
  namespace MQTT{
    const uint8_t NOT_RETAIN = false;
    const uint8_t RETAIN = true;
    const uint8_t QoS2 = 2;
    const uint8_t QoS1 = 1;
    const uint8_t QoS0 = 0;
    void messageReceived(String &topic, String &payload) ;
    void publish(String topic, String value);
    void publish(String topic, double value);
    void setup();
    void loop() ;
    void x();
  }
}
#endif
