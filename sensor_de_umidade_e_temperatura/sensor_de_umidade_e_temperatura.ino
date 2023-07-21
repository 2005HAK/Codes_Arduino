#include <LiquidCrystal.h>
#include <DHT.h>//Inclui a biblioteca DHT Sensor Library
#define DHTPIN A0//Pino alalogico A0 conectado ao DHT11
#define DHTTYPE DHT11//DHT 11
DHT dht(DHTPIN, DHTTYPE);//Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup()
{
  pinMode(12, OUTPUT);//Define o pino 12 do lcd como saida
  pinMode(11, OUTPUT);//Define o pino 11 do lcd como saida
  Serial.begin(9600);//Inicializa a comunicação serial
  dht.begin();//Inicializa o sensor DHT11
  lcd.begin(16, 2);//Inicia o display lcd
}
void loop()
{
  lcd.clear();//limpa o painel lcd
  float h = dht.readHumidity();//lê o valor da umidade e armazena na variável h do tipo float (aceita números com casas decimais)
  float t = dht.readTemperature();//lê o valor da temperatura e armazena na variável t do tipo float (aceita números com casas decimais)
  if (isnan(h) || isnan(t))//Verifica se a umidade ou temperatura são ou não um número
  {
    return;//Caso não seja um número retorna
  }
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
}
