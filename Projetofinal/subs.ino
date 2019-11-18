#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//WiFi
const char* SSID = "LUIZANTONIO_2GHz";                // SSID / nome da rede WiFi que deseja se conectar
const char* PASSWORD = "andrea1130";   // Senha da rede WiFi que deseja se conectar
WiFiClient wifiClient;

//MQTT Server
const char* BROKER_MQTT = "test.mosquitto.org"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883;                      // Porta do Broker MQTT

//Som
int s1 = D5;
int s2 = D6;

#define ID_MQTT  "padiohnk4654121564"            //Informe um ID unico e seu. Caso sejam usados IDs repetidos a ultima conexão irá sobrepor a anterior. 
#define TOPIC_PUBLISH "pp"    //Informe um Tópico único. Caso sejam usados tópicos em duplicidade, o último irá eliminar o anterior.
PubSubClient MQTT(wifiClient);        // Instancia o Cliente MQTT passando o objeto espClient

//Declaração das Funções
void mantemConexoes();  //Garante que as conexoes com WiFi e MQTT Broker se mantenham ativas
void conectaWiFi();     //Faz conexão com WiFi
void conectaMQTT();     //Faz conexão com Broker MQTT
void enviaPacote();     //


String json[] = {"casa","12"};

void setup() {
  Serial.begin(9600);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  
  conectaWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callback);
  mantemConexoes();
  mantemConexoes();
  MQTT.subscribe("pp");
  json[0]="cas";
}

void loop() {
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
      Serial.println("Não foi possivel se conectar ao broker.");
      Serial.println("Nova tentatica de conexao em 10s");
      delay(10000);
    }
  }
}



void callback(char* topic, byte*message, unsigned int length) {
  
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  Serial.println(messageTemp);
  Serial.println();
  String a = messageTemp.substring(messageTemp.indexOf(":")+1);
  String ldr1 = a.substring(0,a.indexOf(","));
  Serial.println(a);
  Serial.print("LDR1: ");
  Serial.println(ldr1);
  a = a.substring(a.indexOf(":")+1);
  String f1 = a.substring(0,a.indexOf(","));
  a = a.substring(a.indexOf(":")+1);
  String ldr2 = a.substring(0,a.indexOf(","));
  Serial.print("LDR2: ");
  Serial.println(ldr2);
  a = a.substring(a.indexOf(":")+1);
  String f2 = a.substring(0,a.indexOf(","));
  int ff1 = f1.toInt();
  int ff2 = f2.toInt();
  exc(ldr1,ldr2,ff1,ff2);
}
String makestr(String t){
  String ret;
  ret = "LDR1:"+ t[0];
  ret+= ",LDR2:"+t[1];
  Serial.println(ret);
  return ret;
}
void exc(String l1,String l2,int f1,int f2){
    if(l1=="on"){
      Serial.println("on1");
      tone(s1,f1,1000);
      }
     if(l2=="on"){
      Serial.println("on2");
      tone(s2,f2,1000);
      }
  
}



