#ifndef SETTING_H
#define SETTING_H
#include "Embedis.h"
namespace SETTING{
  uint SERIAL_BADURATE();
  namespace LOG {
    String LEVEL();
  }
  namespace DEVICE{
    String ID();
  }
  const String WIFI_SSID = "WIFI_SSID";
  const String WIFI_PASSWORD = "WIFI_PASSWORD";
  const String TANK_DEMANDED_TEMPERATURE = "TANK_DEMANDED_TEMPERATURE";
  const String TELNET_PASSWORD = "TELNET_PASSWORD";
  const String MQTT_HOST = "MQTT_HOST";
  const String MQTT_LOGIN = "MQTT_LOGIN";
  const String MQTT_PASSWORD = "MQTT_PASSWORD";
  const String MQTT_PORT = "MQTT_PORT";
  const String MQTT_CLIENT = "MQTT_CLIENT";
  const String MDNS_HOSTNAME = "MDNS_HOSTNAME";
  const String LOG_LEVEL = "LOG_LEVEL";

  namespace WIFI {
    String SSID();
    String PASSWORD();
  }

  namespace TELNET{
    String PASSWORD();
  }

  namespace MDNS{
    String HOSTNAME();
  }
  namespace MQTT{
    String HOST();
    String LOGIN();
    String PASSWORD();
    String CLIENT();
    uint16_t PORT();
    //  const String INSIDE_TANK_PRESSURE_TOPIC  = LOGIN() + "/"  + CLIENTCLIENT() + "/TANK_PRESSURE";
    const String INSIDE_TANK_TEMPERATURE_TOPIC  = DEVICE::ID() + "/INSIDE_TANK_TEMPERATURE";
    const String IN_MEDIUM_TEMPERATURE_TOPIC    =  DEVICE::ID() + "/IN_MEDIUM_TEMPERATURE";
    const String OUT_MEDIUM_TEMPERATURE_TOPIC   = DEVICE::ID() + "/OUT_MEDIUM_TEMPERATURE";
    const String HEATING_MEDIUM_VALVE_TOPIC     = DEVICE::ID() + "/HEATING_MEDIUM_VALVE_STATUS";
    const String COOLING_MEDIUM_VALVE_TOPIC     = DEVICE::ID() + "/COOLING_MEDIUM_VALVE_STATUS";
    const String DEMANDED_INSIDE_TANK_TEMPERATURE_TOPIC = DEVICE::ID() + "/DEMANDED_TANK_TEMPERATURE";
  }

  namespace TANK{
    float DEMANDED_TEMPERATURE();
  }
}
#endif
