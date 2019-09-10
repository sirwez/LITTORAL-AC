 #include <IRac.h>
  #include <IRrecv.h>
  #include <IRremoteESP8266.h>
  #include <IRsend.h>
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  #include <ESP8266WiFi.h> //lib para conectar o wifi do ESP201
  #include <ESP8266WiFiMulti.h>//lib para as funções addAP e  run
  #include <SPI.h>  //protocolo síncrono de dados serial
  LiquidCrystal_I2C lcd(0x27, 16, 2);


 // =============================================================================================================
// --- Declaração de Objetos ---
  IRsend irsend(IrLed);
  IRrecv irrecv(IR_Recv);
  decode_results results;
  ESP8266WiFiMulti WiFiMulti; //cria uma instância da classe ESP8266WiFiMulti
  IPAddress local_IP(192, 168, 10, 110); //Cria uma instância da classe IPAddress e define o ip do servidor
// =============================================================================================================


// =============================================================================================================
// --- Declaração de Constantes ---
  int IR_Recv = 14;   //Receptor Infravermelho (IR)
  int temp_atual = 22;

   const uint16_t IrLed = 12; //Emissor Infravermelho (IR)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  //Valores Hexadecimais
  //Raw responsavel por cada sinal enviado do emissor IR ao A/C
  uint16_t powerOffRawData[199] = {4370, 4374,  512, 1662,  512, 576,  514, 1684,  488, 1660,  514, 576,  514, 576,  514, 1684,  488, 580,  538, 548,  514, 1660,  512, 576,  514, 576,  514, 1660,  514, 1658,  514, 576,  514, 1660,  540, 548,  514, 1662,  512, 1684,  488, 1660,  512, 1658,  514, 576,  514, 1658,  514, 1662,  536, 1634,  510, 576,  514, 576,  514, 576,  514, 576,  514, 1684,  490, 576,  514, 578,  538, 1634,  512, 1660,  512, 1662,  510, 576,  514, 576,  514, 576,  514, 576,  514, 578,  540, 548,  514, 576,  514, 574,  514, 1658,  514, 1658,  516, 1658,  514, 1660,  512, 1658,  540, 5194,  4372, 4352,  514, 1660,  512, 576,  514, 1660,  514, 1660,  510, 576,  514, 576,  514, 1660,  512, 578,  538, 550,  514, 1660,  512, 576,  514, 576,  514, 1660,  512, 1684,  490, 574,  514, 1660,  538, 550,  514, 1660,  512, 1660,  512, 1658,  514, 1684,  488, 574,  514, 1660,  512, 1660,  538, 1632,  512, 576,  514, 576,  514, 576,  514, 576,  514, 1660,  512, 576,  514, 578,  538, 1656,  488, 1660,  512, 1684,  488, 576,  514, 576,  514, 576,  514, 578,  512, 578,  538, 550,  514, 576,  514, 576,  514, 1660,  512, 1684,  488, 1660,  512, 1660,  512, 1662,  536};  // COOLIX B27BE0
  uint16_t powerOnRawData[199] =  {4372, 4350,  514, 1660,  512, 576,  514, 1658,  514, 1658,  514, 576,  514, 576,  514, 1658,  514, 578,  518, 570,  512, 1684,  490, 574,  514, 576,  514, 1658,  512, 1684,  490, 576,  514, 1660,  538, 550,  514, 576,  514, 576,  514, 1660,  512, 1660,  512, 1682,  490, 1682,  488, 1662,  538, 1632,  512, 1662,  510, 1684,  490, 576,  514, 576,  514, 576,  514, 576,  514, 578,  538, 550,  512, 1662,  512, 1684,  488, 1662,  510, 1660,  512, 576,  514, 576,  514, 576,  538, 1632,  514, 576,  514, 576,  514, 576,  514, 576,  514, 1660,  512, 1662,  510, 1658,  540, 5190,  4374, 4352,  514, 1658,  512, 576,  514, 1658,  514, 1660,  514, 574,  514, 576,  514, 1684,  488, 578,  530, 558,  514, 1658,  512, 576,  514, 576,  516, 1658,  514, 1660,  512, 576,  514, 1662,  536, 550,  514, 576,  514, 576,  514, 1684,  488, 1658,  514, 1660,  514, 1656,  514, 1662,  536, 1634,  512, 1660,  512, 1658,  512, 576,  514, 574,  514, 576,  514, 574,  514, 578,  538, 550,  514, 1660,  510, 1684,  490, 1658,  514, 1660,  514, 576,  514, 576,  514, 578,  516, 1680,  490, 576,  512, 578,  514, 576,  514, 576,  514, 1660,  512, 1682,  490, 1660,  540};  // COOLIX B21F78
  uint16_t set17RawData[199] =    {4372, 4360,  514, 1656,  514, 576,  514, 1682,  490, 1660,  512, 576,  514, 576,  514, 1660,  512, 578,  538, 548,  514, 1662,  510, 576,  514, 576,  514, 1682,  490, 1682,  490, 576,  514, 1662,  536, 550,  514, 574,  514, 576,  514, 1682,  490, 1660,  514, 1660,  512, 1682,  490, 1684,  514, 1630,  516, 1658,  514, 1682,  490, 576,  514, 576,  514, 576,  514, 574,  514, 578,  538, 550,  514, 576,  514, 576,  514, 576,  514, 1684,  488, 576,  514, 576,  514, 578,  538, 1630,  516, 1658,  514, 1658,  514, 1658,  514, 574,  514, 1658,  514, 1682,  490, 1658,  538, 5192,  4372, 4350,  516, 1680,  490, 576,  514, 1660,  514, 1658,  512, 576,  514, 574,  514, 1660,  512, 578,  540, 548,  514, 1660,  512, 576,  514, 576,  516, 1656,  514, 1684,  488, 576,  514, 1684,  514, 550,  514, 576,  514, 576,  516, 1656,  514, 1682,  490, 1658,  514, 1684,  488, 1662,  538, 1632,  514, 1658,  514, 1682,  490, 576,  512, 576,  514, 576,  514, 576,  514, 578,  540, 548,  514, 576,  514, 576,  514, 576,  516, 1660,  510, 576,  514, 576,  514, 578,  538, 1656,  490, 1658,  514, 1682,  488, 1684,  490, 574,  514, 1684,  490, 1658,  514, 1660,  538};  // COOLIX B21F08
  uint16_t set18RawData[199] =    {4370, 4356,  514, 1658,  512, 576,  514, 1656,  514, 1658,  512, 576,  514, 576,  512, 1658,  514, 578,  538, 548,  514, 1658,  512, 576,  514, 576,  512, 1660,  512, 1656,  514, 576,  512, 1660,  538, 550,  512, 578,  512, 576,  514, 1660,  512, 1656,  514, 1660,  510, 1660,  512, 1662,  536, 1632,  512, 1660,  512, 1660,  510, 576,  512, 576,  514, 576,  514, 576,  512, 580,  538, 548,  514, 574,  514, 576,  512, 1658,  514, 1656,  514, 576,  514, 574,  514, 578,  536, 1634,  512, 1660,  512, 1656,  514, 576,  514, 576,  514, 1660,  512, 1658,  514, 1656,  540, 5190,  4368, 4350,  512, 1658,  512, 576,  514, 1656,  512, 1658,  514, 576,  514, 576,  514, 1658,  512, 578,  538, 548,  514, 1660,  510, 576,  512, 576,  514, 1658,  512, 1658,  514, 574,  514, 1662,  536, 548,  514, 576,  512, 576,  514, 1656,  514, 1660,  510, 1658,  514, 1658,  512, 1660,  538, 1632,  514, 1660,  512, 1658,  512, 576,  514, 576,  514, 576,  514, 574,  514, 578,  536, 550,  514, 576,  514, 576,  514, 1658,  514, 1660,  512, 576,  512, 576,  512, 578,  538, 1632,  514, 1660,  512, 1658,  512, 576,  514, 576,  514, 1660,  512, 1684,  488, 1660,  536};  // COOLIX B21F18
  uint16_t set19RawData[199] =    {4370, 4358,  512, 1658,  514, 576,  514, 1658,  512, 1660,  512, 574,  514, 576,  514, 1658,  512, 578,  520, 566,  514, 1656,  514, 576,  514, 576,  514, 1658,  512, 1658,  514, 576,  512, 1660,  516, 570,  514, 576,  512, 576,  514, 1656,  514, 1660,  512, 1658,  512, 1656,  514, 1660,  538, 1632,  514, 1658,  514, 1658,  512, 576,  514, 576,  512, 576,  514, 576,  514, 578,  538, 550,  512, 578,  512, 1658,  512, 1658,  514, 1658,  514, 576,  514, 576,  514, 578,  538, 1632,  512, 1658,  512, 576,  514, 576,  514, 574,  514, 1660,  512, 1658,  512, 1658,  538, 5192,  4368, 4350,  514, 1658,  514, 574,  514, 1660,  512, 1660,  512, 574,  514, 576,  512, 1658,  514, 578,  518, 570,  514, 1658,  512, 576,  514, 576,  514, 1656,  514, 1658,  512, 576,  514, 1660,  512, 574,  514, 576,  514, 576,  514, 1656,  514, 1658,  512, 1658,  512, 1658,  514, 1660,  514, 1654,  514, 1658,  512, 1660,  510, 576,  514, 576,  512, 578,  512, 576,  514, 578,  538, 550,  512, 576,  514, 1656,  514, 1658,  512, 1660,  512, 574,  514, 576,  512, 578,  538, 1630,  514, 1660,  512, 576,  514, 576,  514, 576,  512, 1658,  514, 1656,  514, 1662,  510};  // COOLIX B21F38
  uint16_t set20RawData[199] =    {4396, 4344,  512, 1658,  512, 576,  514, 1658,  512, 1656,  514, 576,  514, 574,  514, 1658,  512, 578,  538, 550,  512, 1660,  510, 576,  514, 576,  512, 1658,  512, 1658,  512, 574,  514, 1660,  536, 552,  514, 576,  514, 576,  514, 1658,  512, 1658,  512, 1658,  512, 1658,  512, 1662,  516, 1652,  512, 1658,  512, 1660,  512, 576,  512, 576,  514, 576,  514, 574,  514, 576,  518, 568,  514, 576,  514, 1656,  516, 574,  514, 1658,  514, 574,  516, 574,  514, 576,  514, 1656,  512, 1658,  514, 574,  516, 1658,  510, 576,  514, 1656,  516, 1658,  512, 1656,  538, 5192,  4366, 4348,  514, 1658,  512, 574,  516, 1656,  514, 1660,  512, 574,  514, 576,  514, 1660,  510, 576,  514, 572,  514, 1658,  512, 574,  514, 574,  514, 1658,  512, 1660,  512, 576,  514, 1660,  536, 550,  512, 576,  514, 576,  512, 1660,  512, 1658,  512, 1658,  512, 1658,  514, 1660,  514, 1658,  510, 1658,  512, 1656,  514, 576,  514, 576,  514, 574,  514, 574,  514, 578,  540, 548,  514, 576,  512, 1658,  512, 576,  514, 1660,  510, 576,  514, 576,  512, 578,  530, 1640,  514, 1656,  512, 576,  512, 1656,  514, 576,  512, 1658,  514, 1658,  514, 1658,  538};  // COOLIX B21F28
  uint16_t set21RawData[199] =    {4340, 4416,  486, 1660,  512, 574,  514, 1658,  512, 1656,  514, 576,  514, 574,  514, 1658,  514, 578,  516, 572,  514, 1658,  514, 574,  514, 576,  514, 1656,  514, 1658,  512, 576,  514, 1660,  526, 560,  514, 576,  514, 576,  514, 1658,  514, 1658,  514, 1658,  512, 1658,  514, 1660,  538, 1630,  514, 1658,  512, 1656,  516, 576,  514, 574,  514, 576,  514, 576,  514, 578,  538, 550,  514, 1658,  512, 1656,  516, 576,  514, 1658,  512, 576,  514, 576,  514, 578,  538, 1630,  516, 574,  514, 576,  512, 1658,  512, 576,  514, 1656,  514, 1658,  512, 1656,  540, 5192,  4368, 4352,  510, 1656,  514, 574,  514, 1658,  514, 1656,  516, 576,  514, 574,  514, 1660,  512, 576,  514, 574,  514, 1658,  514, 576,  512, 574,  514, 1658,  514, 1658,  512, 578,  512, 1660,  520, 566,  514, 576,  514, 576,  514, 1658,  514, 1656,  514, 1658,  514, 1658,  514, 1660,  536, 1630,  516, 1660,  510, 1656,  516, 574,  514, 576,  512, 576,  514, 576,  514, 578,  514, 572,  514, 1656,  516, 1658,  514, 574,  512, 1658,  514, 576,  514, 574,  514, 578,  514, 1656,  512, 574,  514, 576,  516, 1656,  514, 574,  514, 1656,  514, 1658,  514, 1658,  538};  // COOLIX B21F68
  uint16_t set22RawData[199] =    {4340, 4390,  512, 1658,  512, 576,  514, 1658,  512, 1658,  512, 576,  514, 576,  512, 1658,  514, 578,  536, 548,  514, 1658,  514, 576,  514, 576,  512, 1656,  516, 1656,  516, 574,  514, 1658,  538, 550,  512, 576,  514, 576,  514, 1658,  514, 1658,  512, 1658,  514, 1656,  514, 1658,  536, 1632,  514, 1658,  514, 1658,  514, 574,  514, 574,  514, 576,  514, 576,  514, 578,  514, 572,  514, 1656,  514, 1660,  512, 1656,  514, 1658,  512, 574,  514, 576,  514, 576,  518, 1654,  510, 576,  514, 576,  512, 576,  514, 574,  514, 1658,  514, 1656,  514, 1656,  540, 5190,  4366, 4350,  512, 1656,  514, 576,  514, 1656,  514, 1658,  514, 574,  514, 576,  512, 1656,  514, 576,  538, 550,  514, 1656,  514, 574,  514, 576,  514, 1656,  514, 1660,  512, 574,  514, 1660,  520, 566,  514, 574,  516, 574,  514, 1658,  512, 1658,  512, 1658,  512, 1658,  514, 1660,  538, 1632,  512, 1658,  514, 1656,  514, 576,  512, 576,  514, 576,  514, 574,  514, 576,  538, 548,  514, 1658,  512, 1658,  514, 1658,  514, 1660,  510, 574,  516, 574,  514, 578,  538, 1632,  512, 578,  512, 574,  514, 576,  512, 576,  514, 1656,  514, 1656,  514, 1662,  536};  // COOLIX B21F78
  uint16_t set23RawData[199] =    {4368, 4366,  516, 1658,  514, 574,  514, 1658,  514, 1656,  514, 576,  512, 576,  514, 1658,  514, 578,  536, 550,  514, 1660,  512, 574,  514, 576,  514, 1660,  512, 1660,  512, 576,  512, 1660,  538, 550,  514, 574,  516, 574,  514, 1660,  510, 1658,  514, 1658,  514, 1658,  512, 1658,  540, 1632,  514, 1656,  514, 1658,  512, 576,  514, 574,  516, 574,  514, 574,  514, 576,  540, 548,  514, 1656,  516, 576,  514, 1660,  510, 1658,  512, 576,  514, 574,  514, 578,  514, 1656,  514, 574,  514, 1660,  512, 574,  516, 574,  514, 1658,  514, 1658,  512, 1656,  540, 5190,  4370, 4350,  514, 1658,  512, 576,  514, 1656,  514, 1656,  514, 576,  514, 574,  514, 1656,  516, 576,  538, 550,  514, 1658,  512, 576,  514, 574,  514, 1660,  512, 1658,  514, 576,  514, 1658,  540, 548,  514, 576,  514, 576,  514, 1658,  512, 1660,  512, 1656,  514, 1658,  514, 1660,  538, 1632,  512, 1656,  514, 1660,  512, 576,  514, 574,  514, 576,  514, 576,  514, 576,  538, 548,  514, 1658,  514, 574,  514, 1660,  512, 1658,  514, 574,  514, 576,  512, 578,  538, 1632,  514, 574,  514, 1658,  514, 574,  514, 576,  514, 1656,  514, 1658,  512, 1660,  538};  // COOLIX B21F58
  uint16_t set24RawData[199] =    {4396, 4344,  514, 1656,  514, 574,  514, 1660,  512, 1658,  512, 574,  516, 574,  514, 1656,  514, 576,  540, 548,  514, 1658,  512, 576,  514, 576,  512, 1660,  510, 1658,  512, 576,  514, 1660,  538, 548,  514, 576,  514, 574,  514, 1658,  514, 1656,  516, 1656,  514, 1658,  514, 1658,  538, 1632,  514, 1656,  514, 1656,  514, 576,  514, 574,  516, 574,  514, 576,  514, 578,  526, 560,  514, 1658,  514, 574,  514, 574,  516, 1658,  512, 574,  514, 574,  514, 576,  540, 1630,  514, 574,  514, 1656,  516, 1656,  514, 574,  514, 1656,  514, 1658,  514, 1656,  540, 5190,  4370, 4350,  514, 1658,  514, 574,  514, 1660,  512, 1656,  514, 574,  516, 576,  514, 1658,  514, 578,  516, 570,  514, 1658,  514, 574,  514, 576,  514, 1658,  512, 1658,  514, 576,  512, 1658,  540, 548,  514, 576,  514, 576,  514, 1658,  514, 1658,  512, 1660,  512, 1656,  514, 1658,  538, 1628,  516, 1658,  514, 1658,  514, 574,  514, 576,  514, 574,  514, 574,  516, 576,  538, 548,  514, 1658,  514, 574,  516, 574,  514, 1658,  514, 576,  514, 574,  514, 576,  538, 1632,  512, 574,  516, 1658,  512, 1656,  514, 576,  512, 1660,  512, 1660,  512, 1660,  518};  // COOLIX B21F48
  uint16_t set25RawData[199] =    {4372, 4342,  514, 1656,  514, 576,  514, 1658,  514, 1652,  516, 574,  514, 576,  514, 1682,  488, 578,  538, 548,  514, 1658,  512, 576,  514, 574,  514, 1658,  512, 1656,  514, 574,  514, 1658,  538, 550,  514, 574,  514, 574,  514, 1656,  516, 1656,  516, 1656,  514, 1656,  514, 1660,  514, 1654,  514, 1658,  514, 1656,  514, 574,  514, 576,  514, 574,  514, 576,  514, 578,  538, 1630,  516, 1682,  488, 574,  514, 574,  514, 1656,  514, 576,  514, 576,  514, 576,  540, 548,  514, 574,  514, 1656,  516, 1656,  514, 576,  514, 1656,  514, 1656,  514, 1656,  542, 5188,  4370, 4350,  514, 1656,  514, 574,  514, 1656,  514, 1656,  514, 574,  514, 574,  514, 1656,  514, 578,  538, 548,  514, 1656,  514, 576,  514, 576,  514, 1658,  512, 1656,  514, 574,  514, 1658,  538, 548,  516, 576,  514, 574,  514, 1658,  512, 1658,  514, 1656,  514, 1658,  514, 1660,  538, 1630,  514, 1658,  512, 1658,  512, 574,  514, 576,  514, 574,  516, 574,  514, 578,  538, 1630,  514, 1660,  512, 576,  514, 574,  516, 1656,  514, 574,  514, 576,  514, 578,  538, 548,  514, 576,  514, 1656,  514, 1658,  514, 574,  514, 1658,  514, 1656,  514, 1658,  538};  // COOLIX B21FC8
// =============================================================================================================


  void setup() {
    Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
    irrecv.enableIRIn(); //inicia o receptor infravermelho (IR)
    irsend.begin();
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();

    //configura modo como estação
    WiFi.mode(WIFI_STA);
    
    //parametros: WiFi.softAP(nomeDoAccessPoint, senhaRede)
    //redeVisivel: a rede pode ou não aparecer para outros serviços 
    WiFiMulti.addAP("UFPI", "");
    
    //enquanto o cliente não estiver conectado, escreve "."
    while (WiFiMulti.run() != WL_CONNECTED) 
     Serial.print(".");
  }

  void set_Ar(int set){ 
    switch(set) {
      case 0:{
      irsend.sendRaw(powerOffRawData, 199, 38);
      set_Display("Desligando....");
      delay(1000);
      set_Display("Desligado");
      break;
      }
      case 1:{
      irsend.sendRaw(powerOnRawData, 199, 38);
      set_Display("Ligando...");
      delay(1000);
      set_Display("Temperatura: 22");
      break;
      }
      case 17:{
      irsend.sendRaw(set17RawData, 199, 38);
      set_Display("Temperatura: 17");
      break;
      }
      case 18:{
      irsend.sendRaw(set18RawData, 199, 38);
      set_Display("Temperatura: 18");
      break;
      }
      case 19:{
      irsend.sendRaw(set19RawData, 199, 38);
      set_Display();
      break;
      }case 20:{
      irsend.sendRaw(power20RawData, 199, 38);
      set_Display("Temperatura: 19");
      break;
      }
      case 21:{
      irsend.sendRaw(power21RawData, 199, 38);
      set_Display("Temperatura: 21");
      break;
      }
      case 22:{
      irsend.sendRaw(power22RawData, 199, 38);
      set_Display("Temperatura: 22");
      break;
      }
      case 23:{
      irsend.sendRaw(power23RawData, 199, 38);
      set_Display("Temperatura: 23");
      break;
      }
      case 24:{
      irsend.sendRaw(power24RawData, 199, 38);
      set_Display("Temperatura: 24");
      break;
      }
      case 25:{
      irsend.sendRaw(power25RawData, 199, 38);
      set_Display("Temperatura: 25");
      break;
      }
    
    }
  }
  
  void set_Display(String msg){
    lcd.clear();
    for(int i = 0; i < msg.length(); i++ ) {
      lcd.setCursor(i, 0);
      lcd.print(msg.charAt(i));
    }
    
 }
  void loop() {
    //porta 5000 do protocolo TCP, deve ser a mesma utilizada pelo servidor
    const uint16_t port = 9999;
    //endereço ip, deve ser o mesmo utilizado pelo servidor
    const char * host = "10.94.15.69";
  
    //inicializa a lib do cliente
    WiFiClient client;



    
   if (irrecv.decode(&results))   {  //decodificamos a entrada do receptor infravermelho
     
      switch (results.value) {
        case 16720605: { //ligar (seta esquerda) 
        temp_atual = 22;
        set_Ar(0);
        break;
      }
      
      case 16761405:{   //desligar (seta direita)
        temp_atual = -1;
        set_Ar(1);
        break;
      }
  
      case 16736925:   { //seta pra cima
        temp_atual = temp_atual + 1;
        set_Ar(temp_atual);
  
        break;
      }
  
      case 16754775:  {//seta pra baixo
        temp_atual = temp_atual - 1;
        set_Ar(temp_atual);
  
        break;
      }
    }
   irrecv.resume(); // Recebe o proximo valor do botÃ£o que pressionamos
   
   if (!client.connect(host, port))    {    //Envioda temperatura atual
      Serial.println("Falha...");
      return;
    }else{
      client.println(" ");
      client.println("Disnel");
      client.println(temp_atual); 
      client.println("-1.0"); 
      client.println("-1.0"); 
      client.println("fim"); 
    }
   }
  delay(100);
  }
