const int pinLaser = 8;
const int tiempoBit = 25; // Debe coincidir exactamente con el receptor

void setup() {
  pinMode(pinLaser, OUTPUT);
  Serial.begin(9600);

  // Estado inicial: Láser encendido
  digitalWrite(pinLaser, HIGH);

  Serial.println("--- Emisor Óptico Listo ---");
  Serial.println("Escribe un mensaje y presiona Enter:");
}

void loop() {
  if (Serial.available() > 0) {
    char caracter = Serial.read();
    enviarCaracter(caracter);
  }
}

void enviarCaracter(char c) {
  // 1. Bit de Inicio (Láser Apagado = LOW)
  digitalWrite(pinLaser, LOW);
  delay(tiempoBit);

  // 2. Enviar 8 bits de datos (LSB First)
  for (int i = 0; i < 8; i++) {
    bool bitActual = bitRead(c, i);

    // Si el bit es 1, el láser se enciende (HIGH)
    // Si el bit es 0, el láser se apaga (LOW)
    digitalWrite(pinLaser, bitActual ? HIGH : LOW);
    delay(tiempoBit);
  }

  // 3. Bit de Parada (Láser Encendido = HIGH)
  digitalWrite(pinLaser, HIGH);
  delay(tiempoBit);

  // Pequeña pausa de seguridad antes del siguiente carácter
  delay(tiempoBit);
}

