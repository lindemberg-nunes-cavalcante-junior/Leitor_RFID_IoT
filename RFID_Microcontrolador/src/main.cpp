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

String api = "http://ip_api:porta/autenticar?";



//MFRC522 mfrc522(SDA_pin, RST_pin);



void setup() {
  Serial.begin(9600);

  //SPI.begin();

  mfrc522.PCD_Init();

  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  
  /*mfrc522.PCD_Init();
  Serial.println(mfrc522.PCD_PerformSelfTest() ? "ok": "ERROR!");
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();*/

  Serial.println("Agora ligando o RFID...");

  WiFi.begin("Laica-IoT","Laica321");

  Serial.println("connecting...");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());
  //http.begin(cliente, "http://192.168.10.135:8080/entrar"); //utilizar apenas na versão de envio json
  

}



void loop() {


  if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
		return;
	}

  MFRC522Debug::PICC_DumpToSerial(mfrc522, Serial, &(mfrc522.uid));



  //String data = String((char*)teste);

  //int date = 1;
  //String data = String(date);
  //data = "Isso é uma string " + data;
  //Serial.println(data);

  //delay(1000);

  //http.begin(cliente,"http://192.168.10.135:8080/");

  /*if (http.GET() > 0){
    data1 = http.getString();
    Serial.println(data1);
  }*/


  /*if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
    for (byte i = 0; i < mfrc522.uid.size;i++){
      api += String(mfrc522.uid.uidByte[i]);
    }

    Serial.println(api);

    mfrc522.PICC_HaltA();

    //http.addHeader("Content-Type","aplication/json");


    //data = "{data:123}";
    //Serial.println(uid[0]);
    //http.POST(data);

    /*if (http.POST(data) == 0){
      String response = http.getString();
      Serial.println(response);
    }*/

  }







// put function definitions here:
//int myFunction(int x, int y) {
// return x + y;
//}