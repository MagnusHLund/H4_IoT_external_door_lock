#include <SoftwareSerial.h>

// ESP32-CAM connection pins
SoftwareSerial esp32Serial(A1, A2); // RX=A1, TX=A2

void setup() {
  // Start main serial for debugging
  Serial.begin(115200);
  
  // Start ESP32-CAM communication
  esp32Serial.begin(9600);
  
  Serial.println("=== ESP32-CAM Connection Test ===");
  Serial.println("Wiring:");
  Serial.println("ESP32 5V -> Arduino 5V");
  Serial.println("ESP32 GND -> Arduino GND");
  Serial.println("ESP32 U0T -> Arduino A1");
  Serial.println("ESP32 U0R -> Arduino A2");
  Serial.println("");
  Serial.println("Testing connection...");
}

void loop() {
  // Send test message to ESP32-CAM
  Serial.println("Sending: HELLO");
  esp32Serial.println("HELLO");
  
  // Wait for response
  delay(1000);
  
  // Check if ESP32-CAM responded
  if (esp32Serial.available()) {
    String response = esp32Serial.readString();
    response.trim();
    Serial.println("ESP32-CAM Response: " + response);
  } else {
    Serial.println("No response from ESP32-CAM");
  }
  
  Serial.println("---");
  delay(3000); // Wait 3 seconds before next test
}