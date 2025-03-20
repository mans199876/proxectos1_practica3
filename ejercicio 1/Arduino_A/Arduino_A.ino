#define TRIG_PIN1 3  // Pin TRIG del sensor 1
#define ECHO_PIN1 2  // Pin ECHO del sensor 1
#define TRIG_PIN2 5  // Pin TRIG del sensor 2
#define ECHO_PIN2 4  // Pin ECHO del sensor 2
#define MAX_DISTANCE 200 // Distancia máxima en cm
#define UMBRAL_CAMBIO 10 // Cambio en cm necesario para reanudar el envío

bool enviarDatos = true; // Variable de control
int ultimaDistancia = -1; // Última distancia registrada

void setup() {
    Serial.begin(9600);  // Comunicación con Arduino B

    pinMode(TRIG_PIN1, OUTPUT);
    pinMode(ECHO_PIN1, INPUT);
    pinMode(TRIG_PIN2, OUTPUT);
    pinMode(ECHO_PIN2, INPUT);

    Serial.println("Arduino A: Iniciando...");
}

// Función para medir la distancia con un sensor ultrasónico
long medirDistancia(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duracion = pulseIn(echoPin, HIGH);
    long distancia = duracion * 0.034 / 2; // Convertir tiempo a distancia en cm

    if (distancia == 0) distancia = MAX_DISTANCE; // Evitar valores nulos
    return distancia;
}

void loop() {
    // Verifica si hay un mensaje de Arduino B
    if (Serial.available() > 0) {
        String mensaje = Serial.readString();
        mensaje.trim(); // Eliminar espacios o saltos de línea

        if (mensaje == "stop") {
            enviarDatos = false; // Detener envío de datos temporalmente
            Serial.println("Arduino A: Envío de datos detenido.");
        }
    }

    // Medir distancias aunque el envío esté detenido
    medir();

    // Si la diferencia con la última distancia registrada es mayor al umbral, reanudar envío
    if (!enviarDatos && ultimaDistancia != -1 && abs(distanciaMin - ultimaDistancia) > UMBRAL_CAMBIO) {
        enviarDatos = true;
        Serial.println("Arduino A: Cambio detectado, reanudando envío de datos...");
    }

    // Actualizar la última distancia registrada
    ultimaDistancia = distanciaMin;

    // Si está activado el envío de datos, mandar la información a Arduino B
    if (enviarDatos) enviarDatos();

    delay(500); // Pequeña pausa antes de la siguiente lectura
}

void medir()
{
  int distancia1 = medirDistancia(TRIG_PIN1, ECHO_PIN1);
  int distancia2 = medirDistancia(TRIG_PIN2, ECHO_PIN2);
  int distanciaMin = min(distancia1, distancia2);
}

void enviarDatos()
{
  Serial.print("Sensor detecta: ");
  Serial.print(distanciaMin);
  Serial.println(" cm");
  Serial.println(distanciaMin); // Enviar solo el número para que Arduino B lo lea fácilmente
    
}

