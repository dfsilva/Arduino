#include <dht.h>
#include <IRremote.h>
#include <MideaIR.h>

dht DHT;
#define DHT11_PIN 7
#define IR_EMITER 3

#define SIXT_SECONDS 60000
#define TEN_SECONDS  10000
#define FIVE_SECONDS 5000

#define IDEAL_TEMP 24

int lastTemp = 18;

IRsend irsend;
MideaIR remote_control(&irsend);

void setup(){
  Serial.begin(9600);
  // Define IR PIN as Output
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
   delay(FIVE_SECONDS);
   int chk = DHT.read11(DHT11_PIN);
   double temperature = DHT.temperature;
   Serial.print("Temperature = ");
   Serial.println(temperature);
   double humidity = DHT.humidity;
   Serial.print("Humidity = ");
   Serial.println(humidity);

  if((int)temperature > IDEAL_TEMP){
    if((int)lastTemp > 17){
       lastTemp = lastTemp - 1;
    }
    Serial.print("Setando a temperatura reduzida = ");
    Serial.println(lastTemp);
  }else{
    if((int)lastTemp < 30){
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
