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
  lcd.setCursor(0,0);
  lcd.print("Database :");
  lcd.setCursor(0,1);
  lcd.print ("Menghubungkan....");

  Firebase_begin();

  if(signupOK == true){
    lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("Database :");
    lcd.setCursor(0,1);
    lcd.print ("Terhubung");
    delay(2000);
  }else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Database :");
    lcd.setCursor(0,1);
    lcd.print ("Gagal Terhubung");
    lcd.setCursor(0,3);
    lcd.print("Tekan Tombol Merah");
    while (digitalRead(pinSubmit) == HIGH){
      delay(100);
    }
    setup();
  }
}

void setup() {
  Serial.begin(115200);
  lcd.begin();
  logo();
  WifiSetup("Smart Scale");
  TimeValid(pinSubmit);
  Test_Firebase();
}
float berat;
String tipe;
void loop() {
  /*
  scale.set_scale(calibration_factor);
  Serial.print("Pembacaan : ");
  units = scale.get_units();
  if (units < 0){
    units = 0.00;
  }
  lcd.print(units);
  Serial.print(units);
  delay(100);
 Serial.print(" calibration_factor: ");
 Serial.println(calibration_factor);
  if(Serial.available()){
 char temp = Serial.read();
 if(temp == '+' || temp == 'a')
 calibration_factor += 1;
 else if(temp == '-' || temp == 'z')
 calibration_factor -= 1;
 }
  */
  // manual
  lcd.setCursor(8,0);
  lcd.print(analogRead(A0));
  lcd.print(" Kg");
  delay(500);
  lcd.clear();
  //Firebase_send("20",GetDateTime());
}