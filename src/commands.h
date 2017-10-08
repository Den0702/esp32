#ifndef COMMANDS_H
#define COMMANDS_H
#include "Arduino.h"
#include "Embedis.h"
const uint8_t EEPROM_SIZE = 64;
void setup_commands();
float getRequestedTankThermometerTemperature();
#endif
