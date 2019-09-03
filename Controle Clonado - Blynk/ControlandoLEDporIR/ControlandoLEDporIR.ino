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
 
#include <IRremote.h>
 
int IR_Recv = 11;   //Pino OUT do Receptor Infravermelho (IR)
int ledVermelho = 10;
int ledAmarelo = 9;
int ledVerde = 8;
 
IRrecv irrecv(IR_Recv);
decode_results results;
 
void setup(){
  Serial.begin(9600); //iniciamos a comunicacao serial
  irrecv.enableIRIn(); //inicia o receptor infravermelho (IR)
  pinMode(ledVermelho, OUTPUT); // configuramos o pino digital como saída
  pinMode(ledAmarelo, OUTPUT); // configuramos o pino digital como saída
  pinMode(ledVerde, OUTPUT); // configuramos o pino digital como saída

}
 
void loop(){
  //decodificamos a entrada do receptor infravermelho
  if (irrecv.decode(&results)){
    long int decCode = results.value;
    Serial.println(results.value);
    
    //SWITCH CASE para usar o botão pressionado do controle remoto
    switch (results.value){
      case 551520375: //quando pressiono o botao 1 do meu controle remoto
        digitalWrite(ledVermelho, HIGH);
        break;   
      case 551495895: //quando pressiono o botao 4 do meu controle remoto
        digitalWrite(ledVermelho, LOW);   
        break;
       case 551504055: //quando pressiono o botao 2 do meu controle remoto
        digitalWrite(ledAmarelo, HIGH);
        break;           
       case 551528535: //quando pressiono o botao 5 do meu controle remoto
        digitalWrite(ledAmarelo, LOW);
        break;       
       case 551536695: //quando pressiono o botao 3 do meu controle remoto
        digitalWrite(ledVerde, HIGH);
        break;       
       case 551512215: //quando pressiono o botao 6 do meu controle remoto
        digitalWrite(ledVerde, LOW);
        break;
    }
    irrecv.resume(); // Recebe o próximo valor do botão que pressionamos
  }
  delay(10);
}
