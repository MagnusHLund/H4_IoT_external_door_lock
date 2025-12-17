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
  bool fiveSecondReached = false;
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
        fiveSecondReached = false;
      }
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (buttonState == LOW) {
        unsigned long holdDuration = millis() - buttonPressStartTime;
        
        // Check if 5 seconds have been reached
        if (!fiveSecondReached && holdDuration >= holdTime) {
          Serial.println("Button held for 5 seconds - LED will turn GREEN, you can release now!");
          fiveSecondReached = true;
        }
        
        // Handle LED color change after 5 seconds
        if (fiveSecondReached) {
          // Change to GREEN LED after 5 seconds (instead of blinking)
          digitalWrite(RED_PIN, LOW);
          digitalWrite(GREEN_PIN, HIGH); // Green indicates ready to release
          digitalWrite(BLUE_PIN, LOW);
          
          // Trigger pairing only once after 5 seconds
          if (!buttonHoldHandled) {
            if (pairingManager) {
              Serial.println("LED turned GREEN - Triggering pairing - button can be released");
              pairingManager->pairToHomeAssistant();
              buttonHoldHandled = true; // Prevent multiple triggers
            }
          }
        } else {
          // Normal blue LED on while pressing (before 5 seconds)
          digitalWrite(RED_PIN, LOW);
          digitalWrite(GREEN_PIN, LOW);
          digitalWrite(BLUE_PIN, HIGH);
        }
      } else {
        // Button is released, turn off all LEDs and reset states
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        buttonHoldHandled = false;
        fiveSecondReached = false;
      }
    }
    
    lastButtonState = buttonState;
  }
};