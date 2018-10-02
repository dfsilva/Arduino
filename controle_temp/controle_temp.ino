#include <IRremote.h>
#include <MideaIR.h>
#include "Si7021.h"

Si7021 si7021;

#define IR_EMITER 3

#define SIXT_SECONDS 60000
#define TEN_SECONDS  10000
#define FIVE_SECONDS 5000

#define IDEAL_TEMP 24.00

int lastTemp = IDEAL_TEMP;

IRsend irsend;
MideaIR remote_control(&irsend);

void setup(){
  Serial.begin(9600);
  si7021.begin();

  pinMode(IR_EMITER, OUTPUT);
  
  remote_control.turnON();
  delay(FIVE_SECONDS);
  remote_control.setNoSound();
  delay(FIVE_SECONDS);
  remote_control.setTemperature(lastTemp);
  remote_control.emit();
}

void loop()
{
 checkTemperature();
}

void checkTemperature(){
   delay(SIXT_SECONDS);
   double humidity = si7021.measureHumidity();
   Serial.print("Humidity DH11= ");
   Serial.println(humidity);
   
   double temperature = si7021.getTemperatureFromPreviousHumidityMeasurement();
   Serial.print("Temperature DH11 = ");
   Serial.println(temperature);

  if(temperature > IDEAL_TEMP){
    if(lastTemp > 17){
       lastTemp = lastTemp - 1;
    }
    Serial.print("Setando a temperatura reduzida = ");
    Serial.println(lastTemp);
  }else{
    if(lastTemp < 30){
      lastTemp = lastTemp + 1;
    }
    Serial.print("Setando a temperatura aumentada = ");
    Serial.println(lastTemp);
  }

  remote_control.setMode(mode_cool);
  remote_control.setSpeedFan(fan_speed_1);
  remote_control.setTemperature(lastTemp);
  remote_control.emit();
}
