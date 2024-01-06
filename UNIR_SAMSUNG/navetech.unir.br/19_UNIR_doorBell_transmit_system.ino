/*
Project: 
      19_UNIR_doorBell_transmit_system
      Link: https://www.tinkercad.com/things/ehEDYXSSMlV-12-unir-autowaterbotultimateversionv02
            https://medium.com/jungletronics/doorbell-xbee-radios-0dac24e6b83e

   Objective:       
      This sketch focuses on wireless communication utilizing XBee Radios Series 1. 
      The system comprises two Arduino units, each equipped with an XBee shield and a radio module. 
      One Arduino is positioned outside your home or apartment, while the other is located indoors. 
      Upon pressing a button on the outdoor unit, the indoor board triggers the doorbell. 
      The previous code (18) is an integral component of this project.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   Authors:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                    SparkFun XBee Shield
                    (https://www.sparkfun.com/products/12847)
                    Seeeduino Stalker v2.3
                    (https://wiki.seeedstudio.com/Seeeduino_Stalker_v2.3/#stalker-v23-schematic-online-viewer)
                    (https://www.openhacks.com/uploadsproductos/seeeduino_stalker_v2.pdf)
                    Arduino Uno R3
                    (https://docs.arduino.cc/hardware/uno-rev3 )                   
   
   Software:    XCTU (legacy 5.2.8)
                (https://hub.digi.com/support/products/xctu/?path=/support/asset/xctu-installer/)
                XBee Shield Hookup Guide
                (https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide?_ga=2.154318712.17993789.1703803228-504829612.1703803228&_gl=1*9ifkof*_ga*NTA0ODI5NjEyLjE3MDM4MDMyMjg.*_ga_T369JS7J9N*MTcwMzgwMzIyNy4xLjAuMTcwMzgwMzIyNy42MC4wLjA.)

                                
  Output:       This sketch is crafted to wirelessly push a button, resulting in ringing a tone and flashing the RGB LED.

   Connections: 
                HiLetgo 37 Sensors Assortment Kit
                (https://www.amazon.com/HiLetgo-Sensors-Assortment-Raspberry-Projects/dp/B01N5910XS)
                RGB    -    Pins 11,10,9
                Buzzer -    Pin  8

                https://www.ktron.in/product/1k-ohms-3296-multiturn-trimpot-potentiometer/

   Based on:    Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
                Exploring Arduino - Code Listing 11-6: Receiving Arduino
                http://www.exploringarduino.com/content/ch11
   
   Date: 29 dez 2023

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/
                              // We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

                              //For Atmega328P's
                              // XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
                              // XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3);    // RX, TX
                              //Sending POT value to the computer

const int BUT=12;             //BUT on Pin 12

int val;                      //For holding mapped pot value

void setup()
{
                              // Set up both ports at 9600 baud. This value is most important
                              // for the XBee. Make sure the baud rate matches the config
                              // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);         //Start Serial
}

void loop()
{
  val = digitalRead(BUT);      //Read BUT
  Serial.println(val);         //Send value
  delay(50);                   //Delay so we don't flood the computer
  
    if (Serial.available())
  {                            // If data comes in from serial monitor, send it out to XBee
    XBee.write(Serial.read());
  }
  if (XBee.available())
  {                             // If data comes in from XBee, send it out to serial monitor
    Serial.write(XBee.read());
  }                                   
}
