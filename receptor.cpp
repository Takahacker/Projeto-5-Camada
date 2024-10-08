const int rxPin = 8;  // Pino de recepção (pino digital qualquer)
const int baudRate = 9600;  // Baudrate de 9600 bps
const int bitDelay = 1000000 / baudRate;  // Tempo entre os bits baseado no baudrate

void setup() {
  pinMode(rxPin, INPUT);
  Serial.begin(9600);  // Inicia a comunicação serial para monitorar no PC
}

void loop() {
  if (digitalRead(rxPin) == LOW) {  // Detecta o start bit (LOW)
    char receivedByte = readByte();
    int parityBit = readBit();

    // Verificação da paridade
    if (calculateParity(receivedByte) == parityBit) {
      Serial.print("Caractere recebido: ");
      Serial.println(receivedByte);  // Exibe o caractere recebido no monitor serial
    } else {
      Serial.println("Erro de paridade!");  // Se a paridade estiver incorreta
    }

    // Aguarda o stop bit
    while (digitalRead(rxPin) == LOW);  // Espera pelo fim do stop bit
  }
}

char readByte() {
  char data = 0;
  delayMicroseconds(bitDelay);  // Espera o tempo do start bit

  // Lê os 8 bits de dados (LSB primeiro)
  for (int i = 0; i < 8; i++) {
    data |= (digitalRead(rxPin) << i);  // Constrói o byte recebido bit a bit
    delayMicroseconds(bitDelay);
  }
  return data;
}

int readBit() {
  delayMicroseconds(bitDelay);  // Espera o tempo de um bit
  return digitalRead(rxPin);  // Retorna o valor do bit de paridade
}

int calculateParity(char data) {
  // Calcula a paridade par (XOR de todos os bits)
  int parity = 0;
  for (int i = 0; i < 8; i++) {
    parity ^= (data >> i) & 0x01;
  }
  return parity;
}