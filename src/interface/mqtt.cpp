
#include "Arduino.h"
#include "mqtt.h"
#include "../log.h"
#include "setting.h"
#include <WiFi.h>

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include "../devices/thermometer.h"
// #include <WiFiClientSecure.h>
#include <WiFiClient.h>

WiFiClient clientMQTT;
#define AIO_SERVER      "iteam.uek.krakow.pl"
// #define AIO_SERVER      "iothub.pl"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "user"
#define AIO_KEY         "key"
// WiFiClientSecure clientMQTT;
Adafruit_MQTT_Client mqtt(&clientMQTT, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);
//
//  Adafruit_MQTT_Client mqtt(&clientMQTT, "iothub.uek.krakow.pl",
// 1883,"ii", "SETTING::MQTT::LOG::LOGIN().c_str()", "SETTING::MQTT::PASSWORD().c_str()");
//
//

// const char* test_root_ca= \
//      "-----BEGIN CERTIFICATE-----\n" \
//      "MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n" \
//      "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
//      "DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n" \
//      "SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n" \
//      "GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n" \
//      "AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n" \
//      "q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n" \
//      "SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n" \
//      "Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n" \
//      "a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n" \
//      "/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n" \
//      "AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n" \
//      "CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n" \
//      "bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n" \
//      "c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n" \
//      "VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n" \
//      "ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n" \
//      "MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n" \
//      "Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n" \
//      "AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n" \
//      "uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n" \
//      "wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n" \
//      "X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n" \
//      "PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n" \
//      "KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n" \
//      "-----END CERTIFICATE-----\n";

// // You can use x.509 client certificates if you want
// const char* test_client_key = "";   //to verify the client
// const char* test_client_cert = "";  //to verify the client


//
// clientMQTT.setCACert(test_root_ca);
// clientMQTT.setCertificate(test_client_key); // for client verification
// clientMQTT.setPrivateKey(test_client_cert);	// for client verification
//

/**
* @TODO ADD QOS_2 and retain
*/
Adafruit_MQTT_Publish insideTankTemperaturePublisher  = Adafruit_MQTT_Publish(&mqtt, SETTING::MQTT::INSIDE_TANK_TEMPERATURE_TOPIC.c_str(), MQTT_QOS_1 );
Adafruit_MQTT_Publish inMediumTemperaturePublisher    = Adafruit_MQTT_Publish(&mqtt, SETTING::MQTT::IN_MEDIUM_TEMPERATURE_TOPIC.c_str(), MQTT_QOS_1);
Adafruit_MQTT_Publish outMediumTemperaturePublisher   = Adafruit_MQTT_Publish(&mqtt, SETTING::MQTT::OUT_MEDIUM_TEMPERATURE_TOPIC.c_str(), MQTT_QOS_1 );
// Adafruit_MQTT_Publish coolingMediumValvePublisher     = Adafruit_MQTT_Publish(&mqtt, SETTING::MQTT::COOLING_MEDIUM_VALVE_TOPIC.c_str(), MQTT_QOS_1);
// Adafruit_MQTT_Publish heatingMediumValvePublisher     = Adafruit_MQTT_Publish(&mqtt, SETTING::MQTT::HEATING_MEDIUM_VALVE_TOPIC.c_str(), MQTT_QOS_1);
Adafruit_MQTT_Subscribe demandedInsideTankTemperatureSubscriber = Adafruit_MQTT_Subscribe(&mqtt, SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC.c_str(), MQTT_QOS_1);



void callbackForDemandedInsideTankTemperature(double value) {
  Embedis::set(SETTING::TANK_DEMANDED_TEMPERATURE, String(value));
  LOG::LOG("[ INFO ] Recived message from topic:" + SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC + " = " + value);
}

void logPublication(bool result, double value, String topic){
  if(result)
  LOG::LOG("[ DEBUG ] Pulished  value: " + String(value) + " to topic: " + topic);
  else
  LOG::LOG("[ ERROR ] Did not publish value: " + String(value) + " to topic: " + topic);
}

void logPublication(bool result, bool value, String topic){
  if(result)
  LOG::LOG("[ DEBUG ] Published value: " + String(value) + " to topic:" + topic);
  else
  LOG::LOG("[ ERROR ] Did not publish value: " +  String(value) + " to topic: " + topic);
}

bool MQTT_SETUP = false;
void setup_mqtt(){
  if(!WiFi.isConnected()){
    return;
  }
  if(MQTT_SETUP){
    return;
  }

  if (mqtt.subscribe(&demandedInsideTankTemperatureSubscriber) ) {
    demandedInsideTankTemperatureSubscriber.setCallback(callbackForDemandedInsideTankTemperature);
    LOG::LOG("[ DEBUG ] Subscribed to topic: " + SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC);
    MQTT_SETUP = true;
  } else {
    LOG::LOG("[ DEBUG ] Subscription did not suceed to topic:  " + SETTING::MQTT::DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC);
  }
  int error = mqtt.connect();
    LOG::LOG(String(mqtt.connectErrorString(mqtt.connect())));


  if(error != 0){
    LOG::LOG("[ ERROR ] Could not connect to mqtt server");
    return;
  }else{
    LOG::LOG("[ DEBUG ] Connected to mqtt server");

  }
}

uint64_t previousMillis = 0;        // will store last time LED was updated
uint interval = 10000;           // interval at which to blink (milliseconds)
void loop_mqtt(){
  delay(10);
  if(!WiFi.isConnected()){
    return;
  }

  uint64_t currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (mqtt.connected()){
      if(mqtt.ping(1)) {
        publishInsideTankTemperature();
        publishInMediumTemperature();
        publishOutMediumTemperature();
      }else{
        mqtt.disconnect();
        MQTT_SETUP = false;
      }
    }else{
      MQTT_SETUP = false;
      setup_mqtt();
    }
  }
}
