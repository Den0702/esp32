#ifndef LOG_H
#define LOG_H
#include "Arduino.h"
namespace LOG{
  void LOG(const String& message);
  void DEBUG(const String& message);
  void ERROR(const String& message);
}
#endif
