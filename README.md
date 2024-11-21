# Inteli - Instituto de Tecnologia e Liderança 

<p align="center">
<a href= "https://www.inteli.edu.br/"><img src="assets/inteli.png" alt="Inteli - Instituto de Tecnologia e Liderança" border="0" width=40% height=40%></a>
</p>

<br>

# Nome do grupo:

## BiMu

## 👨‍🎓 Integrantes: 

<div align="center">
  <table>
    <tr>
      <td align="center"><a href="https://www.linkedin.com/in/davi-abreu-da-silveira/"><img style="border-radius: 10%;" src="./assets/imagens_integrantes/abreu.jpg" width="100px;" alt="Foto de Davi Abreu" /><br><sub><b>Davi Abreu</b></sub></a></td>
      <td align="center"><a href="https://www.linkedin.com/in/isadoragatto/"><img style="border-radius: 10%;" src="./assets/imagens_integrantes/basa.jpg" width="100px;" alt="Foto de Davi Basã"/><br><sub><b>Davi Basã</b></sub></a></td>
      <td align="center"><a href="https://www.linkedin.com/in/j%C3%BAlia-lika-ishikawa/"><img style="border-radius: 10%;" src="./assets/imagens_integrantes/felipe.png" width="100px;" alt="Foto de Felipe Zillo"/><br><sub><b>Felipe Zillo</b></sub></a></td>
      <td align="center"><a href="https://www.linkedin.com/in/murilo-couto-oliveira/"><img style="border-radius: 10%;" src="./assets/imagens_integrantes/leonardo.jpg" width="100px;" alt="Foto de Leonardo Ogata"/><br><sub><b>Leonardo Ogata</b></sub></a></td>
      <td align="center"><a href="https://www.linkedin.com/in/marcoruas/"><img style="border-radius: 10%;" src="./assets/imagens_integrantes/marco.jpg" width="100px;" alt="Foto de Marco Ruas"/><br><sub><b>Marco Ruas</b></sub></a></td>
      <td align="center"><a href="https://www.linkedin.com/in/renan-reis-483a10289/"><img style="border-radius: 10%;" src="./assets/imagens_integrantes/rafael.jpg" width="100px;" alt="Foto de Rafael Barbosa"/><br><sub><b>Rafael Barbosa</b></sub></a></td>
      <td align="center"><a href="https://www.linkedin.com/in/vinicius-ibiapina/"><img style="border-radius: 10%;" src="./assets/imagens_integrantes/wildisley.jpg" width="100px;" alt="Foto de Wildisley Filho"/><br><sub><b>Wildisley Filho</b></sub></a></td>
    </tr>
  </table>
</div>

# Atividade:

## 🚦 Semáforo Inteligente

Imagine uma cidade onde os semáforos não apenas controlam o tráfego, mas também se comunicam entre si, ajustando o fluxo de veículos de forma inteligente e eficiente. Essa é a visão de uma Smart City, e é exatamente o que você e seu grupo irão explorar nesta atividade. Vocês serão os engenheiros responsáveis por criar um semáforo inteligente, capaz de detectar a presença de veículos através de um sensor de luz (LDR) e adaptar seu comportamento automaticamente para diferentes condições, como o "modo noturno".


## 📁 Estrutura de pastas

Dentre os arquivos e pastas presentes na raiz do projeto, definem-se:

- <b>assets</b>: aqui estão os arquivos relacionados a parte gráfica do projeto, ou seja, as imagens e vídeos que os representam (O logo do grupo pode ser adicionado nesta pasta).

- <b>src</b>: Todo o código fonte criado para o desenvolvimento do projeto, incluindo firmware, notebooks, backend e frontend, se aplicáveis.

- <b>README.md</b>: arquivo que serve como guia e explicação geral sobre a atividade (o mesmo que você está lendo agora).

- <b>funcionamento.mp4</b>: arquivo que mostra o funcionamento da atividade em vídeo.

## 📝 Documentação

### **1. Descrição do Projeto**

A atividade consiste no desenvolvimento de um **semáforo inteligente** como parte da visão de uma Smart City. O semáforo é capaz de detectar a presença de veículos por meio de um sensor de luminosidade (LDR) e adaptar-se automaticamente para diferentes condições com seus diferentes modos, como o **modo noturno**. Adicionalmente, o sistema possui integração com a nuvem (MQTT) para comunicação centralizada e visualização remota dos dados e estados.

---

### **2. Objetivos**

#### Parte 1: Montagem Física e Programação com LDR e Modo Noturno
- Criar dois semáforos controlados por um ESP32.
- Implementar o sensor de luminosidade (LDR) para detecção de veículos e adaptação automática ao modo noturno.

#### Parte 2: Configuração da Interface Online
- Desenvolver uma interface que permita ajustar o comportamento dos semáforos, visualizar os dados captados pelo LDR e ativar/desativar o modo noturno.

#### Extra: Conexão com Ubidots
- Implementar a conectividade de ambos os semáforos com o Ubidots, permitindo gerenciamento remoto por meio de dashboards.

---

### **3. Materiais Utilizados**

#### 3.1 Hardware:
- 2 x ESP32 (um para cada semáforo).
- 6 x LEDs (2 conjuntos de vermelho, amarelo e verde).
- 1 x Sensor LDR.
- 1 x Protoboard.
- Resistores com diversas resistências.
- Jumpers macho-macho de diversas cores.

#### 3.2 Software:
- **Arduino IDE** para programação do ESP32.
- **Bibliotecas:** WiFi, MQTT, e Ticker.
- **Plataforma Ubidots** para gerenciamento remoto.

---

### **4. Estrutura do Código**

O código foi estruturado para ser modular e organizado, facilitando manutenção e escalabilidade. Abaixo estão as principais seções:

#### 4.1. Configuração de Pinos e Conexão WiFi
Os pinos do ESP32 foram configurados para controlar os LEDs dos semáforos e o sensor LDR. A conexão WiFi utiliza credenciais definidas no código e suporta comunicação segura via MQTT com o HiveMQ.

```cpp
const char* ssid = "Zoin";          // Nome da rede WiFi
const char* password = "12345678";  // Senha da rede WiFi
const char* mqtt_server = "706f3a6885be461ea18a14eeca8916ee.s1.eu.hivemq.cloud"; // Endereço do broker MQTT
```

#### 4.2. Classe para Controle dos Semáforos
Foi criada uma classe para encapsular os métodos de controle dos estados do semáforo (verde, amarelo e vermelho). A modularidade permite reaproveitamento do código para múltiplos semáforos.

```cpp
class Semaforo {
  private:
    short int vermelho, amarelo, verde;
  public:
    Semaforo(short int pinoVerm, short int pinoVerde, short int pinoAmar);
    void abrir();          // Ativa o LED verde
    void esperar();        // Ativa o LED amarelo
    void fechar();         // Ativa o LED vermelho
    void desligarTodos();  // Desativa todos os LEDs
    void alternarAmarelo();// Alterna o estado do LED amarelo (modo noturno)
};
```

#### 4.3. Controle do Ciclo dos Semáforos
Os estados dos semáforos são controlados por meio de uma enumeração `EstadoSemaforo`, que define claramente os possíveis estados do sistema: `SEMAFORO1_VERDE`, `SEMAFORO1_AMARELO`, `SEMAFORO1_VERMELHO`, e assim por diante. Isso facilita a expansão e manutenção do código.

Os tempos de transição entre os estados do semáforo são controlados por meio da biblioteca `Ticker`, garantindo uma temporização não bloqueante. Além disso, o `Ticker` também é utilizado para gerenciar o pisca-pisca dos LEDs amarelos no modo noturno.

#### 4.4. Modo Noturno
O modo noturno pode ser ativado automaticamente com base no valor do sensor LDR (luminosidade menor ou igual a 100) ou manualmente via comando MQTT (`noturno`). Durante este modo, os LEDs amarelos piscam alternadamente para sinalizar tráfego reduzido.

```cpp
void iniciarModoNoturno() {
  modoNoturno = true;
  timerSemaforo.detach();
  semaforo1.desligarTodos();
  semaforo2.desligarTodos();
  timerPiscaNoturno1.attach(1, []() { semaforo1.alternarAmarelo(); });
  timerPiscaNoturno2.attach(1, []() { semaforo2.alternarAmarelo(); });
}
```

Da mesma forma, o modo normal é restaurado automaticamente quando a luminosidade aumenta ou manualmente com o comando MQTT (`normal`).

#### 4.5. Controle Manual dos Semáforos
Os modos `semaforo1` e `semaforo2` permitem forçar um dos semáforos a permanecer no estado "verde", enquanto o outro é mantido no estado "vermelho". Esses modos são ativados via mensagens MQTT nos seguintes formatos:
- **Mensagem:** `semaforo1` - Mantém o Semáforo 1 aberto.
- **Mensagem:** `semaforo2` - Mantém o Semáforo 2 aberto.

#### 4.6. Publicação e Assinatura de Tópicos MQTT
O sistema utiliza o HiveMQ para enviar e receber mensagens. Os valores do sensor LDR são publicados no tópico `hivemqdemo/commands`. Comandos para os semáforos também são enviados ao mesmo tópico.

```cpp
client.subscribe("hivemqdemo/commands");        // Tópico para comandos
client.publish("hivemqdemo/commands", ldrString.c_str()); // Publica valor do LDR
```

#### 4.7. Integração com o Sensor LDR
O sensor LDR monitora a presença de veículos e a iluminação ambiente. Valores do LDR influenciam a ativação do modo noturno ou ajustes no comportamento dos semáforos.

```cpp
int valorLDR = analogRead(PINO_LDR);
if (valorLDR <= 100) {
  iniciarModoNoturno();  // Baixa luminosidade: ativa modo noturno
} else {
  pararModoNoturno();    // Alta luminosidade: retorna ao modo normal
}
```

---

### **5. Funcionamento Previsto**

#### 5.1.Modo Normal:
- Os semáforos alternam automaticamente entre verde, amarelo e vermelho com tempos programados, ajustando o fluxo de acordo com a presença de veículos detectada pelo sensor LDR.
- Os dados captados são enviados ao HiveMQ para visualização remota.

#### 5.2. Modo Noturno:
- Os LEDs amarelos piscam alternadamente, indicando menor atividade no tráfego. Este modo é ativado automaticamente com base nos valores do LDR ou manualmente via MQTT.

#### 5.3. Modo Forçado Semáforo 1:
- Mantém o semáforo 1 aberto (verde), enquanto o semáforo 2 permanece fechado (vermelho). Este estado pode ser ativado manualmente pela interface MQTT.

#### 5.3. Modo Forçado Semáforo 2:
- Mantém o semáforo 2 aberto (verde) e o semáforo 1 fechado (vermelho), também ativado manualmente via MQTT.

---

### **6. Conexão com Ubidots**
Cada semáforo está conectado a um ESP32 que envia dados captados pelo sensor LDR para o Ubidots. A plataforma é configurada permitir ajustes nos estados dos semáforos e visualização remota.
