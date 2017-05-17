#include "MFRC522.h"

MFRC522 rfid(10, 9);
MFRC522::MIFARE_Key key;

int LED_Green = 2;
int LED_Red = 3;
int scanStateFlag = 0;

#define RFID_AccessCards 1
String RFID_Correct[RFID_AccessCards] = {"2c:d7:c3:a5"};
unsigned long RFID_ScanTime;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Red, OUTPUT);
  digitalWrite(LED_Green,HIGH);
  digitalWrite(LED_Red,HIGH);
}

void loop() {
  processStateFlag();
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }else {
    String strID = "";
    for (byte i = 0; i < 4; i++) {
      strID += (rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX) + (i!=3 ? ":" : "");
    }
    for(int i = 0; i < RFID_AccessCards; i++) {
      int found = 0;
      if (strID == RFID_Correct[i]) {
        scanStateFlag = 1;
        found = 1;
      }
      if (found == 0) {
         scanStateFlag = 2;
      }
    }
    RFID_ScanTime = millis(); //12000
    Serial.print("Card key: ");
    Serial.println(strID);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

void processStateFlag() {
  if(scanStateFlag == 1) {
      if(millis() - RFID_ScanTime < 2000) {
        digitalWrite(LED_Red,HIGH);
        digitalWrite(LED_Green,LOW);
      }else {
        digitalWrite(LED_Green,HIGH);
        scanStateFlag = 0;
      }
  }else if(scanStateFlag == 2) {
      if(millis() - RFID_ScanTime < 2000) {
        digitalWrite(LED_Green,HIGH);
        digitalWrite(LED_Red,LOW);
      }else {
        digitalWrite(LED_Red,HIGH);
        scanStateFlag = 0;
      }    
  }else {
    
  }
}

