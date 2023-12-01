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
  
  // Pilih mode
  lcd.setCursor(5,0);
  lcd.print("Pilih Mode");
  while (digitalRead(pinSubmit) == HIGH){
    if (online){
      lcd.setCursor(2,2);
      lcd.print("Gunakan Internet");
    }else if (offline){
      lcd.setCursor(3,2);
      lcd.print("Tanpa Internet");
    }
    
    if (digitalRead(pinSelect) == LOW && active == false){
      if (online){
        offline_mode();
      }else if (offline){
        online_mode();
      }
      active = true;
    } else if (digitalRead(pinSelect) == HIGH){
      active = false;
    }
    lcd.setCursor(0,2);
    lcd.print("                   ");
    delay(200);
  }
  if (online){
    WifiSetup("Scale","scalecode");
    timeBegin();
    TimeValid(pinSubmit);
    Test_Firebase();
  }
  HX_begin();
  delay(1000);
}

String berat;

void loop() {
  delay(100);
  if (online){
    berat = String(HX_data()/1000);
    select_jenis(pinSelect);
    tmp_datetime = GetDateTime();
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
        scale.tare();
    }
  }

  else if(offline){
    offline_display(HX_data());

    if(analogRead(pinZero) == LOW){
        scale.tare();
    }
    delay(100);
    if(analogRead(pinZero) == LOW){
        scale.tare();
    }

    delay(100);
    if(analogRead(pinZero) == LOW){
        scale.tare();
    }
  }
}