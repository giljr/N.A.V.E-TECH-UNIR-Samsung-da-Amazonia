/*Project: 
      25_UNIR_blinking_led_attiny85
      Link: [TODO: link to jungletronics page goes here ]
   
   Objective:       
      This sketch is to upload to ATtiny85. It will blink an LED on Pin Zero. 
      ATtiny85 can be programmed with Arduino as ISP.
      Tutorials: Programming an ATtiny w/ Arduino 1.6 (or 1.0)
      https://highlowtech.org/?p=1695
      Arduino to Arduino — Cheap AVR Programming
      How To Flash Your Arduino Using Other Arduino Board — #basicTronic #Episode 10
      https://medium.com/jungletronics/arduino-to-arduino-cheap-avr-programming-a59dbeb5317a
      Arduino’s Bootloader
      What is the concept of the bootloader?
      https://medium.com/jungletronics/arduinos-bootloader-9c21b1fda662
      ATtiny85 Easy Flashing Through Arduino
      Programming ATtiny85 in 10 steps #arduSerie 29
      https://medium.com/jungletronics/attiny85-easy-flashing-through-arduino-b5f896c48189
      This is a component of my study on nRF24L0 radios.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):
   
   Authors:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                    Arduino Uno R3
                    (https://docs.arduino.cc/hardware/uno-rev3 )                   
   
   Software:    Arduino IDE 2.2.1
                  
   Connections:       


   output:      The LED on Pin Zero blinks

   Based on: 
          ArduinoISP version 04m3
          Copyright (c) 2008-2011 Randall Bohn
          If you require a license, see
          http://www.opensource.org/licenses/bsd-license.php

   Date: 14 jan 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
 
*/
void setup() {
                           // initialize digital ATtiny pin 0 as an output.
  pinMode(0, OUTPUT);
}

                           // the loop function runs over and over again forever
void loop() {
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a 100 ms
  digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  delay(100);              // wait for  a 100 ms
}
