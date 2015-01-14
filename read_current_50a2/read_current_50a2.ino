

void setup()
{
  Serial.begin(9600);  
}
void loop()
{   
  
  int samplesnum = 100;
  int adc_zero = 507; 
  float sensitivity = 0.04;
  float currentacc = 0.0;
  
    for(int i=0; i < samplesnum ; i++) {
      int adc_raw = analogRead(0);
      currentacc += (adc_raw - adc_zero) * (adc_raw - adc_zero); //subtract the zero-current value (512 or thereabouts) from the raw readings, square that, and add it to an accumulator variable
      //currentacc += (adc_raw - 500)*5/1024/0.04-0.04;
      delay(10);
    }
    
    float meanSquare = currentacc/samplesnum;
    float currentac = sqrt(meanSquare)*5/1024/0.04-0.10;// * (5 / (0.0016 * 1024.0)) - 0.5;
    Serial.println(currentac);
    delay(100); 
}



