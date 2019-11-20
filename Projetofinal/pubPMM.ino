#include <WiFi.h>
#include <PubSubClient.h>
//pinos sensores
int lr1 = 27;
int lr2 = 26;
int pot = 25;
int a[100][4];
int aux = 0;

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

void setup() {


  pinMode(lr1, INPUT);
  pinMode(lr2, INPUT);
  pinMode(pot, INPUT);
  conectaWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  Serial.begin(9600);

}
int luz1, luz2, p;

void loop() {
  
 mantemConexoes();
 enviaValores();
 MQTT.loop();
   
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
String conversor() {
  String  v1, v2, v3;
  p = analogRead(pot);
  p = map(p, 100, 4070, 0, 8);
  luz1 = analogRead(lr1);
  luz2 = analogRead(lr2);
  Serial.print(luz1);
  Serial.print(" ");
  Serial.print(luz2);
  Serial.print(" ");
  if (luz1 > 40)
  {
    v1 = "on";
    v2 = "off";
  }
  if (luz2 > 40) {
    v1 = "off";
    v2 = "on";
  }

  if (luz2 > 40 && luz1 > 40) {
    v1 = "on";
    v2 = "on";
  }
  if (luz2 < 40 && luz1 < 40) {
    v1 = "off";
    v2 = "off";
  }

  v3 = String(p);
  String json[] = {"ldr1:", v1, ",ldr2:", v2, ",f:", v3, "."};

  String msg;
  for (int i = 0; i < 7; i++) {
    msg += json[i];
  }
  return msg;
}
 
void enviaValores() {
String msg=conversor();
  //const char* dados = msg.c_str();
  Serial.println(msg);
 
 
  delay(300);
//MQTT.publish(TOPIC_PUBLISH, dados);
delay(300);
 
}
