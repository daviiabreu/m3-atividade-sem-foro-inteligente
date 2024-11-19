// Inclusão das bibliotecas necessárias
#include <WiFi.h>        // Biblioteca para conexão WiFi
#include <PubSubClient.h> // Biblioteca para comunicação MQTT
#include <WiFiClientSecure.h> // Biblioteca para conexão segura
#include <Ticker.h>      // Biblioteca para temporização não-bloqueante
// Definição dos pinos para o primeiro semáforo
#define PINO_VERMELHO1 32
#define PINO_AMARELO1 33
#define PINO_VERDE1 26
// Definição dos pinos para o segundo semáforo
#define PINO_VERMELHO2 18
#define PINO_AMARELO2 16
#define PINO_VERDE2 4
// Pino do sensor de luminosidade
#define PINO_LDR 34
// Configurações da rede WiFi
const char* ssid = "Marco_Ruas";
const char* password = "12345678";
// Configurações do servidor MQTT (HiveMQ Cloud)
const char* mqtt_server = "706f3a6885be461ea18a14eeca8916ee.s1.eu.hivemq.cloud";
const int mqtt_port = 8883; // Porta SSL
const char* mqtt_user = "admin";
const char* mqtt_password = "Admin1234";
// Objetos para conexão WiFi e MQTT
WiFiClientSecure espClient;
PubSubClient client(espClient);
// Classe para controle do semáforo
class Semaforo {
  private:
    short int vermelho;
    short int amarelo;
    short int verde;
  public:
    // Construtor - inicializa os pinos do semáforo
    Semaforo(short int pinoVerm, short int pinoVerde, short int pinoAmar) {
      this->vermelho = pinoVerm;
      this->amarelo = pinoAmar;
      this->verde = pinoVerde;
    }
    // Inicializa os pinos como saída
    void init() {
      pinMode(this->vermelho, OUTPUT);
      pinMode(this->amarelo, OUTPUT);
      pinMode(this->verde, OUTPUT);
    }
    // Abre o semáforo (verde ligado)
    void abrir() {
      digitalWrite(this->vermelho, LOW);
      digitalWrite(this->amarelo, LOW);
      digitalWrite(this->verde, HIGH);
    }
    // Estado de atenção (amarelo ligado)
    void esperar() {
      digitalWrite(this->vermelho, LOW);
      digitalWrite(this->amarelo, HIGH);
      digitalWrite(this->verde, LOW);
    }
    // Fecha o semáforo (vermelho ligado)
    void fechar() {
      digitalWrite(this->vermelho, HIGH);
      digitalWrite(this->amarelo, LOW);
      digitalWrite(this->verde, LOW);
    }
    // Desliga todas as luzes
    void desligarTodos() {
      digitalWrite(this->vermelho, LOW);
      digitalWrite(this->amarelo, LOW);
      digitalWrite(this->verde, LOW);
    }
    // Alterna o estado do LED amarelo (usado no modo noturno)
    void alternarAmarelo() {
      digitalWrite(this->amarelo, !digitalRead(this->amarelo));
    }
};
// Criação dos objetos dos semáforos
Semaforo semaforo1(PINO_VERMELHO1, PINO_VERDE1, PINO_AMARELO1);
Semaforo semaforo2(PINO_VERMELHO2, PINO_VERDE2, PINO_AMARELO2);
// Tickers para controle de tempo
Ticker timerSemaforo;        // Controla os tempos dos estados do semáforo
Ticker timerPiscaNoturno1;   // Controla o pisca do primeiro semáforo no modo noturno
Ticker timerPiscaNoturno2;   // Controla o pisca do segundo semáforo no modo noturno
// Variáveis de controle
bool modoNoturno = false;
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
String message = "normal";
// Enumeração dos possíveis estados do semáforo
enum EstadoSemaforo {
  SEMAFORO1_VERDE,
  SEMAFORO1_AMARELO,
  SEMAFORO1_VERMELHO,
  SEMAFORO2_VERDE,
  SEMAFORO2_AMARELO,
  SEMAFORO2_VERMELHO
};
EstadoSemaforo estadoAtual = SEMAFORO1_VERDE;
// Função que gerencia as transições de estado do semáforo
void gerenciarEstadoSemaforo() {
  switch (estadoAtual) {
    case SEMAFORO1_VERDE:
      semaforo1.abrir();
      semaforo2.fechar();
      estadoAtual = SEMAFORO1_AMARELO;
      timerSemaforo.once(3, gerenciarEstadoSemaforo); // Agenda próxima transição em 3 segundos
      break;
    case SEMAFORO1_AMARELO:
      semaforo1.esperar();
      semaforo2.fechar();
      estadoAtual = SEMAFORO1_VERMELHO;
      timerSemaforo.once(1, gerenciarEstadoSemaforo); // Agenda próxima transição em 1 segundo
      break;
    case SEMAFORO1_VERMELHO:
      semaforo1.fechar();
      semaforo2.abrir();
      estadoAtual = SEMAFORO2_AMARELO;
      timerSemaforo.once(3, gerenciarEstadoSemaforo); // Agenda próxima transição em 3 segundos
      break;
    case SEMAFORO2_AMARELO:
      semaforo1.fechar();
      semaforo2.esperar();
      estadoAtual = SEMAFORO2_VERMELHO;
      timerSemaforo.once(1, gerenciarEstadoSemaforo); // Agenda próxima transição em 1 segundo
      break;
    case SEMAFORO2_VERMELHO:
      semaforo1.fechar();
      semaforo2.fechar();
      estadoAtual = SEMAFORO1_VERDE;
      timerSemaforo.once(1, gerenciarEstadoSemaforo); // Agenda próxima transição em 1 segundo
      break;
  }
}
// Função de callback para mensagens MQTT recebidas
void callback(char* topic, byte* payload, unsigned int length) {
  message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println("callback " + message);
}
// Função para conectar ao WiFi
void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi");
  espClient.setInsecure(); // Desabilita verificação SSL para teste
}
// Função para reconectar ao broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao HiveMQ...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("conectado");
      client.subscribe("hivemqdemo/commands");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}
// Função para iniciar o modo noturno
void iniciarModoNoturno() {
  modoNoturno = true;
  timerSemaforo.detach(); // Desativa o timer do modo normal
  semaforo1.desligarTodos();
  semaforo2.desligarTodos();
  // Inicia o pisca-pisca dos amarelos
  timerPiscaNoturno1.attach(1, []() { semaforo1.alternarAmarelo(); });
  timerPiscaNoturno2.attach(1, []() { semaforo2.alternarAmarelo(); });
}
// Função para parar o modo noturno
void pararModoNoturno() {
  modoNoturno = false;
  timerPiscaNoturno1.detach(); // Desativa os timers do modo noturno
  timerPiscaNoturno2.detach();
  semaforo1.desligarTodos();
  semaforo2.desligarTodos();
}
// Função de configuração inicial
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  semaforo1.init();
  semaforo2.init();
  pinMode(PINO_LDR, INPUT);
  // Inicia o ciclo normal do semáforo
  gerenciarEstadoSemaforo();
}
// Loop principal
void loop() {
  // Verifica conexão MQTT
  if (!client.connected()) {
    reconnect();
  }
  // Lê valor do sensor de luminosidade
  int valorLDR = analogRead(PINO_LDR);
  String ldrString = String(valorLDR);
  client.publish("hivemqdemo/commands", ldrString.c_str());
  if (valorLDR > 2000 && modoNoturno && message != "noturno") {
  pararModoNoturno();
  gerenciarEstadoSemaforo();
}
  // Modo normal
  if (message == "normal" && valorLDR > 2000) {
    if (modoNoturno) {
      pararModoNoturno();
      gerenciarEstadoSemaforo();
    }
  }
  // Modo noturno
  else if (message == "noturno" || valorLDR <= 2000) {
    if (!modoNoturno) {
      iniciarModoNoturno();
    }
  }
  // Forçar semáforo 1 aberto
  else if (message == "semaforo1" && valorLDR > 2000) {
    timerSemaforo.detach();
    pararModoNoturno();
    semaforo1.abrir();
    semaforo2.fechar();
  }
  // Forçar semáforo 2 aberto
  else if (message == "semaforo2" && valorLDR > 2000) {
    timerSemaforo.detach();
    pararModoNoturno();
    semaforo1.fechar();
    semaforo2.abrir();
  }
  client.loop(); // Mantém a conexão MQTT ativa
}