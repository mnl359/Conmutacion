#define PIN_TRIGGER 3
#define PIN_ECHO 2
#define SONAR_TRIGGER_PIN_2 5
#define SONAR_ECHO_PIN_2 4


int microarriba = 37;
int microabajo = 36;
int motorup = 22;
int motordown = 23;
char data;   
bool pulsi = false;  

float distancia;
unsigned long tiempo;
unsigned long cronometro;
unsigned long reloj=0;
 
void setup()
{
  Serial.begin(9600);
  pinMode(PIN_ECHO,INPUT);
  pinMode(PIN_TRIGGER,OUTPUT);
  digitalWrite(PIN_TRIGGER,LOW); // Para «limpiar» el pulso del pin trigger del módulo
  delayMicroseconds(2);
  pinMode(microarriba,INPUT);
  pinMode(microabajo,INPUT);
  pinMode(motorup,OUTPUT);
  pinMode(motordown,OUTPUT);
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
 
void loop()
{
  cronometro=millis()-reloj;
  if(cronometro>ESPERA_ENTRE_LECTURAS)
  {
    digitalWrite(PIN_TRIGGER,HIGH); // Un pulso a nivel alto…
    delayMicroseconds(10); // …durante 10 µs y
    digitalWrite(PIN_TRIGGER,LOW); // …volver al nivel bajo
    tiempo=pulseIn(PIN_ECHO,HIGH,TIMEOUT_PULSO); // Medir el tiempo que tarda en llegar un pulso
    distancia=MEDIA_VELOCIDAD_SONIDO*tiempo;
    Serial.print(distancia);
    Serial.println(" cm");
    reloj=millis();
    if(distancia <= 30){
      subirO();
     }
  }
  
}
