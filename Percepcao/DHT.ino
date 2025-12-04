#include <DHT.h> // DHT sensor adafruit

#define DHTPIN         10
#define DHTTYPE        DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    dht.begin();
}

void loop() {
    float temperatura = dht.readTemperature();
}


CODIGO EXEMPLO
#include "DHT.h"            // Importa a biblioteca do sensor DHT11/DHT22

#define DHTPIN 4            // Pino onde o DHT está conectado
#define DHTTYPE DHT11       // Tipo do sensor (pode trocar para DHT22)

DHT dht(DHTPIN, DHTTYPE);   // Cria o objeto DHT, informando o pino e o tipo

// Estrutura (tipo personalizado) para guardar os dados do sensor
struct DHTData {
  float temperatura;        // Vai guardar a temperatura lida
  float umidade;            // Vai guardar a umidade lida
  bool ok;                  // Indica se a leitura deu certo (true/false)
};

// Função que lê o DHT e devolve tudo organizado
DHTData lerDHT() {
  DHTData data;             // Cria uma variável do tipo DHTData

  data.umidade = dht.readHumidity();       // Lê a umidade do DHT
  data.temperatura = dht.readTemperature(); // Lê a temperatura do DHT

  // Se qualquer leitura falhar, o valor vira "NaN" (Not a Number)
  if (isnan(data.umidade) || isnan(data.temperatura)) {
    data.ok = false;        // Marca que a leitura falhou
  } else {
    data.ok = true;         // Marca que a leitura funcionou
  }

  return data;              // Devolve as informações organizadas
}

void setup() {
  Serial.begin(115200);     // Inicia o monitor serial
  dht.begin();              // Inicializa o sensor DHT
}

void loop() {
  DHTData leitura = lerDHT();   // Chama a função para ler o DHT

  if (!leitura.ok) {            // Se deu erro na leitura...
    Serial.println("Erro ao ler DHT!");  // Mostra mensagem de erro
  } else {
    // Se deu certo, imprime os valores:
    Serial.print("Temp: ");
    Serial.print(leitura.temperatura);
    Serial.print(" °C | Umidade: ");
    Serial.print(leitura.umidade);
    Serial.println(" %");
  }

  delay(2000);               // Espera 2 segundos antes de ler de novo (DHT precisa desse tempo)
}