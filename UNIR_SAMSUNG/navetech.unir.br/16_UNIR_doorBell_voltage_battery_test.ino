/*
Project: 
      16_UNIR_doorBell_voltage_battery_test for Seeeduino Stalker v2.3
      Link: https://www.tinkercad.com/dashboard?type=circuits&collection=projects&id=bmwfw7NWfXE

   Objective:       
      
      This Arduino code is designed to read the analog voltage from a battery 
      using the internal analog-to-digital converter (ADC) and then print the corresponding 
      battery voltage to the serial monitor. 
      
      It calculates the actual voltage using a voltage divider formula:
      
      voltage = BatteryValue * (1.1 / 1024)* (10+2)/2
      
      This formula takes into account the internal reference voltage (1.1V), 
      the resolution of the ADC (1024 levels), and a voltage divider with resistors of 10kΩ and 2kΩ.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   Authors:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                    Seeeduino Stalker v2.3
                          The Stalker v2.3 uses CN3063 chip: it is a complete constant-current /constant
                          voltage linear charger for single cell Li-ion and Li-Polymer rechargeable batteries.                          
                    Arduino ATMega328p, Arduino Pro or Pro-Mini, 8 Mzh  
                
   
   Software:    Arduino IDE 2.2.1, to compile please select: 
                        Board: Arduino Pro or Pro Mini  and 
                    Processor: ATMEGA328P 3V3, 8 MHZ)               
                                
  Output:       This sketch is designed to output the real timestamp.

   Connections: 
                It was embedded in the Seeeduino Stalker v2.3.

   Based on:    Eric Ayars - Test battery status routines for CN3063 chip.
   
   links :      https://www.openhacks.com/uploadsproductos/dse-cn3063.pdf
                https://wiki.seeedstudio.com/Seeeduino_Stalker_v2.3/
                https://wiki.seeedstudio.com/Seeeduino_Stalker_v2.3/#stalker-v23-schematic-online-viewer
                https://www.openhacks.com/uploadsproductos/seeeduino_stalker_v2.pdf   
                https://docs.arduino.cc/hardware/uno-rev3 
                
  Date: 29 dez 2023

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/  

void setup(){
    Serial.begin(57600);
    analogReference(INTERNAL);
}

void loop() {

float voltage;
int BatteryValue;

    BatteryValue = analogRead(A7);
                                                      //Serial.println(BatteryValue);
    voltage = BatteryValue * (1.1 / 1024)* (10+2)/2;  //Voltage devider

    Serial.print("Battery Voltage -> ");
    Serial.print(voltage);
    Serial.print("V   ");
    Serial.println();

    delay(500);
}