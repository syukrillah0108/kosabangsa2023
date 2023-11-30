#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org");
String DateTime[2] = {};
String* tmp_datetime;

void timeBegin(){
    timeClient.begin();
    timeClient.setTimeOffset(25200); // Menambahkan 7 jam (7 x 3600 detik)
}

String* GetDateTime(){
    timeClient.update();

    time_t rawTime = timeClient.getEpochTime();
    DateTime[0] = 
            String(year(rawTime)) + "-"
            + String( (month(rawTime) < 10 ? "0" : "") ) + String(month(rawTime)) + "-"
            + String( (day(rawTime) < 10 ? "0" : "") ) + String(day(rawTime));
    DateTime[1] =  
            String( (hour(rawTime) < 10 ? "0" : "") ) + String(hour(rawTime)) + ":"
            + String( (minute(rawTime) < 10 ? "0" : "") ) + String(minute(rawTime)) + ":"
            + String( (second(rawTime) < 10 ? "0" : "") ) + String(second(rawTime)); 

    return DateTime;
}

void TimeValid(const uint8_t Pin){
    while (digitalRead(Pin) == HIGH){
        tmp_datetime = GetDateTime();
        lcd.setCursor(2,0);
        lcd.print("Jika Waktu Benar");
        lcd.setCursor(1,1);
        lcd.print("Tekan Tombol Merah");
        lcd.setCursor(5,2);
        lcd.print(tmp_datetime[0]);
        lcd.setCursor(6,3);
        lcd.print(tmp_datetime[1]);
        delay(200);
  }
}