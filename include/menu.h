#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 20, 4);

String tipe = "Organik  ";
bool active = false;

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

void terkirim(){
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Data Berhasil");
  lcd.setCursor(5,2);
  lcd.print("Terkirim");
}

void gagal_terkirim(const uint8_t Pin){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Data Gagal");
  lcd.setCursor(5,1);
  lcd.print("Terkirim");
  lcd.setCursor(0,3);
  lcd.print("Tekan Tombol Merah");
  while (digitalRead(Pin) == HIGH){
    delay(100);
  }
  setup();
}

void select_jenis(const uint8_t Pin){
  if (digitalRead(Pin) == LOW && active == false){
    if (tipe == "Organik  "){
      tipe = "Anorganik";
    }else{
      tipe = "Organik  ";
    }
    active = true;
  } else if (digitalRead(Pin) == HIGH){
    active = false;
  }
}

void timbang(String berat, String tanggal, String waktu, String tipe){
  lcd.setCursor(0,0);
  lcd.print("Tanggal : " + tanggal);
  lcd.setCursor(0,1);
  lcd.print ("Waktu   : " + waktu);
  lcd.setCursor(0,2);
  lcd.print ("Berat   : " + berat);
  lcd.setCursor(0,3);
  lcd.print ("Tipe    : " + tipe);
}