#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11,10, 5, 4, 3, 2);

void setup()
{
 pinMode(12, OUTPUT);
 pinMode(11, OUTPUT);
  
  //inicia o LCD com dimensões 16 x 2
  lcd.begin(16, 2);
}

void loop()
{
  //Apaga o conteudo exibido no display
 lcd.clear();
  
  //posiciona o cursor na posição especificada
  lcd.setCursor(0, 0);
  
  //Ixibe no LCD
  lcd.print("Eai, como vai?");
  
  lcd.setCursor(0, 1);
  
  lcd.print("Deu certo:)");
  
  delay(2000);
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  
  lcd.print("to trocando");
  
  lcd.setCursor(0, 1);
  
  lcd.print("de frase");
  
  delay(2000);
}
