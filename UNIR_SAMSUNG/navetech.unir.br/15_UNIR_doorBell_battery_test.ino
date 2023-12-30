/*
Project: 
      15_UNIR_doorBell_battery_test for Seeeduino Stalker v2.3
      Link: https://www.tinkercad.com/dashboard?type=circuits&collection=projects&id=bmwfw7NWfXE

   Objective:       
      This sketch tests the battery on the Seeeduino Stalker v2.3 board. The output can be 4 states:
      "off" - slepping mode
      "ch " - charging mode
      "ok " - fully charged
      "err" - error status
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

void setup()
{
  Serial.begin(57600);
  analogReference(INTERNAL);
  //analogRead(6);
}

void loop()
{
  char CH_status_print[][4]=
  {
    "off","ch ","ok ","err"
  };
  unsigned char CHstatus = read_charge_status();  //read the charge status
  Serial.print("charge status -->");
  Serial.println(CH_status_print[CHstatus]);
  delay(500);
}


unsigned char read_charge_status(void)
{
  unsigned char CH_Status=0;
  unsigned int ADC6=analogRead(6);
  if(ADC6>900)
  {
    CH_Status = 0;                                //sleeping
  }
  else if(ADC6>550)
  {
    CH_Status = 1;                                //charging
  }
  else if(ADC6>350)
  {
    CH_Status = 2;                                //done
  }
  else
  {
    CH_Status = 3;                                //error
  }
  return CH_Status;
}
