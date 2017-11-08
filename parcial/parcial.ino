#include <SoftwareSerial.h>
int microarriba = 37;
int microabajo = 36;
int motorup = 22;
int motordown = 23;
char data;   
bool pulsi = false;             
void setup()
{
  
  Serial1.begin(38400);
  Serial.begin(9600);
  pinMode(microarriba,INPUT);
  pinMode(microabajo,INPUT);
  pinMode(motorup,OUTPUT);
  pinMode(motordown,OUTPUT);
  Serial1.print("AT+NAME");
  Serial1.print("PUENTE");
  delay(1000);
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
    if (data == '2'){ 
      subirO();
      break;
    }
    else if (data == '3')     
      bajarO();
      break;
  }
  else
  {
    delay(50);
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
      subirO();
      break;
    }
    else if (data == '3')     
      bajarO();
      break;
  }
  else
  {
    delay(50);
  }
    if(digitalRead(microabajo)== HIGH){
      digitalWrite(motordown,LOW);
      pulsi = true;
    }
  }
  pulsi = false;
}

void loop()
{
  if (Serial1.available() > 0) 
  {
    data = Serial1.read();       
    if (data == '1'){ 
      subir();
    }
    else if (data == '0')     
      bajar();
    else if (data == '2')     
      subirO();
    else if (data == '3')     
      bajarO();
  }
  else
  {
    delay(500);
  }
}
