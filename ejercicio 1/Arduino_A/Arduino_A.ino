#define TRIG_PIN1 3  // Pin TRIG del sensor 1
#define ECHO_PIN1 2  // Pin ECHO del sensor 1
#define TRIG_PIN2 5  // Pin TRIG del sensor 2
#define ECHO_PIN2 4  // Pin ECHO del sensor 2
#define MAX_DISTANCE 200 // Distancia máxima en cm
#define UMBRAL_CAMBIO 10 // Umbral de cambio para reanudar envío

bool permitirEnvio = true;
int ultimaDistancia = -1;

void setup() {
    Serial.begin(9600);

    pinMode(TRIG_PIN1, OUTPUT);
    pinMode(ECHO_PIN1, INPUT);
    pinMode(TRIG_PIN2, OUTPUT);
    pinMode(ECHO_PIN2, INPUT);
}

long medirDistancia(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duracion = pulseIn(echoPin, HIGH);
    long distancia = duracion * 0.034 / 2;

    if (distancia == 0) distancia = MAX_DISTANCE;
    return distancia;
}

int medir() {
    int distancia1 = medirDistancia(TRIG_PIN1, ECHO_PIN1);
    int distancia2 = medirDistancia(TRIG_PIN2, ECHO_PIN2);
    return min(distancia1, distancia2);
}

void loop() {
    if (Serial.available() > 0) {
        String mensaje = Serial.readString();
        mensaje.trim();

        if (mensaje == "stop") {
            permitirEnvio = false;
        }
    }

    int distanciaMin = medir();

    if (!permitirEnvio && ultimaDistancia != -1 && abs(distanciaMin - ultimaDistancia) > UMBRAL_CAMBIO) {
        permitirEnvio = true;
    }

    ultimaDistancia = distanciaMin;

    if (permitirEnvio) {
        Serial.println(distanciaMin); // Solo el número, sin texto
    }

    delay(500);
}

