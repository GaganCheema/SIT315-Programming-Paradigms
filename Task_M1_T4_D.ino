const int SoilMoistureSensor = A0;
const int ForceSensor = A1; 
const int PIRSensor = A2;
const int PhotoSensor = A3;

const int led1 = 12;
const int led2 = 11;
const int led3 = 10;
const int led4 = 9;
const int led5 = 8;
const int led6 = 7;
const int led7 = 6;
const int led8 = 5;
const int ledTimer = 4;

void setup()
{
  Serial.begin(9600);
  
  pinMode(SoilMoistureSensor, INPUT);
  pinMode(ForceSensor, INPUT);
  pinMode(PIRSensor, INPUT);
  pinMode(PhotoSensor, INPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(ledTimer, OUTPUT);
  
  PCMSK1 |= bit(PCINT8); // Enable A0
  PCMSK1 |= bit(PCINT9); // Enable A1
  PCMSK1 |= bit(PCINT10);// Enable A2
  PCMSK1 |= bit(PCINT11);// Enable A3
  
  PCICR |= bit(PCIE1);
  PCICR |= bit(PCIE2);

  
  cli();  // Disable interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15625;  // For 1-second interval with a 16MHz clock
  
  TCCR1B |= (1 << WGM12) | (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
 
  sei();

}

void loop()
{
}

ISR(PCINT1_vect) 
{
  if(digitalRead(SoilMoistureSensor))
  {
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    Serial.println("Soil Moisture Sensor: Triggered");
  } else
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  
  if(digitalRead(ForceSensor))
  {
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    Serial.println("Force Sensor: Triggered");
  } else
  {
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  }
  
  if(digitalRead(PIRSensor))
  {
    digitalWrite(led5, LOW);
    digitalWrite(led6, HIGH);
    Serial.println("PIR Sensor: Motion Detected");
  } else
  {
    digitalWrite(led5, HIGH);
    digitalWrite(led6, LOW);
  }
  
  if(digitalRead(PhotoSensor))
  {
    digitalWrite(led8, HIGH);
    digitalWrite(led7, LOW);
    Serial.println("Photo Sensor: Light Detected");
  } else {
    digitalWrite(led7, HIGH);
  	digitalWrite(led8, LOW);
  }
}

ISR(TIMER1_COMPA_vect) 
{
  int LEDState = digitalRead(ledTimer);
  digitalWrite(ledTimer, !LEDState);
}
