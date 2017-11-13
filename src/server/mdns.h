#ifndef SERVER_MDNS_H
#define SERVER_MDNS_H
#include "setting.h"
#include <ESPmDNS.h>
#include "log.h"
namespace SERVER{
  namespace mDNS{
    void setup();
    void loop();
  }
}
#endif
