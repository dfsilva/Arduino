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
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };


void setup(){
    Serial.begin(9600);
    dht.begin();
    radio.begin();

    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(70);

    radio.enableDynamicPayloads();
    radio.setRetries(15,15);
    radio.setCRCLength(RF24_CRC_16);

    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);  

    radio.startListening();
}

void loop(){
    transmitTemperature();
    delay(1000);
    transmitHumidity();
    delay(1000);
}

void transmitTemperature(){
    float t = dht.readTemperature();
    char temp[10];
    dtostrf(t,6,2,temp);
    char msg[40];
    sprintf(msg, "%d,%s",1,temp);
    //free(temp);
    
    Serial.println(msg); 
    //vw_send((uint8_t *)msg, strlen(msg));
    //vw_wait_tx(); 
    //free(msg);

    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(0,pipes[0]);
    radio.stopListening();
    bool ok = radio.write(&msg,strlen(msg));
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]); 
    radio.startListening(); 
}

void transmitHumidity(){
    float h = dht.readHumidity();
    char temp[10];
    dtostrf(h,6,2,temp);
    char msg[40];
    sprintf(msg, "%d,%s",2,temp);
    //free(temp);
    Serial.println(msg); 
    //vw_send((uint8_t *)msg, strlen(msg));
    //vw_wait_tx(); 
   // free(msg);
    
}
