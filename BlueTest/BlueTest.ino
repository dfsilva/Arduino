#include <SoftwareSerial.h>
#include "bluetooth.h"

Bluetooth *blue = new Bluetooth("DiegoBluetooth");

void setup() {
  Serial.begin(9600);
  blue->setupBluetooth();  
}

void loop() {
  String msg = blue->Read();
  if(msg.length() > 1){
    Serial.println(msg);
  }
  
  if(Serial.available()){
    char reader = (char) Serial.read();
    Serial.println(reader);
    blue->Send(reader);
  }
}
