/*Project: 
      26_UNIR_basic_TX_nRF24L_arduino
      Link: [TODO: link to jungletronics page goes here ]
   
   Objective:       
      This sketch is to upload to Arduino paired with nRF24L Radio.
      This is the most basic and straightforward test ever conducted for dealing with the nRF24L Radio.
      Tutorial: https://youtu.be/tWEgvS7Sj-8?si=zdPP_o1gHMPNGU54
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


   output:      The radio transmits an integer that increments by one. 

   Based on: 
          dparson
          NRFLite Arduino nRF24L01 library
          https://youtu.be/tWEgvS7Sj-8?si=zdPP_o1gHMPNGU54
          https://github.com/dparson55/NRFLite/tree/master

   Date: 14 jan 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
 
*/
#include <SPI.h>
#include <NRFLite.h>

NRFLite _radio;
uint8_t _data;

void setup()
{
  Serial.begin(115200);
  _radio.init(1, 7, 8); // Set radio to Id = 1, along with its CE and CSN pins
}

void loop()
{
  _data++;
  _radio.send(0, &_data, sizeof(_data));
  delay(1000);
}  
