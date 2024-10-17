int baudRate = 9600;
int paridadeTipo = 0; // 0 para paridade par, 1 para paridade ímpar
int transmissorPin = 2; // Pino usado para transmissão

// Função para calcular o bit de paridade
int calcularParidade(char data) {
  int paridade = 0;
  
  // Conta o número de bits "1" no dado (ASCII value)
  for (int i = 0; i < 8; i++) {
    paridade += (data >> i) & 0x01;
  }

  return paridade % 2;
}

void funcaoEspera(){
  for(int i = 0; i < 8333; i++){
    asm("NOP");
  }
}

// Função para construir o frame serial com start, stop e paridade


void enviarFrame(char caracter){
    digitalWrite(transmissorPin, LOW);
    funcaoEspera();
    for (int i = 0; i < 8; i++){
      int bit = (caracter >> i) & 0x01;
      digitalWrite(transmissorPin, bit);
      funcaoEspera();
  }
  int paridade = calcularParidade(caracter);
  digitalWrite(transmissorPin, paridade);
  funcaoEspera();
  digitalWrite(transmissorPin, HIGH);
}


void setup() {
 // Inicializar a comunicação serial
  pinMode(transmissorPin, OUTPUT);
  digitalWrite(transmissorPin, HIGH);
  Serial.begin(baudRate); 
}

void loop() {
  char caractere = 'A'; // Exemplo de caractere a ser transmitido (A = 65 em ASCII)
  // Enviar o frame serial
  enviarFrame(caractere);
  Serial.println("Caractere enviado:");
  Serial.println(caractere);
  Serial.println(caractere,BIN);
}
