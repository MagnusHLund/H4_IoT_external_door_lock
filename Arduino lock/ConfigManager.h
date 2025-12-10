#include "Config.h"

class ConfigManager {
  public:
    static void ConfigureEepromValues() {
      Config config;
      config.magic = 0xAFEDAFCB;

      strcpy(config.wifi_ssid, "MySSID");
      strcpy(config.wifi_password, "MyPassword");
      strcpy(config.wifi_static_ip, "192.168.1.50");
      strcpy(config.wifi_subnet_mask, "255.255.255.0");
      strcpy(config.wifi_gateway, "192.168.1.1");
      strcpy(config.wifi_dns_server, "1.1.1.1");

      strcpy(config.mqtt_hostname, "192.168.1.100");
      config.mqtt_port = 8883;
      strcpy(config.mqtt_username, "mqttuser");
      strcpy(config.mqtt_password, "mqttpass");

            strcpy(config.ca_certificate, 
       R"EOF(-----BEGIN CERTIFICATE-----
        -----END CERTIFICATE-----)EOF");

      config.motor_pin = 2;
      config.pair_button_pin = 3;

      // Saves config to the EEPROM
      saveConfig(config);
    }

  private:
    static void LoadConfig(Config& config) {
      EEPROM.begin();          // no size argument
      EEPROM.get(0, config);   // read struct from address 0

      if (config.magic != 0xAFEDAFCB) {
        ConfigureEepromValues();
        EEPROM.get(0, config);
      }
    }
  
  private:
    static void SaveConfig(const Config& config) {
      EEPROM.begin();          // no size argument
      EEPROM.put(0, config);   // write struct at address 0
      // no commit() needed on Uno R4 WiFi
    }
};
