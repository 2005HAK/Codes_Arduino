#include <Servo.h>

Servo servomotor;//Criando objeto do tipo Servo
int pos = 0;//Variável que armazena a posição do servo

void setup()
{
servomotor.attach(9);//Atribui o pino digital 9 ao objeto servomotor
}
void loop() 
{
for(pos = 0; pos <= 180; pos += 1) //para pos igual a 0, enquanto pos for menor que 180, incrementa 1 em pos
{
servomotor.write(pos);// Comanda o servo para ir para o posição da variável pos
delay(50);//Intervalo de 15 milissegundos
}
for(pos = 180; pos >= 0; pos -= 1)//Para pos igual a 180, enquanto por for maior ou igual a 0, decrementa 1 de pos
{
servomotor.write(pos);//Comanda o servo para ir para o posição da variável pos
delay(50);// Intervalo de 15 milissegundos
}
}
