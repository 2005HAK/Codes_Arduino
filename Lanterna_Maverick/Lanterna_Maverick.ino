int bot1 = 1;
int bot2 = 2;
int bot3 = 10;
int bot4 = 3;
int bot5 = 11;
int freio = LOW;
int meialuz = LOW;
int piscaesq = LOW;
int piscadir = LOW;
int alerta = LOW;
int lampd = 6;
int lampe = 7;
int lamfd = 5;
int lamfe = 8;
int lammd = 4;
int lamme = 9;

void setup()
{
  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);
  pinMode(bot3, INPUT);
  pinMode(bot4, INPUT);
  pinMode(bot5, INPUT);
  pinMode(lampd, OUTPUT);
  pinMode(lampe, OUTPUT);
  pinMode(lamfd, OUTPUT);
  pinMode(lamfe, OUTPUT);
  pinMode(lammd, OUTPUT);
  pinMode(lamme, OUTPUT);
}

void loop()
{
  
  freio = digitalRead(bot1);
  meialuz = digitalRead(bot2);
  piscaesq = digitalRead(bot3);
  piscadir = digitalRead(bot4);
  alerta = digitalRead(bot5);
  
  if(alerta == HIGH)
  {
    digitalWrite(lamme, LOW);
    digitalWrite(lamfe, LOW);
    digitalWrite(lampe, LOW);
    digitalWrite(lammd, LOW);
    digitalWrite(lamfd, LOW);
    digitalWrite(lampd, LOW);
    delay(225);
    digitalWrite(lamme, HIGH);
    digitalWrite(lamfe, LOW);
    digitalWrite(lampe, LOW);
    digitalWrite(lammd, HIGH);
    digitalWrite(lamfd, LOW);
    digitalWrite(lampd, LOW);
    delay(225);
    digitalWrite(lamme, HIGH);
    digitalWrite(lamfe, HIGH);
    digitalWrite(lampe, LOW);
    digitalWrite(lammd, HIGH);
    digitalWrite(lamfd, HIGH);
    digitalWrite(lampd, LOW);
    delay(225);
    digitalWrite(lamme, HIGH);
    digitalWrite(lamfe, HIGH);
    digitalWrite(lampe, HIGH);
    digitalWrite(lammd, HIGH);
    digitalWrite(lamfd, HIGH);
    digitalWrite(lampd, HIGH);
    delay(225);
  }
  else
  {    
      if(freio == HIGH)
      {
        digitalWrite(lamfd, HIGH);
        digitalWrite(lamfe, HIGH);
        digitalWrite(lammd, HIGH);
        digitalWrite(lamme, HIGH);
        delay(1);
      }
      else
      {
        digitalWrite(lamfd, LOW);
        digitalWrite(lamfe, LOW);
        digitalWrite(lammd, LOW);
        digitalWrite(lamme, LOW);
      }
      if(meialuz == HIGH || freio == HIGH)
      {
        digitalWrite(lammd, HIGH);
        digitalWrite(lamme, HIGH);
        delay(1);
      }
      else
      {
        digitalWrite(lammd, LOW);
        digitalWrite(lamme, LOW);
      }
      if(piscaesq == HIGH)
      {
        digitalWrite(lamme, LOW);
        digitalWrite(lamfe, LOW);
        digitalWrite(lampe, LOW);
        delay(225);
        digitalWrite(lamme, HIGH);
        digitalWrite(lamfe, LOW);
        digitalWrite(lampe, LOW);
        delay(225);
        digitalWrite(lamme, HIGH);
        digitalWrite(lamfe, HIGH);
        digitalWrite(lampe, LOW);
        delay(225);
        digitalWrite(lamme, HIGH);
        digitalWrite(lamfe, HIGH);
        digitalWrite(lampe, HIGH);
        delay(225);
      }
      else
      {
        digitalWrite(lampe, LOW);
      }
      if(piscadir == HIGH)
      {
        digitalWrite(lammd, LOW);
        digitalWrite(lamfd, LOW);
        digitalWrite(lampd, LOW);
        delay(225);
        digitalWrite(lammd, HIGH);
        digitalWrite(lamfd, LOW);
        digitalWrite(lampd, LOW);
        delay(225);
        digitalWrite(lammd, HIGH);
        digitalWrite(lamfd, HIGH);
        digitalWrite(lampd, LOW);
        delay(225);
        digitalWrite(lammd, HIGH);
        digitalWrite(lamfd, HIGH);
        digitalWrite(lampd, HIGH);
        delay(225);
      }
      else
      {
        digitalWrite(lampd, LOW);
      }
  }
}
