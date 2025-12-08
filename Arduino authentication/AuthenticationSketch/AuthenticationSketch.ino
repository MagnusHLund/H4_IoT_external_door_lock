#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
#define BUZZER A0

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  SPI.begin();
  rfid.PCD_Init();
  pinMode(BUZZER, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // UID
  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Card type
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.print("Card Type: ");
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // SAK
  Serial.print("SAK: ");
  Serial.println(rfid.uid.sak, HEX);

  // Beep
  tone(BUZZER, 1000, 150);
  delay(500);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
