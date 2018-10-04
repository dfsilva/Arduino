#include <IRremote.h>
#include <MideaIR.h>
#include "Si7021.h"

Si7021 si7021;

#define IR_EMITER 3

#define THIRT_SECONDS 30000
#define TEN_SECONDS  10000
#define FIVE_SECONDS 5000

#define IDEAL_TEMP 25

int ultimaTemperaturaSetada = IDEAL_TEMP;
double ultimaTemperaturaMedida = IDEAL_TEMP;

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
  remote_control.setTemperature(ultimaTemperaturaSetada);
  remote_control.emit();
}

void loop(){
 ajustarTemperatura();
}

void ajustarTemperatura(){
   delay(THIRT_SECONDS);
   double humidadeMedida = si7021.measureHumidity();
   Serial.print("Humidade = ");
   Serial.println(humidadeMedida);
   
   double temperaturaMedida = si7021.getTemperatureFromPreviousHumidityMeasurement();
   Serial.print("Temperatura = ");
   Serial.println(temperaturaMedida);

  if((int)temperaturaMedida > IDEAL_TEMP){
      if(temperaturaMedida >= ultimaTemperaturaMedida){
        setarTemperatura(ultimaTemperaturaSetada - 1);
      } 
  }else if((int)temperaturaMedida < IDEAL_TEMP){
      if(temperaturaMedida <= ultimaTemperaturaMedida){
        setarTemperatura(ultimaTemperaturaSetada + 1);
      }
  }

  ultimaTemperaturaMedida = temperaturaMedida;
}

void setarTemperatura(int temp){
 
  if(temp < 17){
    temp = 17;
  }

  if(temp > 30){
    temp = 30;
  }

  Serial.print("Setando a temperatura = ");
  Serial.println(temp);
  
  ultimaTemperaturaSetada = temp;
  remote_control.setMode(mode_cool);
  remote_control.setSpeedFan(fan_speed_1);
  remote_control.setTemperature(temp);
  remote_control.emit();
}
