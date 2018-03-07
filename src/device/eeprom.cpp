#include "eeprom.h"
#include <EEPROM.h>
#include "Arduino.h"
#include <Embedis.h>
namespace DEVICE{
  namespace EePROM{
    void setup(){
      if(!EEPROM.begin(SIZE)) {
      }
      Embedis::dictionary(F("EEPROM"), SIZE,
      [](size_t pos) -> char {
        return EEPROM.read(pos);
      },
      [](size_t pos, char value) {
        EEPROM.write(pos, value);
      },
      [](){
        EEPROM.commit();
      });
    };
  }
}
