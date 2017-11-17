void setup() {
  Serial.begin(9600);
  Serial1.begin(38400);
  Serial.println("configuracion");
}

void loop() {
  Serial.println("aqui estoy");
  delay(500);
  if (Serial1.available())
    Serial.println("ya estoy aqui");
    Serial.println(Serial1.read());
  if (Serial.available())
  Serial1.write(Serial.read());
}
