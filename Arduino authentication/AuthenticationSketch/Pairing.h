#pragma once
#include <ArduinoJson.h>

class Pairing {
  WiFiManager& wiFiManager;
  MqttManager& mqttManager;

  public:
    Pairing(WiFiManager& wiFiManager, MqttManager& mqttManager) 
      : wiFiManager(wiFiManager), mqttManager(mqttManager) {}

  public:
    void init() {
      pairToHomeAssistant();
      // Blink LED 5 times to indicate pairing sent
      for (int i = 0; i < 5; i++) {
        digitalWrite(BLUE_PIN, HIGH);
        delay(125);
        digitalWrite(BLUE_PIN, LOW);
        delay(125);
      }
    }

  public:
    void pairToHomeAssistant() {
      char* macAddress = wiFiManager.getMacAddress(true);

      char* message = formatDiscoveryMessageJson(macAddress,  "rfid", "{{ value_json.rfid_authenticated }}", mqttManager.getRfidStateTopic());
      mqttManager.publishMessage(message, mqttManager.getRfidDiscoveryTopic());

      message = formatDiscoveryMessageJson(macAddress, "keypad", "{{ value_json.keypad_authenticated }}", mqttManager.getKeypadStateTopic());
      mqttManager.publishMessage(message, mqttManager.getKeypadDiscoveryTopic());

      Serial.println("Sent discovery message");
    }

  private:
    char* formatDiscoveryMessageJson(char* macAddress, const char* name, const char* templateStr, const char* stateTopic) {
      StaticJsonDocument<512> doc;

      doc["name"]           = name;
      doc["unique_id"]      = String(macAddress) + "_" + name; 
      doc["object_id"]      = String(macAddress) + "_" + name; 
      doc["state_topic"]    = stateTopic;
      doc["device_class"]   = "lock";
      doc["payload_on"]     = "Authenticated";
      doc["payload_off"]    = "Unauthenticated";

      JsonObject device = doc.createNestedObject("device");
      device["identifiers"] = macAddress;
      device["manufacturer"] = "Arduino";
      device["model"] = "Uno R4 WiFi";
      device["name"] = "Door authentication";

      static char buffer[512];
      serializeJson(doc, buffer);

      return buffer;
    }
};