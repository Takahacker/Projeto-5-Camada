int baudRate = 9600;
int paridadeTipo = 0; // 0 para paridade par, 1 para paridade ímpar
int receptorPin = 2; // Pino usado para transmissão

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

void funcaoEsperaMeioPeriodo(){
  for(int i = 0; i < 8333/2; i++){
    asm("NOP");
  }
}

bool verificarParidade(byte data, int paridadeRecebida){
  int paridadeCalculada = calcularParidade(data);
  return paridadeCalculada == paridadeRecebida;
}

void lerFrame(){
  // espera pelo start bit (deve ser 0)
  while (digitalRead(receptorPin) == HIGH);
  funcaoEspera();
  funcaoEsperaMeioPeriodo();

  //start bit detectado, agora ler os outros bits
  byte caracter = 0;  // Inicializa o byte
  for (int i = 0; i < 8; i++){
    caracter |= (digitalRead(receptorPin) << i);
    funcaoEspera();
  }

  // recebe paridade
  int paridadeRecebida = digitalRead(receptorPin);
  funcaoEspera();

  // recebe stop bit
  int stopBit = digitalRead(receptorPin);

  // verifica paridade
  if (verificarParidade(caracter, paridadeRecebida)){
    Serial.println("Paridade correta!");
    Serial.println("Caractere recebido:");
    Serial.println(char(caracter));
  }
  else{
    Serial.println("Erro de paridade!");
  }
}

void setup() {
  Serial.begin(baudRate);
  pinMode(receptorPin, INPUT);
}

void loop() {
  lerFrame();
}
