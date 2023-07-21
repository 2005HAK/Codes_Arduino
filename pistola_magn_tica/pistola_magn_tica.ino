void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  if(digitalRead(3)==HIGH){
    digitalWrite(2, HIGH);
    delay(40);
    digitalWrite(2, LOW);
    delay(3000);
  }
}
