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

### **2. Objetivos do Projeto**

1. **Parte 1: Montagem Física e Programação com LDR e Modo Noturno**
   - Criar dois semáforos controlados por um ESP32.
   - Implementar o sensor de luminosidade (LDR) para detecção de veículos e adaptação automática ao modo noturno.

2. **Parte 2: Configuração da Interface Online**
   - Desenvolver uma interface que permita ajustar o comportamento dos semáforos, visualizar os dados captados pelo LDR e ativar/desativar o modo noturno.

3. **Extra: Conexão com Ubidots**
   - Implementar a conectividade de ambos os semáforos com o Ubidots, permitindo gerenciamento remoto por meio de dashboards.

---

### **3. Materiais Utilizados**

#### Hardware:
- 2 x ESP32 (um para cada semáforo).
- 6 x LEDs (2 conjuntos de vermelho, amarelo e verde).
- 1 x Sensores LDR.
- 1 x Protoboard.
- Resistores com diversas resistências.
- Jumpers macho-macho de diversas cores.

#### Software:
- Arduino IDE para programação do ESP32.
- Biblioteca WiFi e MQTT para conectividade.
- Plataforma Ubidots 

---

### 4. Estrutura do Código

O código foi estruturado para ser modular e organizado, facilitando manutenção e escalabilidade. As principais seções incluem:

#### 4.1 Configuração de Pinos e Conexão WiFi
Os pinos do ESP32 foram configurados para controlar os LEDs dos semáforos e o sensor LDR. A conexão WiFi utiliza credenciais definidas no código e suporta comunicação segura via MQTT com o HiveMQ.

```cpp
const char* ssid = "Marco_Ruas";          // Nome da rede WiFi
const char* password = "12345678";        // Senha da rede WiFi
const char* mqtt_server = "hivemq.cloud"; // Endereço do broker MQTT
```

#### 4.2 Classe para Controle dos Semáforos
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

#### 4.3 Modo Noturno
O modo noturno é ativado automaticamente com base na leitura do LDR ou manualmente via mensagens MQTT. Durante este modo, os LEDs amarelos piscam alternadamente para sinalizar tráfego reduzido.

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

#### 4.4 Controle do Ciclo dos Semáforos
O ciclo dos semáforos (verde, amarelo, vermelho) é gerenciado por uma máquina de estados. Cada estado possui uma duração configurável e transições controladas por um `Ticker`.

```cpp
void gerenciarEstadoSemaforo() {
  switch (estadoAtual) {
    case SEMAFORO1_VERDE:
      semaforo1.abrir();
      semaforo2.fechar();
      estadoAtual = SEMAFORO1_AMARELO;
      timerSemaforo.once(3, gerenciarEstadoSemaforo);
      break;
    case SEMAFORO1_AMARELO:
      semaforo1.esperar();
      estadoAtual = SEMAFORO1_VERMELHO;
      timerSemaforo.once(1, gerenciarEstadoSemaforo);
      break;
    // Outros estados...
  }
}
```

#### 4.5 Conectividade MQTT
A integração com o HiveMQ permite controle remoto e transmissão de dados do sensor LDR. Mensagens MQTT podem ativar/desativar modos ou alterar estados manualmente.

```cpp
client.subscribe("hivemqdemo/commands");        // Tópico para comandos
client.publish("hivemqdemo/ldr", ldrString.c_str()); // Publica valor do LDR
```

#### 4.6 Integração com o Sensor LDR
O sensor LDR monitora a presença de veículos e a iluminação ambiente. Valores do LDR influenciam a ativação do modo noturno ou ajustes no comportamento dos semáforos.

```cpp
int valorLDR = analogRead(PINO_LDR);
if (valorLDR <= 2000) {
  iniciarModoNoturno();  // Baixa luminosidade: ativa modo noturno
} else {
  pararModoNoturno();    // Alta luminosidade: retorna ao modo normal
}
```
---

### **5. Conexão com Ubidots**

- Cada semáforo está conectado a um ESP32 que envia dados captados pelo sensor LDR para o Ubidots.
- A plataforma é configurada para exibir dashboards em tempo real, permitindo ajustes nos estados dos semáforos e visualização remota.

---

### 6. Funcionamento Previsto

**Modo Normal**:  
Os semáforos alternam automaticamente entre verde, amarelo e vermelho com tempos programados, ajustando o fluxo de acordo com a presença de veículos detectada pelo sensor LDR. Os dados captados são enviados ao Ubidots para visualização remota.

**Modo Noturno**:  
Os LEDs amarelos piscam alternadamente, indicando menor atividade no tráfego. Este modo é ativado automaticamente com base nos valores do LDR ou manualmente via MQTT.

**Modo Forçado Semáforo 1**:  
Permite manter o semáforo 1 (verde) aberto forçadamente enquanto o semáforo 2 permanece fechado (vermelho). Este estado pode ser ativado manualmente pela interface MQTT.

**Modo Forçado Semáforo 2**:  
Mantém o semáforo 2 (verde) aberto e o semáforo 1 fechado (vermelho), também ativado manualmente via MQTT.

---

### Conclusão

O projeto explora a inovação no gerenciamento de tráfego urbano, proporcionando quatro modos operacionais para diferentes cenários: fluxo automático, tráfego reduzido e controle manual. Essa abordagem integrada de sensores, conectividade MQTT e visualização em tempo real via Ubidots demonstra o potencial de soluções inteligentes para cidades modernas, otimizando eficiência e segurança no trânsito.