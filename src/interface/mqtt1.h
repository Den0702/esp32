#ifndef INTERFACE_MQTT1_H
#define INTERFACE_MQTT1_H
#include <WiFi.h>
#include <MQTTClient.h>
#include "../log.h"
#include "../setting.h"
#include <Embedis.h>
#include "../devices/thermometer.h"

namespace MQTT{
    void messageReceived(String &topic, String &payload) ;

    void publish(String topic, String value);
    void publish(String topic, double value);

    void setup();
    void loop() ;
}

#endif
