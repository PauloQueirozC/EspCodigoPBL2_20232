#include "dht11.h"


#define TX 1
#define RX 3
#define DHT11PIN 5


dht11 DHT11;
char request = 0;
char address = 0;
char answer[2] = {2,2};

/* 
 * Ler dois Bytes do pino Serial sendo o primeiro a requisição
 * e o segundo o endereço do sensor 
 */
void receivingData(){
  request = Serial.read();
  address = Serial.read();
}

/* 
 * Define como resposta uma mensagem de erro no primeiro Byte e 
 * o endereço do sensor no segundo Byte
 */
void setErroMensage(){
  answer[0] = 0x1F;
  answer[1] = address;
}

/* 
 * Define como resposta o valor em int da temperatura no
 * primeiro Byte e o código de resposta da temperatura no 
 * segundo Byte
 */
void setTempMensage(){
  answer[0] = (char) DHT11.temperature;
  answer[1] = 0x09;
}

/* 
 * Define como resposta o valor em int da umidade no
 * primeiro Byte e o código de resposta da umidade no 
 * segundo Byte
 */
void setHumidMensage(){
  answer[0] = (char) DHT11.humidity;
  answer[1] = 0x08;
}

/* 
 * Define como resposta o código de confirmação do  
 * encerramento do sensoriamento continuo da temperatura 
 * no primeiro Byte e o endereço do sensor no segundo Byte
 */
void setEndSensingTemp(char sensingAddress){
  answer[0] = 0x0A;
  answer[1] = sensingAddress;
}

/* 
 * Define como resposta o código de confirmação do  
 * encerramento do sensoriamento continuo da umidade 
 * no primeiro Byte e o endereço do sensor no segundo Byte
 */
void setEndSensingHumid(char sensingAddress){
  answer[0] = 0x0B;
  answer[1] = sensingAddress;
}

/*
 * Envia pelo pino serial a resposta definida no momento
 */
void sendByts(){
  Serial.print(answer[0]);
  Serial.print(answer[1]);
}

/*
 * Ler o valor da temperatura do sensor DHT11 e solicitar
 * o envio
 */
void sendTemp(int pinDHT11){
  int chk = DHT11.read(pinDHT11);
  if (chk < -1) setErroMensage();
  else setTempMensage();
  sendByts();
}

/*
 * Ler o valor da umidade do sensor DHT11 e solicitar
 * o envio
 */
void sendHumid(int pinDHT11){
  int chk = DHT11.read(pinDHT11);
  if (chk < -1) setErroMensage();
  else setHumidMensage();
  sendByts();
}

/* 
 * Inicia o sensoriamento continuo da temperatura
 */
void continuousSensingTemp(int pinDHT11){
  char addressSensing = address;
  while (!(request == 0x05 && address == addressSensing)) {
    sendTemp(pinDHT11);
    delay(2000);
    if (Serial.available() > 1){
      receivingData();
    }
  }
  setEndSensingTemp(addressSensing);
  sendByts();
}

/* 
 * Inicia o sensoriamento continuo da umidade
 */
void continuousSensingHumid(int pinDHT11){
  char addressSensing = address;
  while (!(request == 0x06 && address == addressSensing)) {
    sendHumid(pinDHT11);
    delay(3000);
    if (Serial.available() > 1){
      receivingData();
    }
  }
  setEndSensingHumid(addressSensing);
  sendByts();
}


/*
 * Define a comunicação serial para a frequência 
 * de 9600Hz
 */
void setup() {
  Serial.begin(9600);
}

/*
 * Main
 */
void loop() {
  // Verifica se chegou alguma solicitação 
  if (Serial.available() > 1){
    receivingData();
    // Verifica qual endereço do sensor foi solicitado e se ele existe
    switch (address) {
      case 0x00:
        // Verifica qual foi a requisição e se ela existe
        switch (request){
          // Sensor funcionando
          case 0x00:
          {
            int chk = DHT11.read(DHT11PIN);
            if (chk < -1) answer[0] = 0x1F;
            else answer[0] = 0x07;
            answer[1] = address;
            sendByts();
          }
          break;
          // Valor da temperatura
          case 0x01:
            sendTemp(DHT11PIN);
          break;
          // Valor da umidade
          case 0x02:
            sendHumid(DHT11PIN);
          break;
          // Inicio do sensoriamento continuo da temperatura
          case 0x03:
            continuousSensingTemp(DHT11PIN);
          break;
          // Inicio do sensoriamento continuo da umidade
          case 0x04:
            continuousSensingHumid(DHT11PIN);
          break;
          // Fim do sensoriamento continuo da temperatura
          case 0x05:
            setEndSensingTemp(address);
            sendByts();
          break;
          // Fim do sensoriamento continuo da umidade
          case 0x06:
            setEndSensingHumid(address);
            sendByts();
          break;
          // Requisição não existente
          default:
          {
            answer[0] = 0x3F;
            answer[1] = address;
            sendByts();
          }
          break;
        }
      // Sensor não existente
      default:
        answer[0] = 0x2F;
        answer[1] = address;
        sendByts();
        break;
    }
    delay(3000);
  }
}
