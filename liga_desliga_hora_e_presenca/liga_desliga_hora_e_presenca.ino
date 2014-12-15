#include <Wire.h>
#include "RTClib.h"

const int mov_sensor_pin = 10;
const int relay_pin = 2;

RTC_DS1307 rtc;

void setup () {
  Serial.begin(9600);
  pinMode(relay_pin, OUTPUT);
  pinMode(mov_sensor_pin, INPUT);
    
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin();
#endif
  rtc.begin();
  //rtc.adjust(DateTime(2014, 14, 12, 17, 18, 0));
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
}

void loop () {
    DateTime now = rtc.now();
    Serial.println(now.hour());
    
    if(now.hour() >= 19 && now.hour() <= 23){
        int pirVal = digitalRead(mov_sensor_pin);
        
        if(pirVal == HIGH){
          digitalWrite(relay_pin, HIGH);
          delay(1800000);
        }else{
          digitalWrite(relay_pin, LOW);
        }
    }else{
      int pirVal = digitalRead(mov_sensor_pin);
      
      if(pirVal == HIGH){
        digitalWrite(relay_pin, HIGH);
        delay(600000);
      }else{
        digitalWrite(relay_pin, LOW);
      }
    }
}
