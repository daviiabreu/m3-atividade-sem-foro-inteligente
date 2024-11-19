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
- Plataforma Ubidots para visualização de dados.

---

### **4. Estrutura do Código**

O código está dividido em partes principais para maior clareza e organização.

#### 4.1 Configuração de Pinos e Conexão WiFi

Os pinos do ESP32 foram configurados para controlar os LEDs e o sensor LDR. A conexão WiFi foi configurada com credenciais fornecidas, e a biblioteca MQTT foi usada para integração com o HiveMQ.

```c++
// Configurações da rede WiFi
const char* ssid = "Marco_Ruas";
const char* password = "12345678";
```

#### 4.2 Controle do Semáforo

Cada semáforo é gerenciado por uma classe que controla os estados (vermelho, amarelo, verde). Essa abordagem modular facilita a reutilização do código.

```c++
class Semaforo {
  private:
    short int vermelho, amarelo, verde;
  public:
    Semaforo(short int pinoVerm, short int pinoVerde, short int pinoAmar);
    void abrir();
    void esperar();
    void fechar();
    void desligarTodos();
    void alternarAmarelo();
};
```

#### 4.3 Modo Noturno

O modo noturno é ativado automaticamente com base nos valores do sensor LDR ou manualmente via MQTT.

```c++
void iniciarModoNoturno() {
  modoNoturno = true;
  timerSemaforo.detach();
  semaforo1.desligarTodos();
  semaforo2.desligarTodos();
  timerPiscaNoturno1.attach(1, []() { semaforo1.alternarAmarelo(); });
  timerPiscaNoturno2.attach(1, []() { semaforo2.alternarAmarelo(); });
}
```

#### 4.4 Conectividade MQTT

O sistema utiliza o HiveMQ para envio e recebimento de mensagens, permitindo controle remoto e integração com a interface.

```c++
client.subscribe("hivemqdemo/commands"); // Tópico para comandos
client.publish("hivemqdemo/ldr", ldrString.c_str()); // Dados do LDR
```

---

### **5. Conexão com Ubidots**

- Cada semáforo está conectado a um ESP32 que envia dados captados pelo sensor LDR para o Ubidots.
- A plataforma é configurada para exibir dashboards em tempo real, permitindo ajustes nos estados dos semáforos e visualização remota.

---

### **6. Resultados Esperados**

#### Modo Normal:
- O semáforo alterna entre estados verde, amarelo e vermelho com base em tempos programados.
- A detecção de veículos pelo LDR é exibida no Ubidots e pode influenciar os tempos do semáforo.

#### Modo Noturno:
- Os LEDs amarelos piscam alternadamente, indicando menor atividade no tráfego.

#### Interface Online:
- O dashboard permite alternar manualmente entre os modos (normal/noturno) e forçar a abertura de um semáforo específico.