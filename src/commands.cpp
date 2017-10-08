#include "commands.h"
#include <EEPROM.h>
#include "Arduino.h"
#include <Embedis.h>

void setup_commands(){
  if(!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Failed to initialise EEPROM!");
    delay(1000000);
  }
  Embedis::dictionary("EEPROM", EEPROM_SIZE,
    [](size_t pos) -> char { return EEPROM.read(pos); },
    [](size_t pos, char value) { EEPROM.write(pos, value); },
    []() { EEPROM.commit(); }
  );
};

const String TANK_TEMPERATURE = "TANK_TEMPERATURE";
float getRequestedTankThermometerTemperature(){
  String temp;
  if(!Embedis::get(TANK_TEMPERATURE, temp)) {
   return 8;
  }
  return temp.toFloat();
};
