/*
 * Modified by Rui Santos, http://randomnerdtutorialscom
 * based on IRremote Library - Ken Shirriff
 * 
 * Adaptado e Modificado por Weslley Aquino
 * Github: https://github.com/sirwez
 * Twitter: https://twitter.com/sirwezy
 *       
 * Rev.01: 02/09/2019
 * 
*/

/*
 * Caso use o app Blynk;
 * 
 * #define  BLYNK_PRINT Serial
 * #include  <ESP8266WiFi.h>
 * #include  <BlynkSimpleEsp8266.h>
 * 
 */
#include <IRac.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
/*
 * char auth [] = " K5qD_hOOgwgsG_wkFKM47SzGTdBtSZh9 "; // My token
 * char ssid [] = "weslley"; ID wifi
 * char pass [] = "weslley12"; key wifi
 * 
 */
LiquidCrystal_I2C lcd(0x27, 16, 2);

int IR_Recv = 14;   //Receptor Infravermelho (IR)
int ledVermelho = 12; //Vou retirar depois, só para testes iniciais
const uint16_t IrLed = 4; //Emissor Infravermelho (IR)

IRsend irsend(IrLed);
IRrecv irrecv(IR_Recv);
decode_results results;
char palavra[16] = "Temperatura:";
int temperatura;
uint16_t powerOffRawData[199] = {};  // COOLIX B27BE0
uint16_t powerOnRawData[199] = {};  // COOLIX B27BE0


void setValor(int num){
 
  switch(num){

case 17:
  irsend.sendRaw(powerOffRawData, 199, 38);
  delay(5000);
  temperatura = num;
  lcd.clear();
    for(int i = 0; i < 12; i++ ){
    
    lcd.setCursor(i, 0);
    lcd.print(palavra[i]);
    
  }
    lcd.print(temperatura);
    lcd.print("º");
  break;
    }
    
}
void setup(){
  
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  irrecv.enableIRIn(); //inicia o receptor infravermelho (IR)
  irsend.begin();
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
//Blynk.begin (auth, ssid, pass);
  pinMode(ledVermelho, OUTPUT); // configuramos o pino digital como saída
  
}
 
void loop(){
//decodificamos a entrada do receptor infravermelho
    if (irrecv.decode(&results)){
 
//SWITCH CASE para usar o botão pressionado do controle remoto
    switch (results.value){

//melhor deixar assim, ou criar uma variavel para ele?
      case 551520375: //quando pressiono o botao 1 do meu controle remoto
        num=17;
        setValor(num);
        digitalWrite(ledVermelho, HIGH);
        break;
        
    }
    irrecv.resume(); // Recebe o próximo valor do botão que pressionamos
  }
  delay(10);
}
