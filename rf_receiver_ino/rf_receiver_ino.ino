#include <VirtualWire.h>

const int led_rec_pin = 13;
//const int transmit_pin = 12;
const int receive_pin = 11;
//const int transmit_en_pin = 3;
const int relay_amp_pin = 10;


char received[20];
void setup() {
    Serial.begin(9600);
    //vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_setup(2000);
    vw_rx_start();
    pinMode(led_rec_pin, OUTPUT);
    pinMode(relay_amp_pin, OUTPUT);
}

void loop() {
    
    uint8_t buflen = 20;
    uint8_t buf[buflen];
 
    if (vw_get_message(buf, &buflen)){
        digitalWrite(led_rec_pin, HIGH);
        for (int i = 0; i < buflen; i++){
	    received[i]=buf[i];
	}
        Serial.println(received);       
        digitalWrite(led_rec_pin, LOW);
    }
    
    //digitalWrite(relay_amp_pin, HIGH);
    //delay(5000);
    //digitalWrite(relay_amp_pin, LOW);
   // delay(5000);
}
