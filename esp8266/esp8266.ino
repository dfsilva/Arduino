#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial esp8266(2, 3); // RX, TX
int debug = true;

void setup() {
  Serial.begin(9600);
  // Configure na linha abaixo a velocidade inicial do
  // modulo ESP8266
  esp8266.begin(115200);
  sendData("AT+RSTrn", 2000, DEBUG);
  delay(1000);
  Serial.println("Versao de firmware");
  delay(3000);
  sendData("AT+GMRrn", 2000, DEBUG); // rst

  sendData("AT+CIOBAUD=19200rn", 2000, DEBUG);
  Serial.println("** Final **");
}

void loop() { // run over and over
 
}

String sendData(String command, const int timeout, boolean debug){
  // Envio dos comandos AT para o modulo
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  
    Serial.print(response);
  }
  return response;
}
