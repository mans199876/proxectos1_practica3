//Importamos librerias necesarias
#include "ultrasonidos.cpp"

//Declaramos las variables y sensores necesarios
ultrasonidos sensor1(6, 7);
#define transmisor 10
#define receptor A0

//Funciones para la transmision y la recepcion
float recibir_datos_pwm(int pin)
{
  unsigned long duracion = pulseIn(pin, HIGH);
  double dutycicle = (duracion / 2145.0) * 255;
  float distancia_trans = round((dutycicle / 255) * 400);
  return distancia_trans;
}
void enviar_datos_pwm(int pin, long datos)
{
  float distancia_trans = float(datos) / 400 * 255;
  int pwm = int(distancia_trans);
  analogWrite(transmisor, pwm);
}

//Programa principal
void setup() {
  // put your setup code here, to run once:
  sensor1.iniciar();
  pinMode(transmisor, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  float datos_arduino_a = recibir_datos_pwm(receptor);
  if (datos_arduino_a <= float(sensor1.medicion())) analogWrite(transmisor, 50);
  else analogWrite(transmisor, 255);
  delay(1000);

}
