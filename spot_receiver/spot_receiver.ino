#include <SPI.h>
#include "DHT.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

RF24 radio(9,10);

const uint64_t pipe_spot1 = 0xF0F0F0F0E1LL;

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

    radio.openReadingPipe(1,pipe_spot1);  
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
   } 
}

