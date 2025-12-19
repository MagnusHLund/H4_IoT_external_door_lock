#include <Arduino.h>
#include "Config.h"
#include <ArduinoJson.h>
#include "WiFiManager.h"
#include "MqttManager.h"
#include "AuthenticationManager.h"
#include "Pairing.h"
#include "KeypadManager.h"
#include "RFIDManager.h"
#include "ButtonManager.h"

WiFiManager wiFiManager(WIFI_SSID, WIFI_PASSWORD, WIFI_STATIC_IP, WIFI_GATEWAY, WIFI_SUBNET_MASK, WIFI_DNS_SERVER);
MqttManager mqttManager(MQTT_HOSTNAME, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD, wiFiManager);

AuthenticationManager authenticationManager(mqttManager);
Pairing pairing(wiFiManager, mqttManager);

KeypadManager keypadManager(mqttManager);
RFIDManager rfidManager(mqttManager);
ButtonManager buttonManager;

unsigned long lastCheck = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  setupLEDs();

  wiFiManager.connect();
  mqttManager.connect();

  const char* macAddress = wiFiManager.getMacAddress(true);
  mqttManager.setupTopics(macAddress);

  keypadManager.setup();
  rfidManager.setup();
  buttonManager.setup();

  // Link authentication manager to keypad and rfid managers
  keypadManager.setAuthenticationManager(&authenticationManager);
  rfidManager.setAuthenticationManager(&authenticationManager);
  
  // Link pairing manager to button manager
  buttonManager.setPairingManager(&pairing);
  
  // Initialize pairing (sends initial discovery message)
  pairing.init();
}

void loop() {
  mqttManager.ensureConnectivity();

  // WiFi can be kept alive less often than MQTT
  if (millis() - lastCheck > 5000) {
    wiFiManager.ensureConnectivity();
    lastCheck = millis();
  }

  keypadManager.update();
  rfidManager.update();
  buttonManager.update();
}