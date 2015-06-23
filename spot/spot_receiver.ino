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
   int len = 0;
   char msg[40] = "";
   
   if (radio.available()) {
      bool done = false;
      while ( !done ) {
        len = radio.getDynamicPayloadSize();
        done = radio.read(&msg,len);
        delay(5);
      }


    Serial.println(msg); 
    msg[len] = 0;   
   } 
}

