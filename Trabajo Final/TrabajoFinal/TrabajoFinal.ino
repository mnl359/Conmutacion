#include <SoftwareSerial.h>


#define SONAR_TRIGGER_PIN 3
#define SONAR_ECHO_PIN 2
#define SONAR_TRIGGER_PIN_2 9
#define SONAR_ECHO_PIN_2 8

int microarriba = 37;
int microabajo = 36;
int motorup = 22;
int motordown = 23;
char data;   
bool pulsi = false;             
void setup()
{
  pinMode(SONAR_TRIGGER_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);
  pinMode(SONAR_TRIGGER_PIN_2, OUTPUT);
  pinMode(SONAR_ECHO_PIN_2, INPUT); 
  Serial1.begin(38400);
  Serial.begin(9600);
  pinMode(microarriba,INPUT);
  pinMode(microabajo,INPUT);
  pinMode(motorup,OUTPUT);
  pinMode(motordown,OUTPUT);
  delay(1000);
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

unsigned int measure_distance2()
{
    // Trigger the SRF05:
   digitalWrite(SONAR_TRIGGER_PIN_2, HIGH);
   delayMicroseconds(10);
   digitalWrite(SONAR_TRIGGER_PIN_2, LOW);

   // Wait for Echo Pulse
   unsigned long pulse_length = pulseIn(SONAR_ECHO_PIN_2, HIGH);

   // Ensure the ultrasonic "beep" has faded away
   delay(50);

   // Convert Pulse to Distance (inches) 
   // pulse_length/58 = cm or pulse_length/148 = inches
   return( (unsigned int) (pulse_length / 58) );
}


void Mantenimiento(){
  while(Serial1.read() != '3'){
  }
  bajar();
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

void subir(){
  digitalWrite(motorup,HIGH);
  while(pulsi==false){
    if (Serial1.available() > 0) 
    {
      data = Serial1.read(); 
      Serial.println(data);      
      if (data == '2'){
        digitalWrite(motorup,LOW); 
        Mantenimiento();
        break;
      }
    }
    if(digitalRead(microarriba)== HIGH){
        pulsi = true;
        digitalWrite(motorup,LOW);
      }
  }
  pulsi = false;
}

void bajarO(){
  digitalWrite(motordown,HIGH);
  while(pulsi==false){
    if(digitalRead(microabajo)== HIGH){
      digitalWrite(motordown,LOW);
      pulsi = true;
    }
  }
  pulsi = false;
}

void bajar(){
  digitalWrite(motordown,HIGH);
  while(pulsi==false){
    if (Serial1.available() > 0) 
  {
    data = Serial1.read();       
    if (data == '2'){  
      digitalWrite(motordown,LOW);
      Mantenimiento();
      break;
    }
  }
  if(digitalRead(microabajo)== HIGH){
      digitalWrite(motordown,LOW);
      pulsi = true;
    }
 }
   pulsi = false;
}



int sensor1(){
  int senmas = 0;
  int senmenos = 0;
  unsigned int a = 0;
  for(int i = 0; i < 5; i++){
    a = measure_distance();
    if(a < 30){
      senmenos += 1;
    } 
    else{
      senmas += 1;
    }
    delay(50);
  }
  if (senmenos > senmas){
    return 1;
  }
  return 0;
}


int sensor2(){
  int senmas = 0;
  int senmenos = 0;
  unsigned int a = 0;
  for(int i = 0; i < 5; i++){
    a = measure_distance2();
    if(a < 30){
      senmenos += 1;
    } 
    else{
      senmas += 1;
    }
    delay(50);
  }
  if (senmenos > senmas){
    return 1;
  }
  return 0;
}


void loop()
{
  if (sensor1() == 1){
      Serial1.println(1);
      subirO();
      delay(5000);
    }
  if(sensor2() == 1){
    Serial1.println(0);
      bajarO();
      delay(5000);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
  }
  else if (Serial1.available() > 0) 
  {
    data = Serial1.read();  
    if(data == '2'){
      Serial1.println(2);
      Mantenimiento();
    }
    else {  
      if (data == '1'){
        subir();
      }
      else if (data == '0') {  
        bajar();
      }
      else
      {
        delay(500);
      }
  }
  delay(500);
 }
 else{
  if(digitalRead(microarriba)== HIGH){
    bajar();
  }
 }
}
