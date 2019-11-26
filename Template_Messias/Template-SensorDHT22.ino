#include <ESP8266WiFi.h>
#include <AddrList.h>

// LwIPv2
#include <lwip/dns.h>
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/ip4_addr.h"
#include "lwip/ip6_addr.h"

#define LWIP_IPV4 0 
#define LWIP_IPV6 1 
#define LWIP_DHCP 0 
#define LWIP_DHCP6 1 

// WIFI
#define STASSID "DiSNeL"
#define STAPSK  "PPgCC-UFPI"

WiFiClient nodemcuClient;
int32_t RSSI;

// --- MQTT ---
#include <PubSubClient.h>
//const char* MQTT_BROKER = "fd9e:6c51:2336::1";
const char* MQTT_BROKER = "fd9e:6c51:2336:0:717b:e02b:9c00:d43a";
const char* MQTT_ClientID = "esp-dht22-node03";
const char* MQTT_USERNAME = "mqtt_user";
const char* MQTT_PASSWORD = "mqtt_ufpi";
PubSubClient client(nodemcuClient);
const char* topicoTemperatura = "ufpi/ppgcc/esp-dht22-node01/temperatura";
const char* topicoUmidade = "ufpi/ppgcc/esp-dht22-node01/umidade";

// --- DHT ---
#include <DHT.h>
#define DHTPIN D5
//#define DHTPIN D1
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float umidade;
float temperatura;

void status(Print& out) {
  out.println(F("--------------------------------------------------------------"));
  
  for (auto a : addrList) {
    out.printf("IF='%s' IPv6=%d local=%d hostname='%s' addr= %s",
               a.ifname().c_str(),
               a.isV6(),
               a.isLocal(),
               a.ifhostname(),
               a.toString().c_str());
    out.println();           
    delay(1000);

  }
  for (int i = 0; i < DNS_MAX_SERVERS; i++) {
      IPAddress dns = WiFi.dnsIP(i);
      if (dns.isSet()) {
        out.printf("dns%d: %s\n", i, dns.toString().c_str());
      }
    }

  out.println(F("--------------------------------------------------------------"));

}

void setup() {
  
  WiFi.hostname("esp-dht22-node03");

  Serial.begin(115200);
  Serial.println();
  Serial.println(ESP.getFullVersion());
  dht.begin();
  conectarWifi();
  client.setServer(MQTT_BROKER, 1883);

  
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }

  for (bool configured = true; !configured;) {
    for (auto addr : addrList)
      if ((configured = !addr.isLocal()
                        && addr.isV6() //
                        && addr.ifnumber() == STATION_IF
          )) {
        break;
      }
    Serial.print('.');
    delay(500);
  }


    status(Serial);

}

void loop() {

     medirTemperaturaUmidade();
     mostrarTemperaturaUmidade();
     if (!client.connected()) {
        reconectarMQTT();
     }
     publicarTemperaturaUmidadeNoTopico();

     RSSI = WiFi.RSSI();
     Serial.printf("RSSI: %i\n", RSSI);
     delay(4000);
     
}

// CONEXAO WIFI
void conectarWifi() {
  delay(10);

 WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}
void reconectarMQTT() {
  while (!client.connected()) {
    // client.connect(MQTT_ClientID);
    client.connect(MQTT_ClientID,MQTT_USERNAME,MQTT_PASSWORD);
  }
}

// MEDICAO TEMPERATURA E UMIDADE
void medirTemperaturaUmidade() {
  umidade = dht.readHumidity();
  temperatura = dht.readTemperature(false);
  delay(5000);
}

// PUBLICACAO VALORES TEMPERATURA E UMIDADE NO BROKER
void publicarTemperaturaUmidadeNoTopico() {
  client.publish(topicoTemperatura, String(temperatura).c_str(), true);
  client.publish(topicoUmidade, String(umidade).c_str(), true);
}

// EXIBIR TEMPERATURA E UMIDADE NA SERIAL
void mostrarTemperaturaUmidade() {
  umidade = dht.readHumidity();
  temperatura = dht.readTemperature(false);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("°C");
  Serial.print("  ");
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print(" %");
  Serial.println("  ");
  delay(1000);
}
