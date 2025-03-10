//Importamos librerias necesarias
#include "ultrasonidos.cpp"

//Declaramos las variables y sensores necesarios
ultrasonidos sensor1(6, 7);
#define transmisor 3
#define receptor A0
#define led 13

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
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(receptor, INPUT);
  sensor1.iniciar();

}

void loop() {
  // put your main code here, to run repeatedly:
  enviar_datos_pwm(transmisor, sensor1.medicion());
  if (recibir_datos_pwm(receptor) <= (30 * 255 / 100)) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);

}
