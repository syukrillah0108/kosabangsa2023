#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 20, 4);

void logo(){
  lcd.backlight();

  lcd.setCursor(2,0);
  lcd.print("KOSABANGSA  2023");
  delay(200);
  lcd.setCursor(1,1);
  lcd.print("KEMENDIKBUDRISTEK");
  delay(200);
  lcd.setCursor(4,2);
  lcd.print ("STT-BANDUNG");
  delay(200);
  lcd.setCursor(1,3);
  lcd.print ("TELKOM  UNIVERSITY");
  delay(4000);
  lcd.clear();
}

void select(byte x){
    if (x==0){
        lcd.setCursor(0,1);
        lcd.print("   ");
        lcd.setCursor(0,0);
        lcd.print("=>");
    } else if (x==1)
    {
        lcd.setCursor(0,0);
        lcd.print("   ");
        lcd.setCursor(0,1);
        lcd.print("=>");
    } else{
        lcd.setCursor(0,0);
        lcd.print("   ");
        lcd.setCursor(0,1);
        lcd.print("   ");
    }
}

void menu_mode(){
    lcd.clear();
    lcd.print("   Manual");
    lcd.setCursor(0,1);
    lcd.print("   Otomatis");
}

byte x=0;
bool active=false;

void chose(const uint8_t pin_slc, const uint8_t pin_sbmt){
  while (true){
  if((digitalRead(pin_slc) == LOW) && active==false){
    Serial.print(x);
    if (x==1){
      x=0;
    } else if (x==0){
      x=1;
    } else{
      x=0;
    }
    select(x);
    active=true;
  } else if (
    (digitalRead(pin_slc) == HIGH) && active==true){
    active=false;
  }

  if(digitalRead(pin_sbmt) == LOW){
    lcd.clear();
    delay(1000);
    //digitalWrite(14,HIGH);
    if(x==0){
      lcd.print("Manual");
    } else if (x==1){
      lcd.print("Otomatis");
    }
    //digitalWrite(14,LOW);
    delay(500);
    break;
  }delay(100);
  }
}