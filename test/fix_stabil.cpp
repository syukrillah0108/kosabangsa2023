#include <Arduino.h>
#include <menu.h>
#include <vector>

bool SemuaSama(const std::vector<int>& array){
    for(size_t i = 1; i < array.size(); i++){
        if (array[i] != array[0]){
            return false;
        }
    }
    return true;

}

std::vector<int> nilai = {1,2,3,4,5};

void setup(){
  Serial.begin(9600);
  lcd.begin();
  logo();
  pinMode(12,INPUT);
}

void loop(){
  if(SemuaSama(nilai)){
    lcd.clear();
    lcd.print("stabil");
    delay(2000);
  }
  lcd.clear();
  nilai.erase(nilai.begin());
  nilai.push_back(digitalRead(12));
  Serial.println(digitalRead(12));
  
  for(int i: nilai){
    lcd.print(i);
  }
  delay(1000);
}