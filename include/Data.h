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
float calibration_factor = -31; //Nilai awal perkiraan
float units;

const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void HX_begin(){
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average(); 
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
}

void Firebase_begin(){
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
}
int val = 1;
void Firebase_send(String Kg, String tanggal, String tipe){
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 100 || sendDataPrevMillis == 0)) {
    if (Firebase.RTDB.getInt(&fbdo, "/Data/Jumlah")) {
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
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/Kg", Kg)) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/Status", "1")) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/Tanggal", tanggal)) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/TanggalPanen", "null")) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/TanggalProses", "null")) &&
        (Firebase.RTDB.setString(&fbdo, "Data/"+String(val)+"/Type", tipe)) &&
        (Firebase.RTDB.setInt(&fbdo, "Data/Jumlah", val))
      ) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
    }
    delay(1000);
  }else{
    Serial.println("Firebase Gagal");
  }
}