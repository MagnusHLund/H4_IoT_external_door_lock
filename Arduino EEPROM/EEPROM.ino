#include <EEPROM.h>
#include "Config.h"
#include "Secrets.h"

Config config;

void setup() {
  Serial.begin(9600);

  config.magic = 0xAFEDAFCB;

  strcpy(config.wifi_ssid, WIFI_SSID);
  strcpy(config.wifi_password, WIFI_PASSWORD);
  strcpy(config.wifi_static_ip, WIFI_STATIC_IP);
  strcpy(config.wifi_subnet_mask, WIFI_SUBNET_MASK);
  strcpy(config.wifi_gateway, WIFI_GATEWAY);
  strcpy(config.wifi_dns_server, WIFI_DNS_SERVER);

  strcpy(config.mqtt_hostname, MQTT_HOSTNAME);
  config.mqtt_port = MQTT_PORT;
  strcpy(config.mqtt_username, MQTT_USERNAME);
  strcpy(config.mqtt_password, MQTT_PASSWORD);

  strcpy(config.ca_certificate, CA_CERTIFICATE);
  strcpy(config.client_certificate, CLIENT_CERTIFICATE);
  strcpy(config.client_key, PRIVATE_KEY);
    
  config.motor_pin = MOTOR_PIN;
  config.pair_button_pin = PAIR_BUTTON_PIN;

  // Write once to EEPROM
  EEPROM.begin();
  EEPROM.put(0, config);

  Serial.println("Provisioning complete. Config saved to EEPROM.");
}

void loop() {
  Serial.println("Remove device!");
  delay(10000);
}
