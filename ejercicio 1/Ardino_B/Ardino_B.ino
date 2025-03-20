#define LED_PIN 2 // Pin donde está conectado el LED en Arduino B

void setup() {
    Serial.begin(9600); // Comunicación con Arduino A
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Arduino B: Iniciando...");
}

void loop() {
    if (Serial.available() > 0) { // Verifica si hay datos entrantes
        int distancia = Serial.parseInt(); // Recibe la distancia

        if (distancia > 0) {
            Serial.print("Arduino B: Distancia recibida: ");
            Serial.print(distancia);
            Serial.println(" cm");

            if (distancia < 50) { // Si la distancia es menor a 50 cm
                digitalWrite(LED_PIN, HIGH); // Encender LED
                Serial.println("Arduino B: LED ENCENDIDO (Distancia < 50 cm)");

                // Enviar mensaje de stop a Arduino A
                Serial.println("stop");
            } else {
                digitalWrite(LED_PIN, LOW); // Apagar LED
                Serial.println("Arduino B: LED APAGADO");
            }
        }
    }
}
