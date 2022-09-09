int LED = 13;
int BOTAO = 2;
int valor = LOW;
int valorAnterior = LOW;
int estado = 0;
int brilho = 128;
unsigned long inicio;

void setup()
{
 pinMode(LED, OUTPUT);
 pinMode(BOTAO, INPUT);
}

void loop()
{
 valor = digitalRead(BOTAO);
  if((valor == HIGH)&&(valorAnterior == LOW)){
    estado = 1 - estado;
    inicio = millis();
    delay(10);
  }
  if((valor ==HIGH) &&(valorAnterior == HIGH)){
    if(estado == 1 &&(millis() - inicio) > 500){
      brilho++;
      delay(10);
  
      if(brilho > 255)
        brilho = 0;
    }
  }
  valorAnterior = valor;
  if(estado ==1)
    digitalWrite(LED, brilho);
  else
    digitalWrite(LED, 0);
}
