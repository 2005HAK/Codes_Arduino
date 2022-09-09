int azul = 10;//Atribui o valor 10 a variável azul
int verde = 9;//Atribui o valor 9 a variável verde
int vermelho = 11;//Atribui o valor 11 a variável vermelho

void setup() 
{
pinMode(azul, OUTPUT);//Define a variável azul como saída
pinMode(verde, OUTPUT) ;//Define a variável verde como saída
pinMode(vermelho, OUTPUT);//Define a variável vermelho como saída
}

void loop() 
{
//vermelho
digitalWrite(vermelho, HIGH);//Coloca vermelho em nível alto, ligando-o
delay(1000);
digitalWrite(vermelho, LOW);//Coloca vermelho em nível alto, ligando-o
delay(1);
//verde
digitalWrite(verde, HIGH);//Coloca verde em nível alto, ligando-o
delay(1000);
digitalWrite(verde, LOW);//Coloca verde em nível alto, ligando-o
delay(1);
//azul
digitalWrite(azul, HIGH);//Coloca azul em nível alto, ligando-o
delay(1000);
digitalWrite(azul, LOW);//Coloca azul em nível alto, ligando-o
delay(1);
//Branco
digitalWrite(azul, HIGH);//Coloca azul em nível alto, ligando-o
digitalWrite(vermelho, HIGH);//Coloca vermelho em nível alto, ligando-o
digitalWrite(verde, HIGH);//Coloca verde em nível alto, ligando-o
delay(1000);//Intervalo de 1 segundo
digitalWrite(azul, LOW);//Coloca azul em nível baixo novamente
digitalWrite(vermelho, LOW);//Coloca vermelho em nível baixo novamente
digitalWrite(verde, LOW);//Coloca verde em nível baixo novamente
delay(1);//Intervalo de 1 segundo
//Magenta (violeta-púrpura)
digitalWrite(azul, HIGH);//Coloca azul em nível alto
digitalWrite(vermelho, HIGH);//Coloca vermelho em nível alto
delay(1000);//Intervalo de 1 segundo
digitalWrite(azul, LOW);//Coloca azul em nível baixo
digitalWrite(vermelho, LOW);//Coloca vermelho em nível baixo
delay(1);//Intervalo de 1 segundo
//Amarelo
digitalWrite(verde, HIGH);//Coloca verde em nível alto
digitalWrite(vermelho, HIGH);//Coloca vermelho em nível alto
delay(1000);//Intervalo de 1 segundo
digitalWrite(verde, LOW);//Coloca verde em nível baixo
digitalWrite(vermelho, LOW);//Coloca vermelho em nível baixo
delay(1);//Intervalo de 1 segundo
//Ciano
digitalWrite(verde, HIGH);//Coloca verde em nível alto
digitalWrite(azul, HIGH);//Coloca azul em nível baixo alto
delay(1000);//Intervalo de 1 segundo
digitalWrite(verde, LOW);//Coloca verde em nível baixo
digitalWrite(azul, LOW);//Coloca azul em nível baixo
delay(1);//Intervalo de 1 segundo
}
