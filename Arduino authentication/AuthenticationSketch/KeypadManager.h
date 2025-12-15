#pragma once
#include <DIYables_Keypad.h>
#include "Config.h"
#include "Buzzer.h"

// Forward declaration
class AuthenticationManager;

class KeypadManager {
public:
  DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(KEYS), PIN_ROWS, PIN_COLS, ROW_NUM, COLUMN_NUM);
  String inputPassword = "";
  AuthenticationManager* authManager = nullptr;

  void setup() {
    inputPassword.reserve(32);
  }

  void setAuthenticationManager(AuthenticationManager* auth) {
    authManager = auth;
  }

  void update() {
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
        if (authManager) authManager->PublishAuthenticationResult(true);
      } else {
        Serial.println("Keypad: Incorrect");
        beepFail();
        showError();
        if (authManager) authManager->PublishAuthenticationResult(false);
      }
      inputPassword = "";
    }
    else {
      inputPassword += key;
    }
  }
};