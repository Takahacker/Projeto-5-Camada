const int txPin = 7;  // Pino de transmissão (escolha um pino digital qualquer)
const int baudRate = 9600;  // Baudrate de 9600 bps
const int bitDelay = 1000000 / baudRate;  // Tempo entre os bits baseado no baudrate

void setup() {
  pinMode(txPin, OUTPUT);
  digitalWrite(txPin, HIGH);  // O estado padrão do pino é HIGH (idle)
}

void loop() {
  char data = 'A';  // Caractere a ser transmitido (pode ser alterado)
  sendByte(data);   // Envia o caractere
  delay(1000);  // Envia o caractere a cada 1 segundo
}

void sendByte(char data) {
  // Start bit (0)
  digitalWrite(txPin, LOW);
  delayMicroseconds(bitDelay);

  // Enviar os 8 bits de dados (LSB primeiro)
  for (int i = 0; i < 8; i++) {
    digitalWrite(txPin, (data >> i) & 0x01);  // Extrai e envia cada bit
    delayMicroseconds(bitDelay);
  }

  // Bit de paridade (calculado para ser par)
  int parity = calculateParity(data);
  digitalWrite(txPin, parity);  // Envia o bit de paridade
  delayMicroseconds(bitDelay);

  // Stop bit (1)
  digitalWrite(txPin, HIGH);
  delayMicroseconds(bitDelay);
}

int calculateParity(char data) {
  // Calcula a paridade par (XOR de todos os bits)
  int parity = 0;
  for (int i = 0; i < 8; i++) {
    parity ^= (data >> i) & 0x01;
  }
  return parity;
}