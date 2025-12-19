#include "Config.h"
#include "Button.h"
#include "Light.h"
#include <ArduinoJson.h>
#include "WiFiManager.h"
#include "MqttManager.h"
#include "LockController.h"
#include "Pairing.h"

WiFiManager wiFiManager(WIFI_SSID, WIFI_PASSWORD, WIFI_STATIC_IP, WIFI_GATEWAY, WIFI_SUBNET_MASK, WIFI_DNS_SERVER);
MqttManager mqttManager(MQTT_HOSTNAME, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD, wiFiManager);

Light light(LIGHT_PIN);
Button pairButton(PAIR_BUTTON_PIN);
Pairing pairing(wiFiManager, mqttManager, pairButton, light);

Motor motor(MOTOR_PIN);
LockController lockController(motor, mqttManager);

unsigned long lastCheck = 0;

void setup() {
  Serial.begin(9600);

  wiFiManager.connect();
  mqttManager.connect();

  const char* macAddress = wiFiManager.getMacAddress(true);
  mqttManager.setupTopics(macAddress);

  lockController.init();
  pairing.init();
}

void loop() {
  mqttManager.ensureConnectivity();

  // WiFi can be kept alive left often than MQTT
  if (millis() - lastCheck > 5000) {
    wiFiManager.ensureConnectivity();
    lastCheck = millis();
  }

  pairing.handlePairingButton();
}