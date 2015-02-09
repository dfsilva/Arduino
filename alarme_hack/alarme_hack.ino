
const int alarmPin = 0;
const int alarmActivePort = 3;
int alarmState = 0; 
int alarmActiveState = 0; 


void setup() {
  Serial.begin(9600);
  pinMode(alarmActivePort, INPUT);     
}

void loop(){
  alarmState = analogRead(alarmPin);
  int disparado = digitalRead(alarmActivePort);
  
  if(alarmState > 190){
    Serial.println("Alarme Desarmado");
    alarmActiveState = LOW;
  }else{
    Serial.println("Alarme Armado");
    
    if(alarmActiveState == LOW && disparado == HIGH ){
      Serial.println("setando para alto");
      alarmActiveState = HIGH;
      delay(1000);
    }
  }
  
  if(alarmActiveState == HIGH){
    Serial.println("DISPARADO");
  }
}
