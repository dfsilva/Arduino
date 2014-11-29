const int relay_amp_pin = 10;
const int mov_sensor_pin = 9;

void setup() {
    Serial.begin(9600);
    pinMode(relay_amp_pin, OUTPUT);
    pinMode(mov_sensor_pin, INPUT);
}

void loop() {
    int pirVal = digitalRead(mov_sensor_pin);
    if(pirVal == HIGH){
      digitalWrite(relay_amp_pin, HIGH);
      delay(2000);
    }else{
      digitalWrite(relay_amp_pin, LOW);
    }
}
