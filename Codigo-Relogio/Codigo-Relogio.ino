#include <DS1302.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
    
LiquidCrystal_I2C lcd(0x27,16,2);

const int RST = 5;  // Chip Enable
const int DAT = 6;  // Input/Output
const int CLK = 7;  // Serial Clock

DS1302 rtc(RST, DAT, CLK);

void setup() {
  Serial.begin(9600);

 // inicializa o LCD 
  lcd.begin();                     
  lcd.begin();
  lcd.backlight();
  
  // Prepara o relógio e desativa a proteção contra a escrita
  rtc.halt(false);
  rtc.writeProtect(false);

  // Cria um objeto com data e hora
 Time t(2020, 10, 11, 15, 10, 00, 1);
  
  // Define a data e hora no chip. ATENÇÃO: Apenas deve ser executado caso nunca tenha sido definida antes
  rtc.time(t);
}

// Mostra a hora e data a cada segundo
void loop() {
  mostraDataHora();
  delay(1000);
}

//Procedimento que mostra no LCD (e monitor série) a data e hora atual
void mostraDataHora() {

  // Obtém a data atual a partir do chip
  Time t = rtc.time();

  // Chama função para receber o número da semana (3 primeiras letras)
  const String diaS = diaSemana(t.day);


  // Coloca numa variável, a data (no formato "##-##-#### (DIA)")
  char data[17];
  snprintf(data, sizeof(data), "%02d-%02d-%04d (%s)", t.date, t.mon, t.yr, diaS.c_str());
  // Coloca numa variável, a hora (no formato "##:##:##")
  char hora[9];
  snprintf(hora, sizeof(hora), "%02d:%02d:%02d",t.hr, t.min, t.sec);
  
  // Mostra a data e hora no LCD
  lcd.setCursor(0,0);
  lcd.print(data);
  lcd.setCursor(0,1);
  lcd.print(hora);

  // Mostra a data e hora no monitor série
  Serial.println(data);
  Serial.println(hora);
}

//Função que devovde o dia da semana a partir de número (1=domingo, etc...) 
String diaSemana(const int dia) {
  switch (dia) {
    case 1: return "DOM";
    case 2: return "SEG";
    case 3: return "TER";
    case 4: return "QUA";
    case 5: return "QUI";
    case 6: return "SEX";
    case 7: return "SAB";
  }
}
