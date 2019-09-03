/*
 * Modified by Rui Santos, http://randomnerdtutorialscom
 * based on IRremote Library - Ken Shirriff
 * 
 * Adaptado e Modificado por Rodrigo Costa
 * Blog: https://eletronicaparatodos.com
 *       http://eletronicaparatodos.net
 *       
 * Rev.01: 28/03/2017
 * Rev.02: 30/03/2017
 * 
*/
 
#define  BLYNK_PRINT Serial
#include  <ESP8266WiFi.h>
#include  <BlynkSimpleEsp8266.h>
#include <IRac.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

 
int IR_Recv = 14;   //Pino OUT do Receptor Infravermelho (IR)
int ledVermelho = 4;
int num;
 
IRrecv irrecv(IR_Recv);
decode_results results;


 void setValor(int n)
{
  switch(num){
  case 17:
        digitalWrite(ledVermelho, HIGH);
  }
}


void setup(){
  Serial.begin(115200); //iniciamos a comunicacao serial
  irrecv.enableIRIn(); //inicia o receptor infravermelho (IR)
  pinMode(ledVermelho, OUTPUT); // configuramos o pino digital como saída
}
 
void loop(){
  //decodificamos a entrada do receptor infravermelho
  if (irrecv.decode(&results)){
    
    switch (results.value){
      case 11697120: //quando pressiono o botao 1 do meu controle remoto
      if(num==0)
      {
        num=20;
         lcd.setCursor(0, 0);
  lcd.print("TEMPERATURA DEFAULT", num);
      }
                   num=num+1;
                   setValor(num);
 lcd.setCursor(0, 0);
  lcd.print("TEMPERATURA %d", num);
        break;   
    }
    irrecv.resume(); // Recebe o próximo valor do botão que pressionamos
  }
  delay(10);
}
