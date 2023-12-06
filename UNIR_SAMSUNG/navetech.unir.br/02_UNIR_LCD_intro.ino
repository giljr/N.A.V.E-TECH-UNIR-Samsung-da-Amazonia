/*
  Project : 02 UNIR - LCD intro 
  Ino File: 02_UNIR_LCD_intro.ino
  link: https://www.tinkercad.com/things/iMBcjtxUw8Y-02-unir-lcd-intro

   Objective: 
      
      This simply initializes the LCD, displays a splash screen,
      and counts every 1 second on the second line. 
      It was developed by Group 3 encounters on a Sunday, December 2, in Porto Velho city. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   Based on : Exploring Arduino, Second Edition
              Code Listing 12-1: LCD Text with an Incrementing Number
              https://www.exploringarduino.com/content2/ch12
              Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
              Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )

   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                 (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
              
   Authors:     MARQUES, Ana P.; RIBEIRO, J.Antônio; OLIVEIRA, Gilberto Jr.
   
   Hardware:    Development Boards:
                   Arduino UNO:    Microcontroller board based on the ATmega328P (datasheet)                   
   
   Software:    Tinkercad : It is a free, easy-to-use app for 3D design, electronics, and coding.
                 LIB: LiquidCrystal.h (https://www.arduino.cc/reference/en/libraries/liquidcrystal/)
                                
   Connections:
   The LCD is connected to the microcontroller as follows:
                    Arduino UNO Rev.3 board:                
                    Microcontroller      LCD               
                    ===============      ===              
                          D4             DB4                 
                          D5             DB5                 
                          D6             DB6                   
                          D7             DB7                   
                          D3             E                     
                          D2             R/S                   
                          GND            RW   

   Date:   Dez 2023
*/
#include <LiquidCrystal.h>

//Start the time at 0
int time = 0;

//Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup()
{
  //Set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Group Three");
}

void loop()
{
  //Move cursor to second line, first position
  lcd.setCursor(0,1);
  //Print Current Time
  lcd.print(time);  
  //Wait 1 second
  delay(1000);
  //Increment the time
  time++; 
}