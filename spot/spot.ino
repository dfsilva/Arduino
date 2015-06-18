#include <SPI.h>
#include "DHT.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup(){
    Serial.begin(9600);
    dht.begin();
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
