#pragma once
#include <DIYables_Keypad.h>
#include "Config.h"
#include "Buzzer.h"

class KeypadManager {
public:
  DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(KEYS), PIN_ROWS, PIN_COLS, ROW_NUM, COLUMN_NUM);
  String inputPassword = "";

  void setup() {
    inputPassword.reserve(32);
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
      } else {
        Serial.println("Keypad: Incorrect");
        beepFail();
        showError();
      }
      inputPassword = "";
    }
    else {
      inputPassword += key;
    }
  }
};
