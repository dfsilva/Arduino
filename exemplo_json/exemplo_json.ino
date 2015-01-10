#include <aJSON.h>


aJsonStream serial_stream(&Serial);

void setup()
{
  Serial.begin(9600);
}

void loop(){

    aJsonObject *msg = aJson.createObject();
    aJson.addStringToObject(msg, "id", "1");
    aJson.addStringToObject(msg, "nome", "sala");
    aJson.addStringToObject(msg, "valor", "40.32");
    aJson.addStringToObject(msg, "teste", "55");
   
    aJson.print(msg, &serial_stream);
    Serial.println(); 
    aJson.deleteItem(msg);

    delay(300);

}
