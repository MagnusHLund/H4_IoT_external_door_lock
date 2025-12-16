#pragma once
#include <MFRC522.h>
#include <SPI.h>
#include "Config.h"
#include "Buzzer.h"

// Forward declaration
class AuthenticationManager;

class RFIDManager {
public:
  MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);
  AuthenticationManager* authManager = nullptr;

  void setup() {
    SPI.begin();
    rfid.PCD_Init();
  }

  void setAuthenticationManager(AuthenticationManager* auth) {
    authManager = auth;
  }

  bool compareUID(byte *uid, byte size) {
    if (size != 4) return false;
    for (byte i = 0; i < 4; i++)
      if (uid[i] != ALLOWED_UID[i]) return false;
    return true;
  }

  void update() {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
      return;

    Serial.print("UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    if (compareUID(rfid.uid.uidByte, rfid.uid.size)) {
      Serial.println("RFID: Card Accepted");
      beepSuccess();
      showSuccess();
      if (authManager) authManager->PublishAuthenticationResult(true, true, false);
    } else {
      Serial.println("RFID: Wrong Card");
      beepFail();
      showError();
      if (authManager) authManager->PublishAuthenticationResult(false, true, false);
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
};