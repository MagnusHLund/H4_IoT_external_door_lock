#include <EEPROM.h>
#include "Config.h"

class ConfigManager {
  public:
    static void ConfigureEepromValues() {
      Config config;
/*
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

      config.motor_pin = 2;
      config.pair_button_pin = 3; */

      strcpy(config.wifi_ssid, "Lab-ZBC");
      strcpy(config.wifi_password, "Prestige#PuzzledCASH48!");
      strcpy(config.wifi_static_ip, "10.101.161.42");
      strcpy(config.wifi_subnet_mask, "255.255.0.0");
      strcpy(config.wifi_gateway, "10.101.161.207");
      strcpy(config.wifi_dns_server, "1.1.1.1");

      strcpy(config.mqtt_hostname, "10.101.161.207");
      config.mqtt_port = 8883;
      strcpy(config.mqtt_username, "mqttuser");
      strcpy(config.mqtt_password, "password");

      config.motor_pin = 2;
      config.pair_button_pin = 3;

      //SaveConfig(config);
    }

    static void LoadConfig(Config& config) {
      EEPROM.begin();          // no size argument
      EEPROM.get(0, config);   // read struct from address 0
    }
  
  private:
    static void SaveConfig(const Config& config) {
      EEPROM.begin();          // no size argument
      EEPROM.put(0, config);   // write struct at address 0
      // no commit() needed on Uno R4 WiFi
    }
};
