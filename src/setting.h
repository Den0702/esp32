#ifndef SETTING_H
#define SETTING_H
#include "Embedis.h"
#include "Arduino.h"
namespace SETTING{

  const uint SERIAL_BADURATE = 112500;
  namespace LOG{
    uint8_t LEVEL();
  }
  namespace EMBEDIS{
  }
  namespace DEVICE{
    const uint MODEL = 0;
    const uint FIRMWARE_VERSION = 0;
    String ID();
  }
}
#endif
