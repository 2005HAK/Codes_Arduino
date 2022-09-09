int buzzer = 1;

int numnotas = 24;

int notas[] = {262, 294, 330, 349, 349, 349, 262, 294, 262, 294, 294, 294, 262, 392, 349, 330, 330, 330, 262, 294, 330, 349, 349, 349};

void setup()
{
  pinMode(buzzer, OUTPUT);
}

void loop()
{ 
  if(valorEntrada==LOW){
  noTone(buzzer);
  
  }else{
  for(int i = 0; i < numnotas; i++){
    tone(buzzer, notas[i]);
    delay(300);
  }
  }
    
}
