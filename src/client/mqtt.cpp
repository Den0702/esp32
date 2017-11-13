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
      if(client.publish(topic, value, NOTRETAIN, QoS2)){
        LOGGER::DEBUG("Published to: "+ topic + " value: "+ value);
      }else{
        LOGGER::ERROR("Did not publish to: "+ topic + " value: "+ value);
      }
    }
    void publish(String topic, double value){
      if(client.publish(topic, String( value), NOTRETAIN, QoS2)){
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
            if(client.subscribe(SETTING::MQTT::TOPIC())){
              LOGGER::DEBUG("Subscribed to topic: " + SETTING::MQTT::TOPIC());
            }else{
              LOGGER::ERROR("Did not subscribe to topic: " + SETTING::MQTT::TOPIC());
            }
          }else{
            LOGGER::ERROR("Did not conect to mqtt server");
          }
        }
        root["model"] = SETTING::DEVICE::MODEL;
        // root["device"] = SETTING::DEVICE::ID();
        root["firmware_version"] = SETTING::DEVICE::FIRMWARE_VERSION;
        root.set<unsigned long>("timestamp", CLIENT::NTP::getEpochTime());
        root.set<double>("in", DEVICE::THERMOMETER::getIncommingMediumTemperature());
        root.set<double>("out", DEVICE::THERMOMETER::getOutcommingMediumTemperature());
        root.set<double>("inside", DEVICE::THERMOMETER::getTankTemperature());

        String jsonToPublish;
        root.printTo(jsonToPublish);
        publish(SETTING::MQTT::TOPIC(), jsonToPublish);
        lastMillis = millis();
      }
    }
  }
}
