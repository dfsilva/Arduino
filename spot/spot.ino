#include <SPI.h>
#include "DHT.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

RF24 radio(9,10);

//Topology
const uint64_t pipe_central =  0xF0F0F0F0E1LL;

void setup(){
    Serial.begin(57600);
    dht.begin();
    radio.begin();

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
    delay(500);
    transmitHumidity();
    delay(500);
}

void transmitTemperature(){
    //radio.stopListening();
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
    //free(temp);
    Serial.println(msg); 
    bool ok = radio.write(&msg,strlen(msg));
    //vw_send((uint8_t *)msg, strlen(msg));
    //vw_wait_tx(); 
   // free(msg);
    
}
