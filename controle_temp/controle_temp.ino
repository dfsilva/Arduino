#include <IRremote.h>
#include <MideaIR.h>
#include "Si7021.h"

Si7021 si7021;

#define IR_EMITER 3
#define FIVE_SECONDS 5000

#define MIN_TEMP 26.30
#define MAX_TEMP 26.90

#define TEMP_UP 28
#define TEMP_MANTAIN 26
#define TEMP_DOWN 24

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
  remote_control.setTemperature(TEMP_MANTAIN);
  remote_control.emit();
  delay(FIVE_SECONDS);
}

void loop(){
 ajustarTemperatura();
}

void ajustarTemperatura(){
  double humidadeMedida = si7021.measureHumidity();
  double temperaturaMedida = si7021.getTemperatureFromPreviousHumidityMeasurement();

  Serial.print("Temperatura Medida: ");
  Serial.println(temperaturaMedida);

  if(temperaturaMedida >= MAX_TEMP){
    setarTemperatura(TEMP_DOWN);
  }else if(temperaturaMedida <= MIN_TEMP){
    setarTemperatura(TEMP_UP);
  }else{
    setarTemperatura(TEMP_MANTAIN);
  }
  
  delay(FIVE_SECONDS);
}

void setarTemperatura(int temp){
    if(temp < 17){
      temp = 17;
    } else if(temp > 30){
      temp = 30;
    }
  
    Serial.print("Setando Temperatura: ");
    Serial.println(temp);

    remote_control.setTemperature(temp);
    remote_control.emit();
}
