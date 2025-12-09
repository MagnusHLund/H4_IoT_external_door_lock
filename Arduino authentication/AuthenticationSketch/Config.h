#pragma once
#include <Arduino.h>

// ----------------- BUZZER -----------------
#define BUZZER A0

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
byte ALLOWED_UID[4] = {0xDE, 0xAD, 0xBE, 0xEF};
