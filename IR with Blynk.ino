/*Projeto Lab LASCOU: Envio de sinal IR e Acionamento Online*/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
int pinValue;
#include <IRremoteESP8266.h>

char auth[] = "K5qD_hOOgwgsG_wkFKM47SzGTdBtSZh9"; //Meu Token do BLYNK
char ssid[] = ".....";
char pass[] = "wifidecasa";

IRsend irsend(12); //FUNÇÃO RESPONSÁVEL PELO MÉTODO DE ENVIO DO SINAL IR / UTILIZA O GPIO14(D5)

int tamanho = 60; //TAMANHO DA LINHA RAW(68 BLOCOS)
int frequencia = 32; //FREQUÊNCIA DO SINAL IR(32KHz)
unsigned int LD[60] = {2700,900,450,450,450,450,450,900,450,900,1350,900,450,450,450,450,450,450,450,450,450,450,450,450,450,450,900,900,900,900,900,900,450,450,900,900,900,900,450,450,900,450,450,450,450,900,450,450,450,450,450,450,900,450,450,900,450,450,450}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES

BLYNK_WRITE(V1)
{
pinValue = param.asInt();
     if (pinValue == 1){
      
        irsend.sendRaw(LD,tamanho,frequencia);  // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
        Serial.println("Comando enviado: Liga / Desliga"); //comando associado ao sinal
        delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
        
    }
}

void setup(){
  
  irsend.begin(); //INICIALIZA A FUNÇÃO
  Serial.begin(115200); //INICIALIZA A PORTA SERIAL
  Blynk.begin(auth, ssid, pass);
  
}

void loop(){
  Blynk.run();
}
