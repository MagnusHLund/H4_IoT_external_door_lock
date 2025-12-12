#include <Arduino.h>
#include "Config.h"
#include "KeypadManager.h"
#include "RFIDManager.h"
#include "ButtonManager.h"

KeypadManager keypadManager;
RFIDManager rfidManager;
ButtonManager buttonManager;

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
  setupLEDs();

  keypadManager.setup();
  rfidManager.setup();
  buttonManager.setup();
}

void loop() {
  keypadManager.update();
  rfidManager.update();
  buttonManager.update();
}
