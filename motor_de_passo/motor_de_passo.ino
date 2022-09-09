#include <Stepper.h>

int passosPorVolta=32; // Quantos passos o motor interno é capaz de dar em uma volta

Stepper mp(passosPorVolta, 8, 9, 10, 11);

void setup() {

mp.setSpeed(500); //Velocidade do motor em RPM

}

void loop() 
{
  mp.step(100); // Passos que o motor vai dar
  delay(10);
  mp.step(-100);
  delay(10);
  mp.step(200);
  delay(10);
}
