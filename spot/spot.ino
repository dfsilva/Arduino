#include <VirtualWire.h>

const int transmit_pin = 12;
const int receive_pin = 13;

void setup(){
    Serial.begin(9600);
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_setup(2000);
}

void loop(){
    char msg2[80];
    sprintf(msg2, "id:%s,nome:%s,valor:%s,teste:%s", "1","sala","40.32","51");
    
    Serial.println(msg2); 
    vw_send((uint8_t *)msg2, strlen(msg2));
    vw_wait_tx(); 
    free(msg2);
}
