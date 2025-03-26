#define LED_PIN 2 // Pin del LED en Arduino B

bool alertaActivada = false; // Controla si ya se ha activado el estado de alerta

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Arduino B: Iniciando...");
}

void loop() {
    if (alertaActivada) return; // Si ya se activó la alerta, salir del loop

    if (Serial.available() > 0) {
        int distancia = Serial.parseInt(); // Recibir distancia

        if (distancia > 0) {
            Serial.print("Distancia recibida: ");
            Serial.print(distancia);
            Serial.println(" cm");

            if (distancia < 50) {
                digitalWrite(LED_PIN, HIGH);
                Serial.println("(Distancia < 50 cm)");

                delay(10); // Pausa para asegurar la transmisión
                Serial.println("stop"); // Enviar señal de detención a Arduino A

                Serial.end(); // Finaliza la comunicación serial
                alertaActivada = true; // Marca que ya se activó
            } else {
                digitalWrite(LED_PIN, LOW);
                Serial.println("LED APAGADO");
            }
        }

        // Limpia cualquier byte sobrante
        while (Serial.available()) Serial.read();
    }
}
