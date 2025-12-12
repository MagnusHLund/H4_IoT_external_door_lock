#pragma once
#include "Include/MqttManager.h"
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
    void PublishAuthenticationResult(bool success) {
      char* message = CreateAuthenticationResultJson(success);
      mqttManager.PublishMessage(message);
    }

  private:
    char* CreateAuthenticationResultJson(bool success) {
      StaticJsonDocument<100> doc;

      doc["authenticated"] = success;
      doc["timestamp"] = millis();

      static char buffer[256];
      serializeJson(doc, buffer);

      return buffer;
    }
};

// To prevent error when compiling
AuthenticationManager* AuthenticationManager::instance = nullptr;