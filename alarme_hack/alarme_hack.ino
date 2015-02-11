
const int alarmPin = 0;
const int alarmActivePort = 3;
int alarmState = 0; 
int alarmActiveState = 0; 

const int disparaAlarmePort = 13;
const int sensorShockPort = 4;

const int rfPin = 1;


void setup() {
  Serial.begin(9600);
  pinMode(alarmActivePort, INPUT);

  pinMode(disparaAlarmePort, OUTPUT);   
  pinMode(sensorShockPort, INPUT);  
  
  digitalWrite(disparaAlarmePort, HIGH);
}

void loop(){
 /*
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
  
  */
  

/*
  int sensorChoque = digitalRead(sensorShockPort);
  Serial.println(sensorChoque);
  delay(500);
  */
  int rfState = analogRead(rfPin);
  Serial.println(rfState);
  delay(10);
 
  
  /*
  digitalWrite(disparaAlarmePort, HIGH);
  delay(10000);
  digitalWrite(disparaAlarmePort, LOW);
  delay(1000);
  */
  
  
}
