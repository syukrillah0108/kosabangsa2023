#include <Arduino.h>
#include <menu.h>
#include <Network.h>
#include <DateTimeLib.h>
#include <Data.h>

#define pinSubmit 1
#define pinSelect 3
#define pinZero 2

void Test_Firebase(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Database :");
  lcd.setCursor(0,1);
  lcd.print ("Menghubungkan....");

  Firebase_begin(pinSubmit);
}

void setup() {
  Serial.begin(115200);
  pinMode(pinSubmit, INPUT);
  pinMode(pinZero, INPUT);
  pinMode(pinSelect, INPUT);
  lcd.begin();
  logo();
  WifiSetup("Scale","scalecode");
  timeBegin();
  TimeValid(pinSubmit);
  Test_Firebase();
  HX_begin();
  delay(1000);
}
String berat;
void loop() {
  delay(100);
  select_jenis(pinSelect);
  tmp_datetime = GetDateTime();
  berat = String(HX_data()/1000);
  lcd.setCursor(11,2);
  lcd.print ("         ");
  timbang(berat + " Kg", tmp_datetime[0], tmp_datetime[1], tipe);
  delay(100);
  
  if(analogRead(pinSubmit) == LOW){
    Firebase_send(berat, tmp_datetime[0]+" "+ tmp_datetime[1], tipe);
  }
  if(analogRead(pinZero) == LOW){
      scale.tare();;
  }
  
  delay(100);
  if(analogRead(pinSubmit) == LOW){
    Firebase_send(berat, tmp_datetime[0]+" "+ tmp_datetime[1], tipe);
  }
  if(analogRead(pinZero) == LOW){
      scale.tare();;
  }

  delay(100);
  if(analogRead(pinSubmit) == LOW){
    Firebase_send(berat, tmp_datetime[0]+" "+ tmp_datetime[1], tipe);
  }
  if(analogRead(pinZero) == LOW){
      scale.tare();;
  }
}