#include <Wire.h>
#include <DS1302.h>
#include <LiquidCrystal.h>//Inclui a biblioteca LiquidCrystal do lcd
#include <DHT.h>//Inclui a biblioteca DHT Sensor Library
#define DHTPIN A0//Pino alalogico A0 conectado ao DHT11
#define DHTTYPE DHT11//DHT 11
DHT dht(DHTPIN, DHTTYPE);//Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

int buzzer = 13;//Define o pino onde o buzzer esta ligado
int notas[] = {300, 700};//Vetor com as frequências para o buzzer
const int rst = 7;
const int  = 7;
const int rst = 7;
int H = 0;//Horas
int M = 0;//Minutos
int S = 0;//Segundos
int d = 1;//Dia
int m = 1;//Mes
int h;//Umidade
float t;//Temperatura
int bot1 = A3;
int bot2 = A2;
int bot3 = A1;
int bot4 = A4;
int valor = 0;
int tempo;
boolean valor2 = true;
boolean valorEdicao = false;

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);//Pinos do painel lcd

void setup() 
{
  pinMode(bot1, INPUT);//Botao 1 "seleção de opções" setado como entrada
  pinMode(bot2, INPUT);//Botao 2 "Alterar valores para mais" setado como entrada
  pinMode(bot3, INPUT);//Botao 3 "Selecionar buzzer como ligado/desligado" setado como entrada
  pinMode(bot4, INPUT);//Botao 4 "Alterar valores para menos" setado como entrada
  pinMode(12, OUTPUT);//Define o pino 12 do lcd como saida
  pinMode(11, OUTPUT);//Define o pino 11 do lcd como saida
  pinMode(buzzer, OUTPUT);//define o buzzer como saida 
  Serial.begin(9600);//Inicializa a comunicação serial
  dht.begin();//Inicializa o sensor DHT11
  lcd.begin(16, 2);//Inicia o display lcd
}
void loop() 
{  
  if(digitalRead(bot1) == HIGH) //Botão para seleção das opções
  {
    valor++;//Agraga mais 1 ao valor de valor
    
    if(valor > 4)//Se valor for maior que 4 "valor" volta a ser 0
    {
      valor = 0;
    }
  }
  if(digitalRead(bot3) == HIGH)//verifica se o botão do buzzer foi apertado
  {    
    if(valor2 == true)//Se foi apertado e ja tem valor true
    {
      valor2 = false;//valor de seleão do buzzer se tornará false
    }
    else
    {
      valor2 = true;//Senão tinha valor true, se tornará true
    }
  }
  
  if(valor >= 1 && valor <=4)
  {
    tempo = 200;
  }
  else
  {
    tempo = 1000;
  }
  
//=========================================================================Seleção de estado do buzzer======================================================================//
 /*   if(valor2 == false || t < 40 && t > -20 && h > 40 && h < 70 || valor >= 1 && valor <=4)
    {
      noTone(buzzer);//Define o buzzer como desligado
      delay(tempo*2);//Aguarda 500 ms
    }
    else
    {
      tocar();
    }
*/
//=========================================================================Opção normal=====================================================================================//
  if(valor == 0)//seleção de valor 0
  {
    if(valorEdicao == true)
    {
      verificar_dia();
    }
    
    sensor();//Chama a função sensor
    relogio();//Chama a função relogio
    dislcd();//Chama a função dislcd  
   
    lcd.setCursor(0, 1);//seta o cusor na posição 0, 0 da matriz do lcd
    lcd.print("U:");//Imprime no monitor serial a mensagem "Umidade: "
    lcd.print(h);//Imprime na serial o valor da umidade
    lcd.print("%");//Imprime na serial o caractere "%" e salta para a próxima linha
    lcd.setCursor(7, 1);
    lcd.print("T:");//Imprime no monitor serial a mensagem "Temperatura: "
    lcd.print(t);//Imprime na serial o valor da temperatura
    lcd.write(B11011111);//Simbolo " º " 
    lcd.print("C");//Imprime no monitor serial "C" e salta para a próxima linha
  }
  
//=========================================================================Opção de edição da hora==========================================================================//
  if(valor == 1)
  {
    dislcd();//Chama a função dislcd
    lcd.setCursor(0, 1);
    lcd.print("^^");
     
        if(digitalRead(bot2) == HIGH)
        {
          H++;
          
          if(H > 23)
          {
            H = 0;
          }  
        }
        if(digitalRead(bot4) == HIGH)
        {
          H--;
          
          if(H < 0)
          {
            H = 23;
          }  
        }
  }

//=========================================================================Opção de edição dos minutos======================================================================//
  if(valor == 2)
  {
    dislcd();//Chama a função dislcd
    lcd.setCursor(3, 1);
    lcd.print("^^");
    S = 0;
    
        if(digitalRead(bot2) == HIGH)
        {
          M++;
          
          if(M > 59)
          {
            H++;
            M = 0;
          }     
        }   
        if(digitalRead(bot4) == HIGH)
        {
          M--;
          
          if(M < 0)
          {
            M = 59;
          }  
        }         
  }

//=========================================================================Opção de edição dos dias=========================================================================//
  if(valor == 3)
  {
    dislcd();//Chama a função dislcd
    lcd.setCursor(11, 1);
    lcd.print("^^");
    
        if(digitalRead(bot2) == HIGH)
        {
          d++;

          if(d > 31)
          {
            d = 1;   
          }
        }  
        if(digitalRead(bot4) == HIGH)
        {
          d--;
          
          if(d < 1)
          {
            d = 31;
          }  
        }
  }

//=========================================================================Opção de edição do mês===========================================================================//
  if(valor == 4)
  {
    dislcd();//Chama a função dislcd
    lcd.setCursor(14, 1);
    lcd.print("^^");
    valorEdicao = true;
    
        if(digitalRead(bot2) == HIGH)
        {
          m++;
          
          if(m > 12)
          {
            m = 1;
          }
        }
        if(digitalRead(bot4) == HIGH)
        {
          m--;
          
          if(m < 1)
          {
            m = 12;
          }  
        }
  }  
  
  delay(tempo);
} 

//=========================================================================Função tocar=====================================================================================//
/*static void tocar()
{
    for(int i = 0; i < 2; i++)
    {
       tone(buzzer, notas[i]);//Passa pelo vetor de notas do buzzer
       delay(tempo);//Tambem aguarda 500 ms mas como aão duas notas para tocar é aguradado 250 ms para cada
    }
}
*/
//=========================================================================Função sensor====================================================================================//
static void sensor()
{
  h = dht.readHumidity();//lê o valor da umidade e armazena na variável h do tipo inteiro
  t = dht.readTemperature();//lê o valor da temperatura e armazena na variável t do tipo float (aceita números com casas decimais)
  if (isnan(h) || isnan(t))//Verifica se a umidade ou temperatura são ou não um número
    {
      return;//Caso não seja um número retorna
    }
}

//=========================================================================Função relogio===================================================================================//
static void relogio()
{
  S++;
  
  if(S > 59)
  {
    M++;
    S = 0;
  }
  
  if(M > 59)
  {
      H++;
      M = 0;
  }
  if(H > 23)
  {
      H = 0;
      d++;
      verificar_dia();
  }  
}

//=========================================================================Função dislcd====================================================================================//
static void dislcd()
{
    lcd.clear();//limpa o painel lcd
    
    lcd.setCursor(0, 0);//Seta o cursor na posição 0, 0 da matriz do lcd
    if(H < 10)//Se o valor de hora for menor que 10
    {
      lcd.print("0");//Adiciona um 0 antes do valor
      lcd.print(H);//Adiciona o valor
    }
    else
    {
      lcd.print(H);//Adiciona somente o valor
    }
    
    lcd.setCursor(2, 0);//Seta o cursor na posição 2, 0 da matriz do lcd
    lcd.print(":");//Adiciona dois pontos antes do valor
    if(M < 10)//Se o valor de minutos for menor que 10
    {
      lcd.print("0");//Adiciona um 0 antes do valor
      lcd.print(M);//Adiciona o valor
    }
    else
    {
      lcd.print(M);//Adiciona somente o valor
    }
    
    lcd.setCursor(5, 0);//Seta o cursor na posição 5, 0 da matriz do lcd
    lcd.print(":");//Adiciona dois pontos antes do valor
    if(S < 10)//Se o valor de segundos for menor que 10
    {
      lcd.print("0");//Adiciona um 0 antes do valor
      lcd.print(S);//Adiciona o valor
    }
    else
    {
      lcd.print(S);//Adiciona somente o valor
    } 
    
    lcd.setCursor(11, 0);//Seta o cursor na posição 11, 0 da matriz do lcd
    if(d < 10)//Se o valor de dia for menor que 10
    {
      lcd.print("0");//Adiciona um 0 antes do valor
      lcd.print(d);//Adiciona o valor
    }
    else
    {
      lcd.print(d);//Adiciona somente o valor
    } 
    
    lcd.setCursor(13, 0);//Seta o cursor na posição 13, 0 da matriz do lcd
    lcd.print("/");//Adiciona uma barra antes do valor
    if(m < 10)//Se o valor de mes for menor que 10
    {
      lcd.print("0");//Adiciona um 0 antes do valor
      lcd.print(m);//Adiciona o valor
    }  
    else
    {
      lcd.print(m);//Adiciona somente o valor
    }
}

//=========================================================================Função verificar_dia=============================================================================//
static void verificar_dia()
{
  if(m == 2)
  {
     if(d > 28)
     {
        d = 1;
        m++;
     }
   }
   else
   {
      if(m >= 1 && m <= 7)
      {
         primeira_metade();
      }
      else
      {
         segunda_metade();
      }
   }
}

//=========================================================================Função primeira_metade===========================================================================//
static void primeira_metade()
{
  if(m % 2 == 0)
     {
        if(d > 30)
        {
           d = 1;
           m++;
        }
     }
     else
     {
        if(d > 31)
        {
           d = 1;
           m++;
        }
     }
}

//=========================================================================Função segunda_metade============================================================================//
static void segunda_metade()
{
  if(m % 2 == 0)
     {
        if(d > 31)
        {
           d = 1;
           m++;
        }
     }
     else
     {
        if(d > 30)
        {
           d = 1;
           m++;
        }
     }
}
