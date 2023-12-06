/* Project: 
      06 - UNIR -Roll A Syngle Die
      Link: https://www.tinkercad.com/things/0fnAGGkzqpq-06-unir-single-dice
   
   Objective: 
      This project involves interacting with a die; A Single Die Rolls freely;  each time a user clicks the button, the die rolls randomly.
      It was developed during the N.A.V.E TECH UNIR Samsung Porto Velho Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Marcelo Ribeiro 
      Professor in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
              
   Authors:     MARQUES, Ana P.; RIBEIRO, J.Antônio; OLIVEIRA, Gilberto Jr.
   
   Hardware:    Development Boards:
                   Arduino UNO:    Microcontroller board based on the ATmega328P (datasheet)                   
   
   Software:    Tinkercad : It is a free, easy-to-use app for 3D design, electronics, and coding.
                 LIB: Adafruit_LEDBackpack.h (7-Segment board - HT16K33)    
                      (https://learn.adafruit.com/adafruit-led-backpack/downloads)
                                
   Connections:
   The 7-SEGS is connected to the microcontroller as follows:
                    Arduino UNO Rev.3 board:                
                    Microcontroller      7-SEGS               
                    ===============      ======              
                          A4             D                 
 

   The Momentary Button is connected to the microcontroller as follows: 
                    Arduino UNO Rev.3 board:                
                    Microcontroller      RESISTOR               
                    ===============      ========     
                           D2            1k Ohms

   Date:   5 Dez 2023
*/

#include "Adafruit_LEDBackpack.h"

Adafruit_7segment led_display1 = Adafruit_7segment();
int BUTT = 2;

void setup()
{
  led_display1.begin(112);
  pinMode(A1, INPUT);
}

void loop()
{
  
    
    if(digitalRead(BUTT) == HIGH){
        // print a random number from 1 to 6
        int randNumber = random(1, 7);
        led_display1.println(randNumber);
  		led_display1.writeDisplay();
        delay(100); // Wait for 100 millisecond(s)
    
  }


}