/*Project: 
      42_UNIR_EEPROM24LC256v1.ino
      Link: https://medium.com/jungletronics/eeprom-24lc256-reading-and-writing-arduino-sketch-bdfb6e5a3b13
   
   Objective:   
      Reads and writes bytes to and from EEPROM.
      Checks 24LC256 external EEPROM is connected.       
      Basic script to read and write to EEPROM.      
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   https://www.digitaltown.co.uk/components1524LC256EEPROM.php
                Arduino UNO 24LC256 External EEPROM24LC256v1

   Author:      Digital Town
    Edited:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                    https://www.microchip.com/en-us/product/24lc256
                    (https://www.microchip.com/en-us/product/24lc256)
                    Arduino R3
                    (https://www.arduino.cc/)

   Connections: 24LC256 - ARDUINO
                    SCL - A5
                    SDA - A4 
                    GND - GND
                    VCC - 5V
                 Required is a 10K pull up resisto
                  
   Based on:           
                https://www.digitaltown.co.uk/
                https://youtu.be/8AVvlZ57X-c?si=yy7dYxGB01VATvx1
                https://youtube.com/playlist?list=PLIJ8TUBQdHKFndv1c6juFv0uGIWp-_wW5&si=9tawri7AzyZvB-Fs
                Author: Digital Town

   Date:  29 jan, 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
*/

//Wire library required as EEPROM run on I2C
#include "Wire.h"
#define disk1 0x50          //Default Address of 24LC256 eeprom chip in Board

                            //I2C scanner used on start up to mkake sure eeprom is alive and well
 void scani2c(){
  byte error, address;
    int nDevices = 0;

  Serial.println("Scanning...");

  for (byte address = 1; address < 127; ++address) {
                            // The i2c_scanner uses the return value of
                            // the Wire.endTransmission to see if
                            // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
}

                                             //this function writes to an eeprom and location with some passed data.
void EEPROMWrite(int disk, int eepromaddress, byte eepromdata){
  Wire.beginTransmission(disk);
  Wire.write((eepromaddress >> 8));          // MSBthese two lines make sure the address gets sent correctly
  Wire.write((eepromaddress & 0xFF));        // LSB
  Wire.write(eepromdata);                    //data
  Wire.endTransmission();
  delay(10);                                 //required to give it time to write
}

                                             //function to get data from eeprom
                                             //returns 1 for good command, 0 for error
int EEPROMRead(int disk, int startdatareadaddress, int numbytes){//numbytes cannot be bigger than 32
  if(numbytes < 33){
    Wire.beginTransmission(disk1);
                                             //splits the address into 2 bytes for transmission
    Wire.write(startdatareadaddress >> 8);   // MSBthese two lines make sure the address gets sent correctly
    Wire.write(startdatareadaddress & 0xFF); // LSB
    Wire.endTransmission();
    Wire.requestFrom(disk, numbytes);        // request bytes from slave device 
    return 1;
  }else{
    Serial.println("EEPROM Read error, too many bytes requested");
    return 0;  
  }
}



void setup() {  
  Serial.begin(9600);
  Serial.println("EEPROM24LC256v1");
                                             //start the I2C wire library
  Wire.begin();
                                             //scans I2C and should return an address of 0x50 if all is well
  scani2c();

  int q;
  byte nextByte;
  for(q=0;q < 10;q++){
    Serial.println("q =: "+String(q));
    EEPROMRead(disk1, q * 32, 32);            //Read from disk1 starting at an address and read 32 bytes of data 

                                              //work through the bytes recieved
    while(Wire.available()){                  // slave may send less than requested
      nextByte = Wire.read();
      Serial.println(nextByte);;
    }
  }

  Serial.println("Writing first 5 bytes");
  for(q=0;q < 5;q++){
    EEPROMWrite(disk1, q, q);  
  }
  Serial.println("Reading back first 5 bytes");
  EEPROMRead(disk1, 0, 5);                    //Read from disk1 starting at an address and read 32 bytes of data 

                                              //work through the bytes recieved
    while(Wire.available()){                  // slave may send less than requested
      nextByte = Wire.read();
      Serial.println(nextByte);;
    }

}

void loop() {
  

}
