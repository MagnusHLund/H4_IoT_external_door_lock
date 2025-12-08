#include "Config.h"
#include "WiFiManager.h"
#include "MqttManager.h"
#include "LockManager.h"

WiFiManager wiFiManager(WIFI_SSID, WIFI_PASSWORD, WIFI_STATIC_IP, WIFI_GATEWAY, WIFI_SUBNET_MASK, WIFI_DNS_SERVER);
MqttManager mqttManager(MQTT_HOSTNAME, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD);

Motor motor(MOTOR_PIN);

LockManager lockManager(motor, mqttManager);

unsigned long lastCheck = 0;

void setup() {
  Serial.begin(9600);

  wiFiManager.Connect();
  mqttManager.Connect();

  lockManager.Init();
}

void loop() {
  mqttManager.EnsureConnectivity();

  // WiFi can be kept alive left often than MQTT
  if (millis() - lastCheck > 5000) {
    wiFiManager.EnsureConnectivity();
    lastCheck = millis();
  }
}