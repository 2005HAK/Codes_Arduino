#define Relay1 2

void setup() 
{
  pinMode(Relay1, OUTPUT);
  digitalWrite(Relay1, HIGH);
}

void loop() 
{
  alteraStatus(Relay1, true);
  delay(10800000); //Carrega
  alteraStatus(Relay1, false);
  delay(10800000); //Desliga
}

void alteraStatus(int porta, bool ativado) 
{
  if (ativado == true) 
  {
    digitalWrite(porta, HIGH);
  }
  else
  {
    digitalWrite(porta, LOW);
  }
}
