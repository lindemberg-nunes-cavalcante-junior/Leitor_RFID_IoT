#include <MFRC522.h>

/*#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <MFRC522Hack.h>*/

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

#define SDA_pin D4
#define RST_pin D2

MFRC522 mfrc522(SDA_pin, RST_pin);

//MFRC522DriverPinSimple ss_pin(SDA_pin);

//SPIClass &spiclass = SPI;

//const SPISettings spiSettings = SPISettings(SPI_CLOCK_DIV4,MSBFIRST,SPI_MODE0);

//MFRC522DriverSPI driver{ss_pin, spiclass, spiSettings};

//MFRC522 mfrc522{driver};

//MFRC522Hack mfrc522Hack(mfrc522, true);

HTTPClient http;
WiFiClient cliente;

//String api = "http://192.168.10.135:8080/autenticar";

//MFRC522::MIFARE_Key key;

//const char nome[] = "Lindemberg";
//const int setor = 4;
//byte dadosParaGravar[16];

String token;

//constexpr uint8_t newUid[] = {0xFF, 0xFF, 0xFF, 0xFF};

//MFRC522 mfrc522(SDA_pin, RST_pin);



void setup() {
  Serial.begin(9600);

  SPI.begin();

  mfrc522.PCD_Init();
  Serial.println(mfrc522.PCD_PerformSelfTest() ? "ok" : "Error");
  mfrc522.PCD_Init();
  //MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);

  Serial.println("Agora ligando o RFID...");

  WiFi.begin("Laica-IoT","Laica321");

  Serial.println("connecting...");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());

  //strncpy((char *)dadosParaGravar, nome, 16);
  
  if(mfrc522.PCD_PerformSelfTest()){
    boolean bol = true;
    Serial.println("Conectando a API...");
    while (bol)
    {
      Serial.print(".");
      http.begin(cliente, "http://192.168.10.135:8080/teste");
      if (http.GET() > 0){
        Serial.println(http.getString());
        mfrc522.PCD_Init();
        http.end();
        bol = false;
      }
      delay(500);
    }
  }else{
    Serial.println("Error");
  }

  //http.begin(cliente, api);

  //http.begin(cliente, "http://192.168.10.135:8080/entrar"); //utilizar apenas na versão de envio json, caso for utilizar

}


void loop() {


  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      token += String(mfrc522.uid.uidByte[i], HEX);
    }

    mfrc522.PICC_HaltA();

    http.begin(cliente,"http://192.168.10.135:8080/autenticar");

    http.addHeader("Token",token);

    if (http.GET()>0){
      token = "";
      http.end();
    }
  }
  

  /*if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  if ( mfrc522Hack.MIFARE_SetUid(newUid, (byte)4, key, true) ) {
    Serial.println(F("Wrote new UID to card."));
  }

  mfrc522.PICC_HaltA();
  if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial() ) {
    return;
  }
  
  Serial.println(F("New UID and contents:"));
  MFRC522Debug::PICC_DumpToSerial(mfrc522, Serial, &(mfrc522.uid));

    Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i]);
  }*/
}







// put function definitions here:
//int myFunction(int x, int y) {
// return x + y;
//}