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

      char* message = formatDiscoveryMessageJson(mac_address,  "rfid", "{{ value_json.rfid_authenticated }}", mqttManager.GetRfidStateTopic());
      mqttManager.PublishMessage(message, mqttManager.GetRfidDiscoveryTopic());

      message = formatDiscoveryMessageJson(mac_address, "keypad", "{{ value_json.keypad_authenticated }}", mqttManager.GetKeypadStateTopic());
      mqttManager.PublishMessage(message, mqttManager.GetKeypadDiscoveryTopic());

      Serial.println("Sent discovery message");
    }

  private:
    char* formatDiscoveryMessageJson(char* mac_address, const char* name, const char* templateStr, const char* state_topic) {
      StaticJsonDocument<512> doc;

      doc["name"]           = name;
      doc["unique_id"]      = String(mac_address) + "_" + name; 
      doc["object_id"]      = String(mac_address) + "_" + name; 
      doc["state_topic"]    = state_topic;
      doc["device_class"]   = "lock";
      doc["payload_on"]     = "Authenticated";
      doc["payload_off"]    = "Unauthenticated";

      JsonObject device = doc.createNestedObject("device");
      device["identifiers"] = mac_address;
      device["manufacturer"] = "Arduino";
      device["model"] = "Uno R4 WiFi";
      device["name"] = "Door authentication";

      static char buffer[512];
      serializeJson(doc, buffer);

      return buffer;
    }
};