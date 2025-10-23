#include <Arduino.h>
#define LED 2

int x = 0;

// put function declarations here:
//int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED,LOW);
  delay(2000);
  x++;
  Serial.println(x);
}

// put function definitions here:
//int myFunction(int x, int y) {
// return x + y;
//}