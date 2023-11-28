#include <Arduino.h>
#include <menu.h>
#include <Network.h>
#include <DateTimeLib.h>
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define API_KEY "AIzaSyB6pacJWFrtRR18HJc7cA7kXxoY6GiH_-8"
#define DATABASE_URL "https://kosabangsa-5ff5d-default-rtdb.firebaseio.com"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

byte mode;

void setup() {
  Serial.begin(115200);
  pinMode(14, INPUT);
  pinMode(12, INPUT);
  WifiSetup("realme C25s", "code787898");
  timeBegin();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  /*
  lcd.begin();
  logo();
  delay(1000);
  lcd.clear();
  TimeValid(14);
  delay(1000);
  menu_mode();
  chose(12,14);
  Serial.print(x);
  */
}
int num = 0;
void loop() {
  num++;
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 100 || sendDataPrevMillis == 0)) {
    Serial.println(num);
    sendDataPrevMillis = millis();
    if (
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(num)+"/Kg", "80")) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(num)+"/Status", "1")) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(num)+"/Tanggal", GetDateTime())) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(num)+"/TanggalPanen", NULL)) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(num)+"/TanggalProses", NULL)) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(num)+"/Type", NULL))
      ) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
    }
    delay(1000);
  }else{
    Serial.println("Firebase Gagal");
  } 
}