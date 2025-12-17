#pragma once
#include <DIYables_Keypad.h>
#include "Config.h"
#include "Buzzer.h"

// Forward declaration
class AuthenticationManager;

class KeypadManager {
private:
  unsigned long unlockTime = 0;
  bool isUnlocked = false;
  const unsigned long lockDelay = 10000; // 10 seconds

  
  public:
  MqttManager& mqttManager;
  DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(KEYS), PIN_ROWS, PIN_COLS, ROW_NUM, COLUMN_NUM);
  String inputPassword = "";
  AuthenticationManager* authManager = nullptr;

  KeypadManager(MqttManager& mqttManager) : mqttManager(mqttManager) {}

  void setup() {
    inputPassword.reserve(32);
  }

  void setAuthenticationManager(AuthenticationManager* auth) {
    authManager = auth;
  }

  void update() {
    // Check if door should auto-lock after 10 seconds (check this first, always)
    if (isUnlocked && (millis() - unlockTime >= lockDelay)) {
      Serial.println("Keypad: Auto-locking after 10 seconds");
      isUnlocked = false;
      showError(); // Show locked state
      if (authManager) {
        mqttManager.PublishMessage("Unauthenticated", mqttManager.GetKeypadStateTopic());
      }
    }
    
    char key = keypad.getKey();
    if (!key) return;

    Serial.println(key);

    if (key == '*') {
      inputPassword = "";
    }
    else if (key == '#') {
      if (inputPassword == PASSWORD) {
        Serial.println("Keypad: Correct");
        beepSuccess();
        showSuccess();
        isUnlocked = true;
        unlockTime = millis();
        if (authManager) {
          mqttManager.PublishMessage("Authenticated", mqttManager.GetKeypadStateTopic());
        }
      } else {
        Serial.println("Keypad: Incorrect");
        beepFail();
        showError();
        if (authManager) authManager->PublishAuthenticationResult(false, false, true); // do not need
      }
      inputPassword = "";
    }
    else {
      inputPassword += key;
    }
  }
};