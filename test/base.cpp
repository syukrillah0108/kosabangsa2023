#include <Arduino.h>
#include <menu.h>
#include <Network.h>
#include <DateTimeLib.h>

const uint8_t Pinzero = 13, Pinselect = 12, Pinsubmit = 14;

void setup() {
  Serial.begin(9600);
  pinMode(Pinsubmit, INPUT);
  pinMode(Pinselect, INPUT);
  lcd.begin();
  //logo();
  /*
  WifiSetup();
  timeBegin();
  TimeValid(Pinsubmit);
  while (digitalRead(Pinsubmit) == HIGH){
    delay(100);
  }
  */
  lcd.clear();
  lcd.print("Pilih Menu");
  delay(2000);
  lcd.clear();
  menu2();
  chose2(Pinselect,Pinsubmit);
}

void loop() {
  //lcd.print("Start");
  Serial.println(digitalRead(Pinsubmit));
  delay(1000);
}
