#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//WiFi
const char* SSID = "Leonardo";                // SSID / nome da rede WiFi que deseja se conectar
const char* PASSWORD = "12345678";   // Senha da rede WiFi que deseja se conectar
WiFiClient wifiClient;

//MQTT Server
const char* BROKER_MQTT = "test.mosquitto.org"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883;                      // Porta do Broker MQTT

#define ID_MQTT  "ppsadiohnk"            //Informe um ID unico e seu. Caso sejam usados IDs repetidos a ultima conexão irá sobrepor a anterior. 
#define TOPIC_PUBLISH "pp"    //Informe um Tópico único. Caso sejam usados tópicos em duplicidade, o último irá eliminar o anterior.
PubSubClient MQTT(wifiClient);        // Instancia o Cliente MQTT passando o objeto espClient

//Declaração das Funções
void mantemConexoes();  //Garante que as conexoes com WiFi e MQTT Broker se mantenham ativas
void conectaWiFi();     //Faz conexão com WiFi
void conectaMQTT();     //Faz conexão com Broker MQTT
void enviaPacote();     //


String json[] = {"off", "off", "1"};
//Sensor de luminosidade LDR
int lr1 = D2;
int lr2 = D1;
//potenciometro
int pot = D4;

void setup() {
  pinMode(lr1, INPUT);
  pinMode(lr2, INPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600);

  conectaWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  mantemConexoes();
  mantemConexoes();
}
int luz1, luz2, p, estado = 0;
unsigned int ton;
int estadoluz1 = 0, estadoluz2 = 0;
String res;
void loop() {
  p = analogRead(pot);
  p = map(p, 0, 4096, 1, 8);
  //  Serial.print("pot = ");
  //  Serial.println(p);

  json[2] = "" + p;
  luz1 = analogRead(lr1);
  if (luz1 > 960) {
    json[0] = "on";
    estadoluz1 = 1;
  } else if (estadoluz1 == 1) {
    json[0] = "off";
    estadoluz1 = 0;
  }
  luz2 = analogRead(lr2);
  if (luz2 > 900) {
    json[1] = "on";
    estadoluz2 = 1;
  } else if (estadoluz2 == 1) {
    json[1] = "off";
    estadoluz2 = 0;
  }

  makestr();

  //mqtt
  enviaValores();
  MQTT.loop();
}
void makestr() {
  res = "LDR1:" + json[0];
  res += ",LDR2" + json[1];
  res += ",mult:" + json[2];
  res += ".";
}
void mantemConexoes() {
  if (!MQTT.connected()) {
    conectaMQTT();
  }

  conectaWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}

void conectaWiFi() {

  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  Serial.print("Conectando-se na rede: ");
  Serial.print(SSID);
  Serial.println("  Aguarde!");

  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
  //WiFi.begin(SSID); // Conecta na rede WI-FI

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso, na rede: ");
  Serial.print(SSID);
  Serial.print("  IP obtido: ");
  Serial.println(WiFi.localIP());
}

void conectaMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Conectando ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao Broker com sucesso!");
    }
    else {
      Serial.println("Noo foi possivel se conectar ao broker.");
      Serial.println("Nova tentatica de conexao em 10s");
      delay(10000);
    }
  }
}

void enviaValores() {
  Serial.println("  ### Envia valores");
  MQTT.publish(TOPIC_PUBLISH, res.c_str());
  delay(1000);
}


