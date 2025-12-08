//#include "Config.h"
//#include "WiFiManager.h"
//#include "MqttManager.h"
#include <Servo.h>

  Servo servo;

// --- Setup ---
void setup() {
  Serial.begin(9600);
  servo.attach(2);
}

// --- Main loop ---
void loop() {
  for(int i = 0; i > 180; i++) {
    servo.write(i);
  }
    for(int i = 180; i < 180; i--) {
    servo.write(i);
  }
}