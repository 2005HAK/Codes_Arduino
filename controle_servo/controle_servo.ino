#include "Servo.h"

int eixo_X = A0; //PINO REFERENTE A LIGAÇÃO DO EIXO X
int eixo_Y = A1; //PINO REFERENTE A LIGAÇÃO DO EIXO Y
int botao = 2; //PINO REFERENTE A LIGAÇÃO NO PINO KEY (EIXO Z)
int angulo = 90;
Servo meuservo;

void setup() {
  pinMode (botao, INPUT_PULLUP); //DEFINE A PORTA COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
  meuservo.attach(3);
}
void loop() {
  angulo = (analogRead(eixo_Y)*180)/1023;
  
  meuservo.write(angulo);
  delay(200); //INTERVALO DE 500 MILISSEGUNDOS
}
