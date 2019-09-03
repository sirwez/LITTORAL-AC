#include <Wire.h>  //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

LiquidCrystal_I2C lcd(0x3F, 16, 2); //FUNÇÃO DO TIPO "LiquidCrystal_I2C"
 
void setup()
{
  lcd.init();   // INICIALIZA O DISPLAY LCD
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("MASTERWALKERSHOP"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)      
  lcd.print("----NODEMCU----"); //ESCREVE O TEXTO NA SEGUNDA LINHA DO DISPLAY LCD
}
 
void loop()
{
  //PROGRAMAÇÃO DE CÓDIGO DO VOID LOOP - PRA ESSE EXEMPLO PODE FICAR SEM NADA
}
