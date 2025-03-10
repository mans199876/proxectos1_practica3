/*
Libreria para el control de sensores de ultrasonidos
Creada por Manuel Fernandez Uceira el 06/02/2025
Ultima modificacion: 06/02/2025 12:47
*/

//Librerias necesarias
#include <arduino.h>

class ultrasonidos{
    public:
    ultrasonidos(){
        trigger = 5;
        echo = 4;
    }
    ultrasonidos(int trig, int Echo){
        trigger = trig;
        echo = Echo;
    }
    
    void iniciar()
    {
      pinMode(trigger, OUTPUT);
      pinMode(echo, INPUT);
    }
    long medicion(){
        long tiempo;
        long distancia;

        digitalWrite(trigger, LOW);
        delayMicroseconds(5);
        digitalWrite(trigger, HIGH);
        delayMicroseconds(15);
        digitalWrite(trigger, LOW);

        tiempo = pulseIn(echo, HIGH);
        distancia = tiempo * 0.01657;

        return (distancia);
    }
    private:
    int trigger, echo;
};