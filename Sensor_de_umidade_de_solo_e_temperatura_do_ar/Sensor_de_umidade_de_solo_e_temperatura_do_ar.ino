// C++ code

#include <LiquidCrystal.h>

//Pino analógico do arduino no qual o sensor está ligado
const int senTemperatura = A0;
const int senUmidade = A1;

//Tempo de atualização entre as leituras em ms
const int TEMPO_ATUALIZACAO = 1000;

float temperatura;
float umidade;
int solenoide = 6;
int lamp = 7;

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(solenoide, OUTPUT);
  pinMode(lamp, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop()
{
  float temperatura = LerTemperatura();
  float umidade = LerUmidade();

  if(temperatura < 15){
    digitalWrite(lamp, HIGH);
  }else{
    digitalWrite(lamp, LOW);
  }
  
  if(umidade < 70){
    digitalWrite(solenoide, HIGH);
  } else {
    digitalWrite(solenoide, LOW);
  }
  
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.write(B11011111);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.print(umidade);
  lcd.print("%");
  
  delay(TEMPO_ATUALIZACAO);
}

//Lê umidade
float LerUmidade(){
  float valor;
  float umid = analogRead(senUmidade);
  valor = map(umid,880,0,100,0);
  return (valor);
}

//Lê temperatura
float LerTemperatura(){
  float valor;
  float temp = analogRead(senTemperatura);
  valor = map(temp,390,0,125,-40);
  return (valor);
}
