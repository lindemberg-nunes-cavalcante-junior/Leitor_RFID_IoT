//#include <MFRC522.h>

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Arduino.h>

#define SDA_pin D4
#define RST_pin D2


MFRC522DriverPinSimple ss_pin(SDA_pin);

SPIClass &spiclass = SPI;

const SPISettings spiSettings = SPISettings(SPI_CLOCK_DIV4,MSBFIRST,SPI_MODE0);

MFRC522DriverSPI driver{ss_pin, spiclass, spiSettings};

MFRC522 mfrc522{driver};

HTTPClient http;
WiFiClient cliente;

String api = "http://192.168.10.135:8080/autenticar";
String data;
String token;



//MFRC522 mfrc522(SDA_pin, RST_pin);



void setup() {
  Serial.begin(9600);

  //SPI.begin();

  mfrc522.PCD_Init();

  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);

  Serial.println("Agora ligando o RFID...");

  WiFi.begin("Laica-IoT","Laica321");

  Serial.println("connecting...");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());

  http.begin(cliente, api);

  //http.begin(cliente, "http://192.168.10.135:8080/entrar"); //utilizar apenas na versão de envio json, caso for utilizar

}



void loop() {

  if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  mfrc522.PICC_HaltA();

  //Pegando UID
	for (byte i = 0; i < mfrc522.uid.size;i++){
    token += String(mfrc522.uid.uidByte[i]);
  }

  if (token != ""){
    http.addHeader("Token",token);

    if (http.GET()> 0){
      data = http.getString();
      Serial.println(data);
    }
  }
  token = "";
}







// put function definitions here:
//int myFunction(int x, int y) {
// return x + y;
//}