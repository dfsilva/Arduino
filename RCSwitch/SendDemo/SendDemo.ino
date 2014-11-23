/*
  Example for different sending methods
  
  http://code.google.com/p/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
const int led_pin = 11;

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(12);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  pinMode(led_pin, OUTPUT);
  
}

void loop() {

  digitalWrite(led_pin, HIGH); 
  /* See Example: TypeA_WithDIPSwitches */
  //mySwitch.switchOn("11111", "00010");
  //delay(1000);
  //mySwitch.switchOn("11111", "00010");
  //delay(1000);

  /* Same switch as above, but using decimal code */
  //mySwitch.send(5393, 24);
  //delay(1000);  
  //mySwitch.send(5396, 24);
  //delay(1000);  

  /* Same switch as above, but using binary code */
  mySwitch.send("teste");
  delay(1000);  
  mySwitch.send("teste");
  delay(1000);

  /* Same switch as above, but tri-state code */ 
  //mySwitch.sendTriState("00000FFF0F0F");
  //delay(1000);  
  //mySwitch.sendTriState("00000FFF0FF0");
  //delay(1000);

  digitalWrite(led_pin, LOW);
  delay(5000);
}
