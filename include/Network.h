#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

void WifiSetup(const char* ssid){
    WiFiManager wifiManager;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hubungkan Hotspot");
    lcd.setCursor(0,1);
    lcd.print("Ke : " + String(ssid));

    lcd.setCursor(0,2);
    lcd.print("IP : 192.168.4.1");
    wifiManager.autoConnect(ssid);

    lcd.clear();
    lcd.print("Terhung ");
    delay(2000);
    lcd.clear();
    //Serial.println("connected...yeey :)");
}