/*
Project: 
      18_UNIR_doorBell_receive_system
      Link: https://www.tinkercad.com/things/ehEDYXSSMlV-12-unir-autowaterbotultimateversionv02
            https://medium.com/jungletronics/doorbell-xbee-radios-0dac24e6b83e

   Objective:       
      This sketch focuses on wireless communication utilizing XBee Radios Series 1. 
      The system comprises two Arduino units, each equipped with an XBee shield and a radio module. 
      One Arduino is positioned outside your home or apartment, while the other is located indoors. 
      Upon pressing a button on the outdoor unit, the indoor board triggers the doorbell. 
      The subsequent code (19) is an integral component of this project.
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

                                
  Output:       This sketch is designed to ring a tone and flash the RGB LED

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

                             //Code running on an Arduino to receive doorbell value
                             // We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

                             //For Atmega328P's
                             // XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
                             // XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3);   // RX, TX

const int RED     = 11;      //Red LED on pin 11
const int GREEN   = 10;      //Green LED on pin 10
const int SPEAKER = 8;       //Speaker on pin 8

char data;                   //Char to hold incoming serial data 
int onLED = GREEN;           //Initially on LED
int offLED = RED;            //Initially off LED
int freq = 131;              //Initial speaker frequency
unsigned long prev_time = 0; //Timer for toggling the LED and speaker

void setup()
{
                             // Set up both ports at 9600 baud. This value is most important
                             // for the XBee. Make sure the baud rate matches the config
                             // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);        //Start serial
}

void loop()
{
 
                             //Handle light and sound toggling
                             //If 100ms have passed
  if (millis() >= prev_time + 100)
  {
                             //Toggle the LED state
    if (onLED == GREEN)
    {
      onLED = RED;
      offLED = GREEN;
    }
    else
    {
      onLED = GREEN;
      offLED = RED;
    }
                             //Toggle the frequency
    if (freq == 261){
       freq = 131;
    } else  {
       freq = 261;
    }
                             //Set the current time in ms to the 
                             //Previous time for the next trip through the loop
    prev_time = millis();  
  }
 
                             //Check if serial data is available
  if (XBee.available() > 0)
  { 
                             //Read byte of data
    data = XBee.read(); 
    
                             //If the button is pressed, play tone and turn LED on
    if (data == '1')
    {
      digitalWrite(onLED, HIGH);
      digitalWrite(offLED, LOW);
      tone(SPEAKER, freq);
    }
                             //If the button is not pressed, turn the sound and light off
    else if (data == '0')
    {
      digitalWrite(onLED, LOW);
      digitalWrite(offLED, LOW);
      noTone(SPEAKER);
    }
  }
}
