#pragma once
#include <Arduino.h>
#include "Config.h"

inline void beepSuccess() { tone(BUZZER, 1000, 400); }
inline void beepFail()    { tone(BUZZER, 500, 150); delay(200); tone(BUZZER, 500, 150); }