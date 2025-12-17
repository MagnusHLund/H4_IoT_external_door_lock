#pragma once
#include <Arduino.h>

// ----------------- WIFI -----------------
#define WIFI_SSID "Lab-ZBC"
#define WIFI_PASSWORD "Prestige#PuzzledCASH48!"
#define WIFI_STATIC_IP "10.101.161.52"
#define WIFI_SUBNET_MASK "255.255.0.0"
#define WIFI_GATEWAY "10.101.1.1"
#define WIFI_DNS_SERVER "1.1.1.1"

// ----------------- MQTT -----------------
#define MQTT_HOSTNAME "10.101.161.207"
#define MQTT_PORT 1883
#define MQTT_USERNAME "mqttuser"
#define MQTT_PASSWORD "password"

// ----------------- BUZZER -----------------
#define BUZZER A0

// ----------------- LED -----------------
#define RED_PIN A1
#define GREEN_PIN A2
#define BLUE_PIN A3

// ----------------- BUTTON -----------------
#define BUTTON_PIN A4

// ----------------- KEYPAD -----------------
const int ROW_NUM = 4;
const int COLUMN_NUM = 3;

char KEYS[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte PIN_ROWS[ROW_NUM] = {8, 7, 6, 5};
byte PIN_COLS[COLUMN_NUM] = {4, 3, 2};

const String PASSWORD = "1234";

// ----------------- RFID -----------------
#define RST_PIN 9
#define SS_PIN 10

// Static allowed card (you will replace later)
byte ALLOWED_UID[4] = {0x76, 0x15, 0x2C, 0x6A};

// ----------------- LED FUNCTIONS -----------------
inline void setupLEDs() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  // Turn off all LEDs initially
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

inline void showSuccess() {
  // Turn off red, turn on green
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  delay(2000); // Show green for 2 seconds
  digitalWrite(GREEN_PIN, LOW); // Turn off green
}

inline void showError() {
  // Turn off green, turn on red
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  delay(2000); // Show red for 2 seconds
  digitalWrite(RED_PIN, LOW); // Turn off red
}
