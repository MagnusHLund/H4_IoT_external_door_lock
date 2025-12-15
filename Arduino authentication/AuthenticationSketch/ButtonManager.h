#pragma once
#include <Arduino.h>
#include "Config.h"

// Forward declaration
class Pairing;

class ButtonManager {
private:
  bool lastButtonState = HIGH;
  unsigned long lastDebounceTime = 0;
  unsigned long buttonPressStartTime = 0;
  bool buttonHoldHandled = false;
  const unsigned long debounceDelay = 50;
  const unsigned long holdTime = 5000; // 5 seconds for pairing
  
  Pairing* pairingManager = nullptr;

public:
  void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
  }

  void setPairingManager(Pairing* pairing) {
    pairingManager = pairing;
  }

  void update() {
    bool buttonState = digitalRead(BUTTON_PIN);
    
    if (buttonState != lastButtonState) {
      lastDebounceTime = millis();
      
      // Button just pressed (LOW)
      if (buttonState == LOW) {
        buttonPressStartTime = millis();
        buttonHoldHandled = false;
      }
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (buttonState == LOW) {
        // Button is pressed, turn on blue LED
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        
        // Check for 5-second hold for pairing
        if (!buttonHoldHandled && (millis() - buttonPressStartTime) >= holdTime) {
          if (pairingManager) {
            Serial.println("Button held for 5 seconds - triggering pairing");
            pairingManager->PairToHomeAssistant();
            buttonHoldHandled = true; // Prevent multiple triggers
          }
        }
      } else {
        // Button is released, turn off blue LED
        digitalWrite(BLUE_PIN, LOW);
        buttonHoldHandled = false; // Reset for next press
      }
    }
    
    lastButtonState = buttonState;
  }
};