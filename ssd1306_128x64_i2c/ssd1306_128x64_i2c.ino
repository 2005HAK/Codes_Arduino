#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Thermistor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16


//Pino analógico do arduino no qual o sensor está ligado

Thermistor senTemperatura(A0);
const int senUmidade = A1;

//Tempo de atualização entre as leituras em ms

const int TEMPO_ATUALIZACAO = 1000;

float temperatura;
float umidade;
float antTemperatura;
float antUmidade;

int solenoide = 6;
int lamp = 7;
int regTemp = A2;
int regUmid = A3;

bool ajuste = LOW;

void setup() {

  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(solenoide, OUTPUT);
  pinMode(lamp, OUTPUT);
  pinMode(regTemp, INPUT);
  pinMode(regUmid, INPUT);
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
}

void loop() {

  float temperatura = LerTemperatura();
  float umidade = LerUmidade();
  float regTemp = RegulaTemperatura();
  float regUmid = RegulaUmidade();

  if (temperatura > regTemp) {

    digitalWrite(lamp, HIGH);

  } else {

    digitalWrite(lamp, LOW);

  }

  if (umidade > regUmid) {

    digitalWrite(solenoide, HIGH);

  } else {

    digitalWrite(solenoide, LOW);

  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(9, 0);
  display.print("Planta");
  display.setCursor(80, 2);
  display.print((char)135);
  display.setCursor(93, 0);
  display.print((char)126);
  display.setCursor(93, 1);
  display.print("a");
  display.setCursor(105, 0);
  display.print("o");

  display.setCursor(0, 20);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("Temperatura: ");
  display.print(temperatura);
  display.print((char)247);
  display.print("C");

  display.setCursor(0, 30);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("Umidade: ");
  display.print(umidade);
  display.print("%");

  display.drawLine(0, 42, 128, 42, SSD1306_WHITE);
  
  display.setCursor(0, 47);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("TempMax: ");
  display.print(regTemp);
  display.print((char)247);
  display.print("C");

  display.setCursor(0, 57);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("UmidMax: ");
  display.print(regUmid);
  display.print("%");

  display.display();

  delay(TEMPO_ATUALIZACAO);

}

//Lê umidade
float LerUmidade() {

  float valor;

  float umid = analogRead(senUmidade);
  valor = map(umid, 880, 0, 100, 0);

  return (valor);

}

//Lê temperatura
float LerTemperatura() {

  float temp = senTemperatura.getTemp();

  return (temp);
}

float RegulaTemperatura() {

  float valor;

  float tempReg = analogRead(regTemp);
  valor = map(tempReg, 0, 1024, 125, -40);

  return (valor);

}

float RegulaUmidade() {

  float valor;

  float umidReg = analogRead(regUmid);
  valor = map(umidReg, 0, 1024, 100, -1);

  return (valor);

}
