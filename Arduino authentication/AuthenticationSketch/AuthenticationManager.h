#pragma once
#include <ArduinoJson.h>

class AuthenticationManager {
  static AuthenticationManager* instance;
  MqttManager& mqttManager;

  public:
    AuthenticationManager(MqttManager& mqttManager)
      : mqttManager(mqttManager) {
        instance = this;
      }

  public:
    void publishAuthenticationResult(bool success, bool rfid, bool keypad) {
      char* message = createAuthenticationResultJson(success, rfid, keypad );
      mqttManager.publishMessage(message);
    }

  private:
    char* createAuthenticationResultJson(bool success, bool rfid, bool keypad) {
      StaticJsonDocument<100> doc;

      doc["state_rfid_authenticated"] = success && rfid ? "Authenticated" : "";
      doc["state_keypad_authenticated"] = success && keypad ? "Authenticated" : "";
      doc["state_rfid_unauthenticated"] = !success && rfid ? "Unauthenticated" : "";
      doc["state_keypad_unauthenticated"] = !success && keypad ? "Unauthenticated" : "";
      doc["timestamp"] = millis();

      static char buffer[256];
      serializeJson(doc, buffer);

      return buffer;
    }
};

// To prevent error when compiling
AuthenticationManager* AuthenticationManager::instance = nullptr;