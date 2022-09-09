//================================================Inclusão de bibliotecas==============================================================//
#include <Wire.h>
#include <DS1302.h>//inclui a biblioteca do clockmodule
#include <LiquidCrystal.h>//Inclui a biblioteca LiquidCrystal do lcd
#include <DHT.h>//Inclui a biblioteca DHT Sensor Library
#define DHTPIN A0//Pino alalogico A0 conectado ao DHT11
#define DHTTYPE DHT11//DHT 11
DHT dht(DHTPIN, DHTTYPE);//Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

//================================================Definição de variaveis===============================================================//
int buzzer = 13;//Define o pino onde o buzzer esta ligado
int notas[] = {300, 700};//Vetor com as frequências para o buzzer
const int rst = 7;//reset do modulo na porta digital 7
const int dat = 8;//data do modulo na porta digital 8
const int clk = 9;//clock do modulo na porta digital 9

DS1302 rtc(rst, dat, clk);

int uMin = 20;//umidade minima
int uMax = 90;//umidade maxima
int tMin = 0;//temperatura minima
int tMax = 50;//temperatura maxima

int h;//Umidade
float t;//Temperatura

int bot1 = A3;//botao 1 na porta analogica A3
int bot2 = A2;//botao 2 na porta analogica A2
int bot4 = A4;//botao 4 na porta analogica A4
int valor = 0;//valor definido com valor 0
boolean valor2 = true;//valor2 com operador logio true

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);//Pinos do painel lcd

//================================================Entradas e saidas e definições=======================================================//
void setup() 
{
  pinMode(bot1, INPUT);//Botao 1 "seleção de opções" setado como entrada
  pinMode(bot2, INPUT);//Botao 2 "Alterar valores para mais" setado como entrada
  pinMode(bot4, INPUT);//Botao 4 "Alterar valores para menos" setado como entrada
  pinMode(12, OUTPUT);//Define o pino 12 do lcd como saida
  pinMode(11, OUTPUT);//Define o pino 11 do lcd como saida
  pinMode(buzzer, OUTPUT);//define o buzzer como saida 
  Serial.begin(9600);//Inicializa a comunicação serial
  dht.begin();//Inicializa o sensor DHT11
  lcd.begin(16, 2);//Inicia o display lcd

  rtc.halt(false);
  rtc.writeProtect(true);//se true, a data e hora nao serao mais alteradas ao subir o codigo novamente, se false, sera alterado

  Time t(2021, 10, 05, 16, 02, 00, 3);//definição da hora(se estiver false o writeProtect)

  rtc.time(t);
}

//================================================Loop=================================================================================//
void loop() 
{  
  if(digitalRead(bot1) == HIGH) //Botão para seleção das opções
  {
    valor++;//Agraga mais 1 ao valor de valor
    
    if(valor > 5)//Se valor for maior que 4 "valor" volta a ser 0
    {
      valor = 0;
    }
  }
  
//================================================Seleção de estado do buzzer==========================================================//
    if(valor2 == false || t < tMax && t > tMin && h > uMin && h < uMax)//verifica as especificações setadas pelo usuario
    {
      noTone(buzzer);//Define o buzzer como desligado
      delay(250);//Aguarda 500 ms
    }
    else//se nao atender a especificação
    {
      tocar();//chama a função tocar
    }

//================================================Opção normal=========================================================================//
  if(valor == 0)//verifica se valor é igual a 0
  {
    lcd.clear();//limpa o lcd
    
    mostraDataHora();//chama a função que mostra a hora
    sensor();//Chama a função sensor 
   
    lcd.setCursor(0, 1);//seta o cusor na posição 0, 0 da matriz do lcd
    lcd.print("U:");//Imprime no lcd a mensagem "Umidade: "
    lcd.print(h);//Imprime no lcd o valor da umidade
    lcd.print("%");//Imprime no lcd o caractere "%" e salta para a próxima linha
    lcd.setCursor(7, 1);//seta o cursor na posição 7, 1
    lcd.print("T:");//Imprime no lcd a mensagem "Temperatura: "
    lcd.print(t);//Imprime no lcd o valor da temperatura
    lcd.write(B11011111);//Simbolo " º " 
    lcd.print("C");//Imprime no lcd "C" e salta para a próxima linha
  }

//================================================Opção de alarme======================================================================//
  if(valor == 1)//verifica se valor é igual a 1
  {
    lcd.clear();//limpa o lcd
    lcd.setCursor(4, 0);//seta o cursor na posição 4, 0
    lcd.print("Alarme:");//escreve no lcd
    
    if(digitalRead(bot2) == HIGH)//verifica se o botão para mais foi apertado
    {    
        valor2 = true;//valor de seleção do buzzer false      
    }
    if(digitalRead(bot4) == HIGH)//verifica se o botao para menos foi apertado
    {
        valor2 = false;// valor do buzzer true     
    }
    if(valor2 == false)//verifica se o valor é falso
    {
      lcd.setCursor(6, 1);//seta o cursor na posição 6, 1
      lcd.print("OFF");//escreve "OFF" no lcd
    }
    else//Se nao for falso é verdadeiro e executa o codigo abaixo
    {
      lcd.setCursor(6, 1);//seta o cursor na posição 6, 1
      lcd.print("ON");//escreve "ON" no lcd
    }    
  }

//================================================Opção de umidade max.================================================================//
  if(valor == 2)//verifica se valor é igual a 2
  {
    lcd.clear();//limpa o lcd
    lcd.setCursor(2, 0);//seta o cursor na posição 2, 0
    lcd.print("Umidade max:");//escreve no lcd
    lcd.setCursor(6, 1);//seta o cursor na posição 6, 1
    lcd.print(uMax);//mostra no lcd a uMax

    if(digitalRead(bot2) == HIGH)//verifica se o botão para mais foi apertado
        {
          uMax++;//aumenta 1
          
          if(uMax > 90)//verifica se uMax é maior que 90
          {
            uMax = 90;//se for, a uMax volta  a ser 90
          }  
        }
        if(digitalRead(bot4) == HIGH)//verifica se o botao para menos foi apertado
        {
          uMax--;//diminui 1
          
          if(uMax <= uMin)//verifica se uMax é menor ou igual a uMin 
          {
            uMax = uMin + 1;//se for, o valor sera igual a uMin + 1
          }  
        }
  }

//================================================Opção de umidade min.================================================================//
  if(valor == 3)//verifica se valor é igual a 3
  {
    lcd.clear();//limpa o lcd
    lcd.setCursor(2, 0);//seta o cursor na posição 2, 0
    lcd.print("Umidade min:");//escreve no lcd
    lcd.setCursor(6, 1);//seta o cursor na posição 6, 1
    lcd.print(uMin);//mostra no lcd a uMin

    if(digitalRead(bot2) == HIGH)//verifica se o botão para mais foi apertado
        {
          uMin++;//aumenta 1
          
          if(uMin >= uMax)//verifica se uMin é maior ou igual a uMax
          {
            uMin = uMax - 1;//se for, o valor sera igual a uMax - 1
          }  
        }
        if(digitalRead(bot4) == HIGH)//verifica se o botao para menos foi apertado
        {
          uMin--;//diminui 1
          
          if(uMin < 20)//verifica se uMin é menor que 20
          {
            uMin = 20;//se for, uMin volta a ser 20
          }  
        }
  }

//================================================Opção de temperatura max.============================================================//
  if(valor == 4)//verifica se valor é igual a 4
  {
    lcd.clear();//limpa o lcd
    lcd.setCursor(0, 0);//seta o cursor na posição 0, 0
    lcd.print("Temperatura max:");//escreve no lcd
    lcd.setCursor(6, 1);//seta o cursor na posição 6, 1
    lcd.print(tMax);//mostra no lcd a tMax

    if(digitalRead(bot2) == HIGH)//verifica se o botão para mais foi apertado
        {
          tMax++;//aumenta 1
          
          if(tMax > 50)//verifica se tMax é maior que 50
          {
            tMax = 50;//se for, o valor de tMax volta a ser 50
          }  
        }
        if(digitalRead(bot4) == HIGH)//verifica se o botao para menos foi apertado
        {
          tMax--;//diminui 1
          
          if(tMax <= tMin)//verifica se tMax é menor ou igual que tMin
          {
            tMax = tMin + 1;//se for menor, o valor será igual a tMin + 1
          }  
        }
  }

//================================================Opção de temperatura min.============================================================//
  if(valor == 5)//verifica se valor é igual a 5
  {
    lcd.clear();//limpa o lcd
    lcd.setCursor(0, 0);//seta o cursor na posição 0, 0
    lcd.print("Temperatura min:");//escreve no lcd
    lcd.setCursor(6, 1);//seta o cursor na posição 6, 1
    lcd.print(tMin);//mostra no lcd a tMin

    if(digitalRead(bot2) == HIGH)//verifica se o botão para mais foi apertado
        {
          tMin++;//aumenta 1
          
          if(tMin >= tMax)//verifica se tMin é maio ou igual que tMax
          {
            tMin = tMax - 1;//se for maior, o valor sera igual a tMax - 1
          }  
        }
        if(digitalRead(bot4) == HIGH)//verifica se o botao para menos foi apertado
        {
          tMin--;//diminui 1
          
          if(tMin < 0)//verifica se tMin é menor que 0
          {
            tMin = 0;//se for menor, tMin volta a ser 0
          }  
        }
  }
  delay(5);//atraso de 5 ms ate a proxima execução
}
//================================================Função tocar=========================================================================//
static void tocar()
{
    for(int i = 0; i < 2; i++)
    {
       tone(buzzer, notas[i]);//Passa pelo vetor de notas do buzzer
       delay(125);//Tambem aguarda 500 ms mas como aão duas notas para tocar é aguradado 250 ms para cada
    }
}

//================================================Função mostrar data e hora===========================================================//
void mostraDataHora()
{
  Time t = rtc.time();//Obtém a data atual a partir do chip
  
  //Coloca numa variável, a data (no formato "##-##-#### (DIA)")
  char data[17];
  snprintf(data, sizeof(data), "%02d/%02d/%04d", t.date, t.mon, t.yr);
  
  // Coloca numa variável, a hora (no formato "##:##:##")
  char hora[9];
  snprintf(hora, sizeof(hora), "%02d:%02d",t.hr, t.min);
  
  lcd.setCursor(0,0);//seta o cursor na posição 0, 0
  lcd.print(data);//mostra a data no lcd
  lcd.setCursor(11,0);//seta o cursor na posição 11, 0
  lcd.print(hora);//mostra a hora no lcd
}

//================================================Função sensor========================================================================//
static void sensor()
{
  h = dht.readHumidity();//lê o valor da umidade e armazena na variável h do tipo inteiro
  t = dht.readTemperature();//lê o valor da temperatura e armazena na variável t do tipo float (aceita números com casas decimais)
  if (isnan(h) || isnan(t))//Verifica se a umidade ou temperatura são ou não um número
    {
      return;//Caso não seja um número retorna
    }
}
