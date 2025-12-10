#include "Config.h"
#include "Button.h"
#include "WiFiManager.h"
#include "MqttManager.h"
#include "LockController.h"
#include "Pairing.h"

WiFiManager wiFiManager(WIFI_SSID, WIFI_PASSWORD, WIFI_STATIC_IP, WIFI_GATEWAY, WIFI_SUBNET_MASK, WIFI_DNS_SERVER);
MqttManager mqttManager(MQTT_HOSTNAME, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD);

Button pairButton(PAIR_BUTTON_PIN);
Pairing pairing(wiFiManager, mqttManager, pairButton);

Motor motor(MOTOR_PIN);
LockController lockController(motor, mqttManager);

unsigned long lastCheck = 0;

void setup() {
  Serial.begin(9600);

  wiFiManager.Connect();
  mqttManager.Connect();

  const char* mac_address = wiFiManager.GetMacAddress(true);
  mqttManager.SetupTopics(mac_address);

  lockController.Init();
  pairing.Init();
}

void loop() {
  mqttManager.EnsureConnectivity();

  // WiFi can be kept alive left often than MQTT
  if (millis() - lastCheck > 5000) {
    wiFiManager.EnsureConnectivity();
    lastCheck = millis();
  }

  pairing.HandlePairingButton();
}