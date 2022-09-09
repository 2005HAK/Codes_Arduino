int led = 10; //Atribui a porta digital 10 a variável led
int ldr = A0; //Atribui A0 a variável ldr
int valorldr = 0;//Declara a variável valorldr como inteiro

void setup() 
{
pinMode(led, OUTPUT); //Define led (pino digital 10) como saída
pinMode(ldr, INPUT); //Define ldr (pino analógico A0) como saída
Serial.begin(9600); //Inicialização da comunicação serial, com velocidade de comunicação de 9600
}
void loop() 
{
valorldr = analogRead(ldr);//Lê o valor do sensor ldr e armazena na variável valorldr
Serial.println(valorldr);//Imprime na serial os dados de valorldr
if(valorldr < 500){ //Se o valor de valorldr for menor que 500:
digitalWrite(led, HIGH);//Coloca led em alto para acioná-lo
}
else{ //Senão:
digitalWrite(led, LOW);//Coloca led em baixo para que o mesmo desligue ou permaneça desligado
}
}
