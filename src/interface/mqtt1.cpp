#include <Arduino.h>
#include "mqtt1.h"
#include <WiFi.h>

#include <MQTTClient.h>
#include "../log.h"
#include "../setting.h"
#include <Embedis.h>
#include "../devices/thermometer.h"

namespace MQTT{
    WiFiClient net;
    MQTTClient client(256);
    bool SETUP = false;
    unsigned long lastMillis = 0;
    void messageReceived(String &topic, String &payload) {
        Embedis::set(SETTING::TANK_DEMANDED_TEMPERATURE, payload);
        LOG::LOG("[ INFO ] Recived message from topic:" + SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC + " = " + payload);
    }
    void publish(String topic, String value){
        if(client.publish(topic, value)){
            LOG::LOG("[ DEBUG ] Published to: "+ topic + " value: "+ value);
        }else{
            LOG::LOG("[ DEBUG ] Did not publish to: "+ topic + " value: "+ value);
        }
    }
    void publish(String topic, double value){
        if(client.publish(topic,String( value))){
            LOG::LOG("Published to:"+ topic + " value: "+ value);
        }else{
            LOG::LOG("Did not publish to: "+ topic + " value: "+ value);
        }
    }

    void setup(){
            if (WiFi.status() != WL_CONNECTED) {
                return;
            }
            if(!SETUP){
                client.setOptions(300, true, 2000);
                client.begin("iteam.uek.krakow.pl", 1883, net);
                client.onMessage(messageReceived);
                SETUP = true;

            }
            if(client.connected()){
                return;
            }
            if(client.connect(SETTING::MQTT::CLIENT().c_str(), "try", "try")) {
                LOG::DEBUG("Connected to mqtt");
                if(client.subscribe(SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC)){
                    LOG::DEBUG("Subscribed to topic:" + SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC);
                }else{
                    LOG::DEBUG("Did not subscribe to topic:" + SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC);
                }
        }
    }
    void loop() {
        if (WiFi.status() != WL_CONNECTED) {
            return;
        }
        client.loop();
        delay(10);  // <- fixes some issues with WiFi stability

        // publish a message roughly every second.
        if (millis() - lastMillis > 10000) {
            lastMillis = millis();
            if (!client.connected()) {
                if(client.unsubscribe(SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC)){
                    LOG::DEBUG("Unsubscribed from topic:" + SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC);
                }else{
                    LOG::DEBUG("Did not unsubscribe from topic:" + SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC);
                }
                if(client.disconnect()){
                    LOG::DEBUG("Disconected from MQTT server");
                }else{
                    LOG::DEBUG("Did not disconect from MQTT server");
                }
                setup();
                // return;
            }
            publish(SETTING::MQTT::IN_MEDIUM_TEMPERATURE_TOPIC, getOutcommingMediumTemperature());
            publish(SETTING::MQTT::INSIDE_TANK_TEMPERATURE_TOPIC, getIncommingMediumTemperature());
            publish( SETTING::MQTT::INSIDE_TANK_TEMPERATURE_TOPIC, getTankTemperature());
        }
    }
}
