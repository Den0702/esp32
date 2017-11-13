#ifndef LOGGER_H
#define LOGGER_H
#include "Arduino.h"
namespace LOGGER{
  namespace LEVEL{
        const uint8_t ERROR = 0;
        // const uint8_t INFO = 2;
        const uint8_t DEBUG = 1;
    }
  void LOG(const String& message);
  void DEBUG(const String& message);
  void ERROR(const String& message);
}
#endif
