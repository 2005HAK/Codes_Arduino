
// Código exemplo para teste de Micro Servo Motor SG90 
// Movimento do servo através de comandos especificados 
 
#include "Servo.h" // Inclui a Biblioteca Servo.h 
 
Servo meuservo; // Cria o objeto servo para programação 
int angulo = 0; // Ajusta o ângulo inicial do Servo 
 
void setup() {
meuservo.attach(3); // Declara o pino do servo
}
 
void loop() { 
  
for (angulo = 0; angulo < 180; angulo++) { // Comando que muda a posição do servo de 0 para 180°
meuservo.write(angulo); // Comando para angulo específico
delay(5); 
}
 
delay(2000); // Tempo de espera para próximo movimento
for (angulo = 180; angulo >= 1; angulo--) { // Comando que muda a posição do servo de 180 para 0°
meuservo.write(angulo); // Comando para angulo específico
delay(5);
}
 
delay(2000); // Tempo de espera para próximo movimento
} 
