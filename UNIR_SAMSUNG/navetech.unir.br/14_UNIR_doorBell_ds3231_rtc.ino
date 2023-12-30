/*
Project: 
      14_UNIR_doorBell_ds3231_rtc
      Link: https://www.tinkercad.com/dashboard?type=circuits&collection=projects&id=bmwfw7NWfXE

   Objective:       
      This sketch marks the commencement of the code study for a doorbell system. 
      We incorporate the DS3231, a real-time clock system, ideal for electronics projects.
      Here, we set the current time, date, and year. 
      Type carefully in the terminal as soon as it prompts you, sequentially, like 231227w164430x.
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
                    (https://wiki.seeedstudio.com/Seeeduino_Stalker_v2.3/#stalker-v23-schematic-online-viewer)
                    (https://www.openhacks.com/uploadsproductos/seeeduino_stalker_v2.pdf)
                    Arduino Uno R3
                    (https://docs.arduino.cc/hardware/uno-rev3 )                   
   
   Software:    Arduino IDE 2.2.1, to compile please select: 
                        Board: Arduino Pro or Pro Mini  and 
                    Processor: ATMEGA328P 3V3, 8 MHZ)               
                                
  Output:       This sketch is designed to output the real timestamp.

   Connections: 
                It was embedded in the Seeeduino Stalker v2.3.

   Based on:    Eric Ayars - Test of set-time routines for a DS3231 RTC
   links :
                https://github.com/NorthernWidget/DS3231/tree/master
                XCTU (legacy 5.2.8)
                (https://hub.digi.com/support/products/xctu/?path=/support/asset/xctu-installer/)
                XBee Shield Hookup Guide
                (https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide?_ga=2.154318712.17993789.1703803228-504829612.1703803228&_gl=1*9ifkof*_ga*NTA0ODI5NjEyLjE3MDM4MDMyMjg.*_ga_T369JS7J9N*MTcwMzgwMzIyNy4xLjAuMTcwMzgwMzIyNy42MC4wLjA.)

   Date: 29 dez 2023

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

#include <DS3231.h>
#include <Wire.h>

DS3231 myRTC;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;

void getDateStuff(byte& year, byte& month, byte& date, byte& dOW,
                  byte& hour, byte& minute, byte& second) {
                                                // Call this if you notice something coming in on
                                                // the serial port. The stuff coming in should be in
                                                // the order YYMMDDwHHMMSS, with an 'x' at the end.
    boolean gotString = false;
    char inChar;
    byte temp1, temp2;
    char inString[20];
    
    byte j=0;
    while (!gotString) {
        if (Serial.available()) {
            inChar = Serial.read();
            inString[j] = inChar;
            j += 1;
            if (inChar == 'x') {
                gotString = true;
            }
        }
    }
    Serial.println(inString);
                                                // Read year first
    temp1 = (byte)inString[0] -48;
    temp2 = (byte)inString[1] -48;
    year = temp1*10 + temp2;
                                                // now month
    temp1 = (byte)inString[2] -48;
    temp2 = (byte)inString[3] -48;
    month = temp1*10 + temp2;
                                                // now date
    temp1 = (byte)inString[4] -48;
    temp2 = (byte)inString[5] -48;
    date = temp1*10 + temp2;
                                                // now Day of Week
    dOW = (byte)inString[6] - 48;
                                                // now hour
    temp1 = (byte)inString[7] -48;
    temp2 = (byte)inString[8] -48;
    hour = temp1*10 + temp2;
                                                // now minute
    temp1 = (byte)inString[9] -48;
    temp2 = (byte)inString[10] -48;
    minute = temp1*10 + temp2;
                                                // now second
    temp1 = (byte)inString[11] -48;
    temp2 = (byte)inString[12] -48;
    second = temp1*10 + temp2;
}

void setup() {
                                                // Start the serial port
    Serial.begin(57600);
    
                                                // Start the I2C interface
    Wire.begin();
}

void loop() {
    
                                                // If something is coming in on the serial line, it's
                                                // a time correction so set the clock accordingly.
    if (Serial.available()) {
        getDateStuff(year, month, date, dOW, hour, minute, second);
        
        myRTC.setClockMode(false);              // set to 24h
                                                //setClockMode(true); // set to 12h
        
        myRTC.setYear(year);
        myRTC.setMonth(month);
        myRTC.setDate(date);
        myRTC.setDoW(dOW);
        myRTC.setHour(hour);
        myRTC.setMinute(minute);
        myRTC.setSecond(second);
                                                // mysetup: -> 231227w164430x
                                                              
                                                // Test of alarm functions
                                                // set A1 to one minute past the time we just set the clock
                                                // on current day of week.
        myRTC.setA1Time(dOW, hour, minute+1, second, 0x0, true,
                        false, false);
                                                // set A2 to two minutes past, on current day of month.
        myRTC.setA2Time(date, hour, minute+2, 0x0, false, false,
                        false);
                                                // Turn on both alarms, with external interrupt
        myRTC.turnOnAlarm(1);
        myRTC.turnOnAlarm(2);
        
    }
    delay(1000);
}
