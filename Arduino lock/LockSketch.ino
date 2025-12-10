#include "ConfigManager.h"
#include "Button.h"
#include <ArduinoJson.h>
#include "WiFiManager.h"
#include "MqttManager.h"
#include "LockController.h"
#include "Pairing.h"

Config config;

// Declare pointers instead of objects
WiFiManager* wiFiManager;
MqttManager* mqttManager;
Button* pairButton;
Pairing* pairing;
Motor* motor;
LockController* lockController;

unsigned long lastCheck = 0;

void setup() {
  Serial.begin(9600);

  // Load data from EEPROM
  ConfigManager::LoadConfig(config);

  // Instantiate classes with EEPROM values
  wiFiManager = new WiFiManager(
    config.wifi_ssid,
    config.wifi_password,
    config.wifi_static_ip,
    config.wifi_gateway,
    config.wifi_subnet_mask,
    config.wifi_dns_server
  );

  mqttManager = new MqttManager(
    config.mqtt_hostname,
    config.mqtt_port,
    config.mqtt_username,
    config.mqtt_password,
    config.ca_certificate
  );

  pairButton = new Button(config.pair_button_pin);
  pairing = new Pairing(*wiFiManager, *mqttManager, *pairButton);

  motor = new Motor(config.motor_pin);
  lockController = new LockController(*motor, *mqttManager);

  // Run setup methods
  wiFiManager->Connect();
  mqttManager->Connect();

  const char* mac_address = wiFiManager->GetMacAddress(true);
  mqttManager->SetupTopics(mac_address);

  lockController->Init();
  pairing->Init();
}

void loop() {
  mqttManager->EnsureConnectivity();

  if (millis() - lastCheck > 5000) {
    wiFiManager->EnsureConnectivity();
    lastCheck = millis();
  }

  pairing->HandlePairingButton();
}
