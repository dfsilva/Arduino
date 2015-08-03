#include <SPI.h>
#include "DHT.h"
#include "nRF24L01.h"
#include "EmonLib.h"  
#include "RF24.h"
#include "printf.h"

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

RF24 radio(9,10);

//Topology
const uint64_t pipe_central =  0xF0F0F0F0E1LL;

EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;

const int PIR_PIN = 5;
const int DOOR_PIN = 0;
const int GAS_PIN = A2;

unsigned long lastDoorChange = 0;
int isPortaAberta = 0;

void setup(){
    Serial.begin(57600);
    dht.begin();
    radio.begin();

    emon1.current(1, 55.3);
    emon2.current(3, 55.3);
    emon3.current(4, 55.3);

    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(70);

    radio.enableDynamicPayloads();
    radio.setRetries(15,15);
    radio.setCRCLength(RF24_CRC_16);

    radio.openWritingPipe(pipe_central);

    pinMode(PIR_PIN, INPUT);
    pinMode(GAS_PIN, INPUT);
    attachInterrupt(DOOR_PIN, portaAberta, CHANGE); 
}

void loop(){
    transmitTemperature();
    transmitHumidity();
    transmitEnergy1();
    transmitEnergy2();
    transmitEnergy3();
    transmitPresence();
    transmitirPorta();
    transmitirFumaca();
    delay(100);
}

void transmitTemperature(){
    float t = dht.readTemperature();
    char temp[10];
    dtostrf(t,6,2,temp);
    char msg[40];
    sprintf(msg, "id:%d,T:temp,value:%s",1,temp);
    Serial.println(msg); 
    bool ok = radio.write(&msg,strlen(msg));
}

void transmitHumidity(){
    float h = dht.readHumidity();
    char temp[10];
    dtostrf(h,6,2,temp);
    char msg[40];
    sprintf(msg, "id:%d,T:hum,value:%s",2,temp);
    Serial.println(msg); 
    bool ok = radio.write(&msg,strlen(msg));
}

void transmitEnergy1(){
  double irms = emon1.calcIrms(1480);
  char msg[40];
  char ampTemp[6];
  dtostrf(irms, 4, 2, ampTemp);
  sprintf(msg, "id:%d,T:amp1,value:%s",4,ampTemp);
  
  Serial.println(msg); 
  bool ok = radio.write(&msg,strlen(msg));
}

void transmitEnergy2(){
  double irms = emon2.calcIrms(1480);
  char msg[40];
  char ampTemp[6];
  dtostrf(irms, 4, 2, ampTemp);
  sprintf(msg, "id:%d,T:amp2,value:%s",5,ampTemp);
  
  Serial.println(msg); 
  bool ok = radio.write(&msg,strlen(msg));
}

void transmitEnergy3(){
  double irms = emon3.calcIrms(1480);
  char msg[40];
  char ampTemp[6];
  dtostrf(irms, 4, 2, ampTemp);
  sprintf(msg, "id:%d,T:amp3,value:%s",6,ampTemp);
  
  Serial.println(msg); 
  bool ok = radio.write(&msg,strlen(msg));
}

void transmitPresence(){
  int pirVal = digitalRead(PIR_PIN);
  char msg[40];
  sprintf(msg, "id:%d,T:pre,value:%d",7,pirVal);
  Serial.println(msg); 
  bool ok = radio.write(&msg,strlen(msg));
}

void transmitirPorta(){
    char msg[40];
    sprintf(msg, "id:%d,T:por,value:%d",8,isPortaAberta);
    Serial.println(msg); 
    bool ok = radio.write(&msg,strlen(msg)); 
    if(isPortaAberta == 1){
      isPortaAberta = 0;
    }   
}

void transmitirFumaca(){
    int valorFumaca = analogRead(GAS_PIN);
    char msg[40];
    sprintf(msg, "id:%d,T:fum,value:%d",3,valorFumaca);
    Serial.println(msg); 
    bool ok = radio.write(&msg,strlen(msg)); 
}

void portaAberta(){
  long now = millis();

  if((now - lastDoorChange) > 2000){
    isPortaAberta = 1;
    lastDoorChange = millis();
  }
}






