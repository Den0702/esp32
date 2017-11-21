#include <Arduino.h>
#include "mqtt.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <MQTTClient.h>
#include "../log.h"
#include "../setting.h"
#include <Embedis.h>
#include "ntp.h"
#include "../device/thermometer.h"
namespace CLIENT{
  namespace MQTT{
    WiFiClient socket;
    MQTTClient client;
    bool SETUP = false;
    void messageReceived(String &topic, String &payload) {
      Embedis::set(SETTING::EMBEDIS::DEMANDED_TANK_TEMPERATURE, payload);
      LOGGER::DEBUG("Recived message from topic: " + SETTING::MQTT::TOPIC() + " = " + payload);
    }
    void publish(String topic, String value){
      if(client.publish(topic, value, NOT_RETAIN, QoS2)){
        LOGGER::DEBUG("Published to: "+ topic + " value: "+ value);
      }else{
        LOGGER::ERROR("Did not publish to: "+ topic + " value: "+ value);
      }
    }
    void publish(String topic, double value){
      if(client.publish(topic, String( value), NOT_RETAIN, QoS2)){
        LOGGER::DEBUG("Published to: "+ topic + " value: "+ value);
      }else{
        LOGGER::ERROR("Did not publish to: "+ topic + " value: "+ value);
      }
    }
    void setup(){
      if (WiFi.status() != WL_CONNECTED) {
        return;
      }
      if(SETUP){
        return;
      }
      // client.setOptions(60000, true, 60000);
      client.begin(SETTING::MQTT::HOST.c_str(), SETTING::MQTT::PORT, socket);
      client.onMessage(messageReceived);
      SETUP = true;
    }


    unsigned long lastMillis = 0;
    void loop() {
      if (WiFi.status() != WL_CONNECTED) {
        return;
      }
      if(!SETUP){
        setup();
        return;
      }
      StaticJsonBuffer<255> jsonBuffer;
      JsonObject& root = jsonBuffer.createObject();
      client.loop();
      if (millis() - lastMillis > SETTING::MQTT::PUBLISH_INTERVAL) {
        if(!client.connected()){
          if(client.connect(SETTING::MQTT::CLIENT().c_str(),
          SETTING::MQTT::LOGIN().c_str(),
          SETTING::MQTT::PASSWORD().c_str())) {
            LOGGER::DEBUG(F("Connected to mqtt"));
            client.setWill(String(SETTING::MQTT::TOPIC()+"/status").c_str(), "0", RETAIN, QoS2);
            client.publish(SETTING::MQTT::TOPIC()+"/status", "1", RETAIN, QoS2);

            if(client.subscribe(SETTING::MQTT::TOPIC())){
              LOGGER::DEBUG("Subscribed to topic: " + SETTING::MQTT::TOPIC());
            }else{
              LOGGER::ERROR("Did not subscribe to topic: " + SETTING::MQTT::TOPIC());
            }
          }else{
            LOGGER::ERROR("Did not conect to mqtt server");
          }
        }
        root.set<unsigned long>("timestamp", CLIENT::NTP::getEpochTime());
        JsonArray& analogValues = root.createNestedArray("sensors");
        analogValues.add(DEVICE::THERMOMETER::getIncommingMediumTemperature());
        analogValues.add(DEVICE::THERMOMETER::getOutcommingMediumTemperature());
        analogValues.add(DEVICE::THERMOMETER::getTankTemperature());

        String jsonToPublish;
        root.printTo(jsonToPublish);
        publish(SETTING::MQTT::TOPIC()+"/sensors", jsonToPublish);
        lastMillis = millis();
      }
    }
  }
}
