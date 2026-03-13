const int pinReceptor = 7;
const int tiempoBit = 25; // Milisegundos (ajustable según estabilidad)

void setup() {
  pinMode(pinReceptor, INPUT);
  Serial.begin(9600);
  Serial.println("--- Receptor Óptico Listo ---");
  Serial.println("Estado Idle: Láser encendido (Luz detectada)");
}

void loop() {
  // 1. Detectar Bit de Inicio
  // Dado que el láser está HIGH en reposo, el fotodiodo entrega LOW.
  // El Bit de Inicio apaga el láser (Oscuridad), por lo que el pin sube a HIGH.
  if (digitalRead(pinReceptor) == HIGH) {

    // 2. Sincronización: Muestreo al centro del bit (1.5 * T)
    delay(tiempoBit * 1.5);

    byte datoRecibido = 0;

    // 3. Lectura de los 8 bits de datos (LSB First)
    for (int i = 0; i < 8; i++) {
      // Leemos el estado actual
      int lectura = digitalRead(pinReceptor);

      // Inversión de Lógica:
      // Si hay luz (Láser ON), el pin está LOW -> Interpretamos como 1 lógico.
      // Si hay oscuridad (Láser OFF), el pin está HIGH -> Interpretamos como 0 lógico.
      if (lectura == LOW) {
        datoRecibido |= (1 << i);
      }

      delay(tiempoBit); // Esperar al centro del siguiente bit
    }

    // 4. Verificación de Bit de Parada (Opcional pero recomendado)
    // El bit de parada es Láser ON (LOW en el sensor).
    delay(tiempoBit);

    // 5. Mostrar resultado
    Serial.print((char)datoRecibido);
  }
}
