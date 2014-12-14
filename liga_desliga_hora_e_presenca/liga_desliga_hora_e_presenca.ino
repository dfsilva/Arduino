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
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();
  //rtc.adjust(DateTime(2014, 12, 12, 22, 0, 0));
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
}

void loop () {
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');1
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    if(now.hour() >= 19 && now.hour() <=23){
      digitalWrite(relay_pin, HIGH);
      delay(60000);
    }else{
      int pirVal = digitalRead(mov_sensor_pin);
      if(pirVal == HIGH){
        digitalWrite(relay_pin, HIGH);
        delay(60000);
      }else{
        digitalWrite(relay_pin, LOW);
      }
    }
}
