/*
  Project : Arduino Start Up Project
  Ino File: 01_Blinking_8_LEDs.ino
  link: https://www.tinkercad.com/things/fYhatzkBG4p-01-unir-blinking-8-leds/

   Objective: 
      
      This is The Hello World Project. It simply blinks 8 LEDs at variable speeds. Please modify the delayTime variable as you wish.
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                 (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
              
   Authors:     MARQUES, Ana P.; RIBEIRO, J.Antônio; OLIVEIRA, Gilberto Jr.
   
   Hardware:    Development Boards:
                   Arduino UNO:    Microcontroller board based on the ATmega328P (datasheet)                   
   
   Software:    Tinkercad : It is a free, easy-to-use app for 3D design, electronics, and coding.
                 LIB: Adafruit_LEDBackpack.h (7-Segment board - HT16K33)    
                      (https://learn.adafruit.com/adafruit-led-backpack/downloads)
                                
   Connections:

   The LEd's was connected to the microcontroller as follows: 
                    Arduino UNO Rev.3 board:                
                    Microcontroller      Resistors               
                    ===============      =========      
                        D2 - D10          330 Ohms

   Date:   Dez 2023
*/
unsigned int delayTime = 50; 

void setup() {  
  for (int i = 2; i < 10; i++) {   
    pinMode(i, OUTPUT);
  }
}


void loop() {
  for (int i = 2; i < 10; i++) {    
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
    delay(delayTime);
  }
}
