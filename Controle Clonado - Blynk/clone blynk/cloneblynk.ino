/* Projeto Lab LITTORAL: Envio de um sinal IR e Acionamento Online */

#define  BLYNK_PRINT Serial
#include  <ESP8266WiFi.h>
#include  <BlynkSimpleEsp8266.h>
#include <IRac.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

char auth [] = " K5qD_hOOgwgsG_wkFKM47SzGTdBtSZh9 " ; // Meu Token do BLYNK
char ssid [] = "weslley";
char pass [] = "weslley12" ;

const uint16_t IrLed = 4;
IRsend irsend(IrLed);


uint16_t powerOffRawData[199] = {4338, 4366,  512, 1658,  510, 576,  512, 1658,  510, 1660,  510, 576,  512, 576,  512, 1680,  488, 578,  512, 574,  512, 1682,  486, 576,  514, 576,  512, 1656,  514, 1658,  512, 576,  514, 1658,  510, 574,  512, 576,  512, 578,  510, 1658,  512, 1656,  512, 1680,  488, 1658,  512, 1660,  512, 1654,  512, 1682,  488, 1656,  512, 574,  512, 576,  512, 576,  512, 576,  512, 578,  512, 574,  514, 1680,  488, 574,  514, 576,  512, 1658,  510, 576,  512, 576,  514, 576,  514, 1654,  512, 576,  512, 1658,  512, 1656,  512, 576,  512, 1656,  512, 1654,  514, 1658,  536, 5186,  4366, 4344,  514, 1658,  512, 574,  514, 1658,  510, 1680,  488, 574,  514, 576,  512, 1658,  510, 578,  514, 574,  512, 1682,  488, 576,  514, 576,  512, 1656,  512, 1656,  512, 576,  512, 1660,  512, 574,  512, 574,  512, 576,  512, 1658,  510, 1656,  514, 1656,  512, 1658,  512, 1658,  512, 1654,  514, 1680,  488, 1656,  512, 576,  512, 576,  512, 576,  512, 576,  514, 578,  512, 574,  512, 1658,  510, 576,  512, 576,  514, 1656,  512, 576,  512, 580,  508, 578,  514, 1654,  512, 576,  514, 1658,  510, 1658,  512, 576,  512, 1656,  512, 1656,  514, 1660,  512};  // COOLIX B27BE0
uint16_t powerOnRawData[199] = {4366, 4352,  514, 1656,  512, 576,  512, 1682,  488, 1682,  488, 576,  512, 576,  514, 1658,  510, 578,  512, 574,  512, 1658,  510, 576,  512, 576,  512, 1658,  510, 1658,  512, 576,  512, 1682,  488, 572,  514, 576,  512, 576,  514, 1682,  488, 1658,  512, 1680,  488, 1658,  512, 1658,  516, 1650,  512, 1658,  510, 1656,  512, 576,  512, 576,  510, 578,  512, 576,  514, 578,  534, 550,  514, 1660,  508, 576,  512, 1658,  510, 1682,  488, 576,  512, 576,  512, 578,  538, 1630,  512, 576,  512, 1658,  510, 576,  512, 576,  512, 1660,  510, 1658,  510, 1680,  514, 5184,  4368, 4346,  512, 1660,  510, 576,  512, 1658,  512, 1680,  488, 576,  512, 576,  512, 1658,  512, 578,  536, 550,  512, 1656,  514, 576,  514, 576,  512, 1680,  488, 1680,  490, 576,  514, 1660,  534, 550,  512, 576,  512, 576,  512, 1682,  488, 1682,  488, 1680,  488, 1680,  488, 1662,  536, 1654,  488, 1680,  488, 1682,  488, 576,  512, 576,  512, 576,  512, 576,  512, 578,  512, 574,  512, 1658,  510, 578,  512, 1658,  510, 1680,  488, 576,  512, 576,  512, 578,  536, 1654,  488, 576,  512, 1680,  488, 576,  512, 576,  514, 1680,  488, 1680,  488, 1682,  488};  // COOLIX B27BE0

WidgetLCD lcd(V0);

BLYNK_WRITE (V1)
{
int buttonState1 = param.asInt();
     if (buttonState1 == 1 ) {
  lcd.print(0,0,"LIGANDO...");
  irsend.sendRaw(powerOffRawData, 199, 38);
  delay(5000);        
    }
}

BLYNK_WRITE (V2)
{
  
int buttonState2 = param.asInt();
     if (buttonState2 == 1 ) {
  lcd.print(0,0,"DESLIGA...");
  irsend.sendRaw(powerOnRawData, 199, 38);
  delay(5000);        
    }
    
}

void  setup () {
  
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  Blynk.begin (auth, ssid, pass);
  
}

void  loop () {
  Blynk.run ();
}