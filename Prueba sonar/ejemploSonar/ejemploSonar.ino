#define SONAR_TRIGGER_PIN 3
#define SONAR_ECHO_PIN 2

int microarriba = 37;
int microabajo = 36;
int motorup = 22;
int motordown = 23;
char data;   
bool pulsi = false;  

void setup() {
   pinMode(SONAR_TRIGGER_PIN, OUTPUT);
   pinMode(SONAR_ECHO_PIN, INPUT);
   Serial.begin(9600);
}

unsigned int measure_distance()
{
   // Trigger the SRF05:
   digitalWrite(SONAR_TRIGGER_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(SONAR_TRIGGER_PIN, LOW);

   // Wait for Echo Pulse
   unsigned long pulse_length = pulseIn(SONAR_ECHO_PIN, HIGH);

   // Ensure the ultrasonic "beep" has faded away
   delay(50);

   // Convert Pulse to Distance (inches) 
   // pulse_length/58 = cm or pulse_length/148 = inches
   return( (unsigned int) (pulse_length / 58) );
}

void subirO(){
  digitalWrite(motorup,HIGH);
  while(pulsi==false){
    if(digitalRead(microarriba)== HIGH){
      pulsi = true;
      digitalWrite(motorup,LOW);
    }
  }
  pulsi = false;
}

void loop() {
  unsigned int current_distance = measure_distance();
  Serial.println(current_distance);
  delay(1000);

}
