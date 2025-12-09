#include <Arduino.h>
#include "Config.h"
#include "KeypadManager.h"
#include "RFIDManager.h"

KeypadManager keypadManager;
RFIDManager rfidManager;

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);

  keypadManager.setup();
  rfidManager.setup();
}

void loop() {
  keypadManager.update();
  rfidManager.update();
}
