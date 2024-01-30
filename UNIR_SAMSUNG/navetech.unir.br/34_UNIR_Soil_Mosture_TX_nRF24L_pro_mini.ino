/*Project: 
      34_UNIR_Soil_Mosture_TX_nRF24L_pro_mini
      Link: https://medium.com/jungletronics/smart-soil-moisture-monitoring-system-09135a6dcd87
   
   Objective:       
      This sketch is to upload to Arduino paired with nRF24L Radio. See Project 26.
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
               Arduino - Radio SPI - Wire Color
                   7   -  CE       - Black
                   8   -  CSN      - White
                  13   -  SCK      - Orange
                  11   -  MOSI     - Yellow
                  12   -  MISO     - Blue
                   3   -  IRQ      - Red

   output:      The radio receives an integer that increments by one. 

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
uint8_t _moistureLevel;
int pin_gnd = 2;            // Connect the sensor ground pin to Arduino pin 2
int pin_vcc = 3;            // Connect the sensor VCC pin to Arduino pin 3
int pin_soil = A2;          // Connect the sensor signal pin to Arduino analog pin A2

void setup()
{
  pinMode(pin_gnd, OUTPUT); // Set ground pin as OUTPUT
  pinMode(pin_vcc, OUTPUT); // Set VCC pin as OUTPUT
  pinMode(pin_soil, INPUT); // Set soil moisture signal pin as INPUT
  Serial.begin(115200);
  _radio.init(1, 7, 8);     // Initialize radio with Id = 1, CE pin 7, and CSN pin 8
}

void loop()
{
                            // Read soil moisture level
  _moistureLevel = analogRead(pin_soil);

                            // Send soil moisture level via radio communication
  _radio.send(0, &_moistureLevel, sizeof(_moistureLevel));

                            // Delay for two second before the next reading
  delay(2000);
}
