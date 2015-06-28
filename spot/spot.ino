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

void setup(){
    Serial.begin(57600);
    dht.begin();
    radio.begin();

    emon1.current(1, 111.1);

    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(70);

    radio.enableDynamicPayloads();
    radio.setRetries(15,15);
    radio.setCRCLength(RF24_CRC_16);

    radio.openWritingPipe(pipe_central);
}

void loop(){
    transmitTemperature();
    transmitHumidity();
    transmitEnergy();
    //delay(500);
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
    sprintf(msg, "id:%d,T:hum,value:%s",1,temp);
    Serial.println(msg); 
    bool ok = radio.write(&msg,strlen(msg));
}

void transmitEnergy(){
  double Irms = emon1.calcIrms(1480);
  Serial.print(Irms*230.0);
  Serial.print(" ");
  Serial.println(Irms);  
}

