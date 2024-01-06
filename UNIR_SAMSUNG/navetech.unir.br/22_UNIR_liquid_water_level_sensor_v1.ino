/*
Project: 
      22_UNIR_liquid_water_level_sensor_v1
      Link: https://medium.com/jungletronics/liquid-water-level-sensor-5a9ddc21d27b

   Objective:       
      This mini float switch, notable for containing no mercury, 
      is designed with a right-angle configuration, 
      allowing for flexible placement at any desired height within the tank.
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
   Output:       This sketch is designed to send data to the serial terminal:
                 
   Connections:           Water Sensor  ------------  Arduino                           
                           REED  SWITCH ------------  D3
                           GREEN LED    ------------  D2


   output: 
                  15:34:36.928 -> 0
                  15:34:36.928 -> 0
                  15:34:36.928 -> 0
                  15:34:36.928 -> 1
                  15:34:36.928 -> 1
                  15:34:36.928 -> 1

   Based on:    Eletrogate - Reed Switch - Sensores e componentes
                (https://youtu.be/ttBtAtqspOg?si=zU4KxSCKg1FrQUY8)
                
         
   
   Date: 04 jan 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
 
*/
#define reed 2 

#define led 3
int val ;
void setup() {
  Serial.begin(9600);
  pinMode(reed, INPUT);
  pinMode(led, OUTPUT);

}

void loop() {
  val = digitalRead(reed);
  Serial.println(val);
  if(digitalRead(reed) == HIGH){
    digitalWrite(led, HIGH);
  }
  else{
   digitalWrite(led, LOW);
 }

}

