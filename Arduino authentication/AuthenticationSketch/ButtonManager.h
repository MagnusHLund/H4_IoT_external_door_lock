#pragma once
#include <Arduino.h>
#include "Config.h"

class ButtonManager {
private:
  bool lastButtonState = HIGH;
  unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 50;

public:
  void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
  }

  void update() {
    bool buttonState = digitalRead(BUTTON_PIN);
    
    if (buttonState != lastButtonState) {
      lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (buttonState == LOW) {
        // Button is pressed, turn on blue LED
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
      } else {
        // Button is released, turn off blue LED
        digitalWrite(BLUE_PIN, LOW);
      }
    }
    
    lastButtonState = buttonState;
  }
};