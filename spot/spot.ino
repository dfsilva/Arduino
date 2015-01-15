#include <VirtualWire.h>
#include "DHT.h"

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int transmit_pin = 12;
const int receive_pin = 13;

void setup(){
    Serial.begin(9600);
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_setup(2000); 
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
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); 
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
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); 
   // free(msg);
    
}
