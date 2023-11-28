#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>

// TODO Sampel 2023-12-24 13:20:50
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org");

void timeBegin(){
    timeClient.begin();
    timeClient.setTimeOffset(25200); // Menambahkan 7 jam (7 x 3600 detik)
}

String GetDateTime(){
    timeClient.update();
  
    // Mengambil waktu dari NTPClient
    time_t rawTime = timeClient.getEpochTime();
    //struct tm *timeInfo = localtime(&rawTime);

    String datetime =
            String( year(rawTime)) + "-" +
            String( (month(rawTime) < 10 ? "0" : "") ) + String(month(rawTime)) + "-" +
            String( (day(rawTime) < 10 ? "0" : "") ) + String(day(rawTime)) + " " +
            String( (hour(rawTime) < 10 ? "0" : "") ) + String(hour(rawTime)) + ":" +
            String( (minute(rawTime) < 10 ? "0" : "") ) + String(minute(rawTime)) + ":" +
            String( (second(rawTime) < 10 ? "0" : "") ) + String(second(rawTime));

    return datetime;
}

void TimeValid(const uint8_t Pin){
    while (digitalRead(Pin) == HIGH){
        timeClient.update();
    
        // Mengambil waktu dari NTPClient
        time_t rawTime = timeClient.getEpochTime();
        String Date, Time;
        Time =
            String( (hour(rawTime) < 10 ? "0" : "") ) + String(hour(rawTime)) + ":"
            + String( (minute(rawTime) < 10 ? "0" : "") ) + String(minute(rawTime)) + ":"
            + String( (second(rawTime) < 10 ? "0" : "") ) + String(second(rawTime));
        Date =
            String( (day(rawTime) < 10 ? "0" : "") ) + String(day(rawTime)) + "/"
            + String( (month(rawTime) < 10 ? "0" : "") ) + String(month(rawTime)) + "/"
            + String(year(rawTime));

        lcd.setCursor(0,0);
        lcd.print("Jika Waktu Sesuai");
        lcd.setCursor(0,1);
        lcd.print("Tekan Tombol Merah");
        lcd.setCursor(4,1);
        lcd.print(Date);
        lcd.setCursor(5,2);
        lcd.print(Time);
        delay(100);
        lcd.clear();
  }
}