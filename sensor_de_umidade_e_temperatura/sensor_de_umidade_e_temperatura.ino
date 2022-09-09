#include <LiquidCrystal.h>
#include <DHT.h>//Inclui a biblioteca DHT Sensor Library
#define DHTPIN A0//Pino alalogico A0 conectado ao DHT11
#define DHTTYPE DHT11//DHT 11
DHT dht(DHTPIN, DHTTYPE);//Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)
int buzzer = 13;//Define o pino onde o buzzer esta ligado
int notas[] = {500, 800};//Vetor com as frequências para o buzzer
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup() 
{
  pinMode(12, OUTPUT);//Define o pino 12 do lcd como saida
  pinMode(11, OUTPUT);//Define o pino 11 do lcd como saida
  pinMode(buzzer, OUTPUT);//define o buzzer como saida
  Serial.begin(9600);//Inicializa a comunicação serial
  dht.begin();//Inicializa o sensor DHT11
  lcd.begin(16, 2);//Inicia o display lcd
}
void loop() 
{
  float h = dht.readHumidity();//lê o valor da umidade e armazena na variável h do tipo float (aceita números com casas decimais)
  float t = dht.readTemperature();//lê o valor da temperatura e armazena na variável t do tipo float (aceita números com casas decimais)
  if (isnan(h) || isnan(t))//Verifica se a umidade ou temperatura são ou não um número
    {
      return;//Caso não seja um número retorna
    }
  lcd.clear();//limpa o painel lcd
  lcd.setCursor(0, 0);//seta o cusor na posição 0, 0 da matriz do lcd
  lcd.print("Umidade: ");//Imprime no monitor serial a mensagem "Umidade: "
  lcd.print(h);//Imprime na serial o valor da umidade
  lcd.print("%");//Imprime na serial o caractere "%" e salta para a próxima linha
  lcd.setCursor(0, 1);//seta o cusor na posição 0, 1 da matriz do lcd
  lcd.print("Temp: ");//Imprime no monitor serial a mensagem "Temperatura: "
  lcd.print(t);//Imprime na serial o valor da temperatura
  lcd.write(B11011111);//Simbolo " º " 
  lcd.print("C");//Imprime no monitor serial "C" e salta para a próxima linha
  delay(500);//Intervalo de meio segundo entre as medições

  if(t < 40 && t > -20 && h > 40 && h < 70)//Verifica se a umidade e a temperatura esta dentro da adequada
  {
    noTone(buzzer);//Define o buzzer como desligado
  }
  else
  {
    for(int i = 0; i < 2; i++)
    {
    tone(buzzer, notas[i]);//Passa pelo vetor de notas do buzzer
    delay(250);
    }
  }
}
