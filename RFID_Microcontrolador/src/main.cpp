#include <MFRC522.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Arduino.h>


#define SDA_pin D4
#define RST_pin D2

HTTPClient http;
WiFiClient cliente;


MFRC522 mfrc522(SDA_pin, RST_pin);

String data1;


void setup() {
  Serial.begin(9600);

  // Iniciar comunicação com o leitor RFID
  // SPI.begin();
  // mfrc522.PCD_Init();
  
  Serial.println("Lendo cartões RFID");

  WiFi.begin("NOME DA REDE WIFI","SENHA DA REDE");

  Serial.println("connecting...");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

}



void loop() {
  
  ///Serial.println(WiFi.localIP());

  http.begin(cliente,"http://10.235.93.245:8080/teste");

  if (http.GET() > 0){
    data1 = http.getString();
    Serial.println(data1);
  }

  /*if (http.GET()){
    http.GET();
    data = http.getString();
    Serial.println(data);
  }*/

  http.end();

  delay(2000);

  /*if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
    Serial.print(F(": Card UID:"));
    for (byte i= 0; i < mfrc522.uid.size; i++){
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0": " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    mfrc522.PICC_HaltA();
  }*/
}






// put function definitions here:
//int myFunction(int x, int y) {
// return x + y;
//}