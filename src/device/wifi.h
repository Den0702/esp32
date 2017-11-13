#ifndef INTERFACE_WIFI_H
#define INTERFACE_WIFI_H
#include <WiFi.h>
namespace DEVICE{
  namespace WIFI{
    void setup();
    void event(WiFiEvent_t event);
  }
}
#endif
