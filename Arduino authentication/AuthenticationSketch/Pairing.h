#pragma once
#include <ArduinoJson.h>

class Pairing {
  WiFiManager& wiFiManager;
  MqttManager& mqttManager;

  public:
    Pairing(WiFiManager& wiFiManager, MqttManager& mqttManager) 
      : wiFiManager(wiFiManager), mqttManager(mqttManager) {}

  public:
    void Init() {
      PairToHomeAssistant();
      // Blink LED 5 times to indicate pairing sent
      for (int i = 0; i < 5; i++) {
        digitalWrite(BLUE_PIN, HIGH);
        delay(125);
        digitalWrite(BLUE_PIN, LOW);
        delay(125);
      }
    }

  public:
    void PairToHomeAssistant() {
      char* mac_address = wiFiManager.GetMacAddress(true);
      char* message = formatDiscoveryMessageJson(mac_address);

      mqttManager.PublishMessage(message, mqttManager.GetDiscoveryTopic());
      Serial.println("Sent discovery message");
    }

  private:
    char* formatDiscoveryMessageJson(char* mac_address) {
      StaticJsonDocument<512> doc;

      const char* command_topic = mqttManager.GetCommandTopic();
      const char* state_topic = mqttManager.GetStateTopic();

      doc["name"]           = "Arduino Authentication";
      doc["unique_id"]      = mac_address; 
      doc["command_topic"]  = command_topic;
      doc["state_topic"]    = state_topic;
      doc["state_rfid_unauthenticated"] = "UNAUTHENTICATED";
      doc["state_keypad_unauthenticated"]   = "UNAUTHENTICATED";
      doc["state_rfid_authenticated"]     = "AUTHENTICATED";
      doc["state_keypad_authenticated"]   = "AUTHENTICATED";

      JsonObject device = doc.createNestedObject("device");
      device["identifiers"] = mac_address;
      device["manufacturer"] = "Arduino";
      device["model"] = "Uno R4 WiFi";

      static char buffer[512];
      serializeJson(doc, buffer);

      return buffer;
    }
};