#include "eeprom.h"
#include <EEPROM.h>
#include "Arduino.h"
#include "log.h"
#include <Embedis.h>

void setup_eeprom(){
  if(!EEPROM.begin(EEPROM_SIZE)) {
    LOG::ERROR("Failed to initialise EEPROM!");
    delay(1000000);
  }

  Embedis::dictionary(F("EEPROM"), EEPROM_SIZE,
    [](size_t pos) -> char { return EEPROM.read(pos); },
    [](size_t pos, char value) { EEPROM.write(pos, value); },
    []() { EEPROM.commit(); }
  );
};
