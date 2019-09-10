// =============================================================================================================
// --- Bibliotecas ---
#include "EmonLib.h"            //Biblioteca para o sensor de corrente
#include "DHT.h"                //biblioteca do sensor de umidade e temperatura
#include <SPI.h>                //Biblioteca SPI            

// =============================================================================================================
// --- Mapeamento de Hardware ---
#define     pin_sct     A0     //sensor de corrente
#define     dht_pin    5       //pino de sinal do dht22 ligado no digital 5

// Definindo o sensor DHT11
#define dht_type DHT22

// Inicializando o sensor DHT
DHT dht(dht_pin, dht_type, 15);


// =============================================================================================================
// --- Constantes do Projeto ---
#define     rede       220     //tensão da rede local 220V
#define      n          50     //número de pontos da média móvel 


// ===============================================================================
// --- Declaração de Objetos ---
EnergyMonitor emon1;            //cria objeto para sensor de corrente



// ===============================================================================
// --- Protótipos das Funções ---
long moving_average();       //Função para filtro de média móvel


// =============================================================================================================
// --- Variáveis Globais ---
short     screens   = 0x01;               //variável para seleção de menus
 

boolean   but_flag  = 0x00,               //flag auxiliar para o botão
          amp_unity = 0x00;               //flag de modificação de múltiplo de unidade de corrente

double    temperatura = 0x00,             //armazena a temperatura em inteiro
          umidade     = 0x00;             //armazena a umidade em inteiro

double    filtrado;                       //receberá os valores filtrados para temperatura e umidade

double    numbers[n];                     //vetor com os valores para média móvel

// =============================================================================================================
// --- Configurações Iniciais ---
void setup()
{

  dht.begin();                          //inicia a comunicação com o dht
  
  pinMode(pin_sct, INPUT);             //entrada para sensor de corrente

  Serial.begin(9600);                  //inicia serial com 9600 baud rate
  
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon1.current(pin_sct, 60);

  Serial.println("LABEL,Hora,Corrente,Temperatura, Umidade");   // Nomeiará as colunas
  
} //end setup


// =============================================================================================================
// --- Loop Infinito ---
void loop()
{  
  double Irms = emon1.calcIrms(1480);   //Calcula a corrente
  
   temperatura = dht.readTemperature();
   umidade     = dht.readHumidity();

   /*
  //Mostra o valor da corrente no serial monitor e display
  Serial.print("Corrente : ");
  Serial.print(Irms); // Irms
  Serial.print(" A");

  //Testanto a armonização procacada pelo filtro de média móvel:
  /*
  Serial.print("Temperatura : ");
  Serial.print(moving_average(temperatura));
  Serial.print(" C");
  Serial.print(" Umidade: ");
  Serial.println(moving_average(umidade));
  

  //Valor da temperatura sem a armonização:
  Serial.print(" Temperatura : ");
  Serial.print(temperatura);
  Serial.print(" C");
  Serial.print(" Umidade: ");
  Serial.print(umidade);
  Serial.println(" g/m^3");

  */

  /*
   * Funiconalidade para mandarmos pro Excel
  Serial.print("DATA,DATE");//A primeira coluna receberá a data calculada pelo excel
  Serial.print(" TIME,");   //juntamente com a hora
  Serial.print(Irms);
  Serial.print(",");
  Serial.print(temperatura);
  Serial.print(",");
  Serial.println(umidade);
  */
  
  //Mandamos cada print desse para o software Prossessing. Ele será o responsável por armazenar as informações no txt.
  Serial.println("");
  Serial.println(Irms);
  Serial.println(temperatura);
  Serial.println(umidade);
  
  delay(5000);  
  
} //end loop



// =============================================================================================================
// --- Desenvolvimento das Funções ---
long moving_average(double original)
{

   //desloca os elementos do vetor de média móvel
   for(int i= n-1; i>0; i--) numbers[i] = numbers[i-1];

   numbers[0] = original; //posição inicial do vetor recebe a leitura original

   long acc = 0;          //acumulador para somar os pontos da média móvel

   for(int i=0; i<n; i++) acc += numbers[i]; //faz a somatória do número de pontos


   return acc/n;  //retorna a média móvel

 
} //end moving_average
