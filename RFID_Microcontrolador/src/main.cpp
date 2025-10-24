#include <MFRC522.h>
#include <SPI.h>
#include <Arduino.h>

#define SDA_pin D4
#define RST_pin D2

MFRC522 mfrc522(SDA_pin, RST_pin);

// put function declarations here:
//int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  Serial.begin(9600);

  SPI.begin();

  mfrc522.PCD_Init();
  

  //pinMode(SDA_pin, OUTPUT);

  Serial.println("Lendo cartões RFID");

}



void loop() {
  // put your main code here, to run repeatedly:

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return; // Não encontrou, sai
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return; // Falha na leitura, sai
  }

  
  Serial.print(F(": Card UID:"));
  for (byte i= 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0": " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  mfrc522.PICC_HaltA();
}





// put function definitions here:
//int myFunction(int x, int y) {
// return x + y;
//}