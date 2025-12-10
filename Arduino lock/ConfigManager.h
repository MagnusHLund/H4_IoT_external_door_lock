#include "Config.h"
#include <EEPROM.h>

class ConfigManager {
  public:
    static void LoadConfig(Config& config) {
      EEPROM.begin();          // no size argument
      EEPROM.get(0, config);   // read struct from address 0

      if (config.magic != 0xAFEDAFCB) {
        EEPROM.get(0, config);
      }
    }
};
