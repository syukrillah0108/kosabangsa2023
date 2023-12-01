#include <Wire.h>
#include "HX711.h"

#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define API_KEY "AIzaSyB6pacJWFrtRR18HJc7cA7kXxoY6GiH_-8"
#define DATABASE_URL "https://kosabangsa-5ff5d-default-rtdb.firebaseio.com"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

HX711 scale;
float calibration_factor = -28;
float units;

const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void HX_begin(){
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();
}

float HX_data(){
  scale.set_scale(calibration_factor);
  units = scale.get_units();
  return units;
}

void HX_calibration(){
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
    if(temp == '+' || temp == 'a'){
      calibration_factor += 1;
    }
    else if(temp == '-' || temp == 'z'){
      calibration_factor -= 1;
    }
  }
}

void Firebase_begin(const uint8_t Pin){
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    if (Firebase.signUp(&config, &auth, "", "")) {
        Serial.println("ok");
        signupOK = true;
        lcd.clear();  
        lcd.setCursor(0,0);
        lcd.print("Database :");
        lcd.setCursor(0,1);
        lcd.print ("Terhubung");
        delay(2000);
    }
    else {
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Database :");
        lcd.setCursor(0,1);
        lcd.print("Gagal Terhubung");
        lcd.setCursor(0,3);
        lcd.print("Tekan Tombol Merah");
        while (digitalRead(Pin) == HIGH){
          delay(100);
        }
        setup();
    }

    config.token_status_callback = tokenStatusCallback;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}
int val = 1;
void Firebase_send(String Kg, String tanggal, String tipe){
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 100 || sendDataPrevMillis == 0)) {
    if (Firebase.RTDB.getInt(&fbdo, "/Jumlah")) {
      Serial.println("Data retrieved successfully!");
      if(fbdo.dataType() == "int" ) {
        val = fbdo.intData() + 1;
        Serial.println(val);}
    } else {
      Serial.println("Failed to retrieve data.");
      Serial.print("Reason: ");
      Serial.println(fbdo.errorReason());
    }
    sendDataPrevMillis = millis();
    if (
        (Firebase.RTDB.setInt(&fbdo, "Data/"+String(val)+"/id", val)) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/weight", Kg)) &&
        (Firebase.RTDB.setInt(&fbdo, "Data/"+String(val)+"/status", 1)) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/date_start", tanggal)) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/date_process", "null")) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/date_harvest", "null")) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/type", tipe)) &&
        (Firebase.RTDB.setInt(&fbdo, "Data/"+String(val)+"/is_ecoenzym", 0)) &&
        (Firebase.RTDB.setInt(&fbdo, "Data/"+String(val)+"/is_compost", 0)) &&
        (Firebase.RTDB.setInt(&fbdo, "Jumlah", val))
      ) {
      terkirim();
      delay(3000);
    }
    else{
      gagal_terkirim(1);
    }
  }
}

void offline_display(float berat){
  lcd.setCursor(0,0);
  lcd.print("Gram : " + String(berat));
  lcd.setCursor(0,2);
  lcd.print("Kg   : " + String(berat/1000));
}