/*Project: 
      43_UNIR_EEPROM24LC256v2.ino
      Link: https://medium.com/jungletronics/eeprom-24lc256-reading-and-writing-arduino-sketch-bdfb6e5a3b13
   
   Objective:   
      Reading and Writing Integers and Longs to EEPROM. See Project #42.     
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
                 Required is a 10K pull up resistor
    Output:    
                EEPROM24LC256v2
                Scanning...
                I2C device found at address 0x50  !
                done

                q =: 0
                ...
                73    -> address:20
                150
                2
                210
                255
                ...
                Writing an integer to address 10
                firstByte : 48
                secondByte : 57
                48
                57
                12345
                myInt : 12345
                Writing a long to address 20
                eepromdata: 
                1234567890
                firstByte : 73
                secondByte : 150
                thirdByte : 2
                forthByte : 210
                73
                150
                2
                210
                1234567890
                myLong : 1234567890
                ....
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
#define disk1 0x50                    //Default Address of 24LC256 eeprom chip in Board

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
  Wire.write((eepromaddress >> 8));   // MSBthese two lines make sure the address gets sent correctly
  Wire.write((eepromaddress & 0xFF)); // LSB
  Wire.write(eepromdata);             //data
  Wire.endTransmission();
  delay(10);                          //required to give it time to write
}

void EEPROMWriteInt(int disk, int eepromaddress, int eepromdata){
  byte firstByte;
  byte secondByte;
  firstByte = eepromdata >> 8;
  secondByte = eepromdata & 0xFF;
  Serial.println("firstByte : " + String(firstByte)); 
  Serial.println("secondByte : " + String(secondByte));
                                     //firstByte * 256 + secondByte = eepromdata 
  EEPROMWrite(disk, eepromaddress, firstByte);
  EEPROMWrite(disk, eepromaddress + 1, secondByte);
}

void EEPROMWriteLong(int disk, int eepromaddress, long eepromdata){
  byte firstByte;
  byte secondByte;
  byte thirdByte;
  byte forthByte;
  Serial.println("eepromdata: ");
  Serial.println(eepromdata);
  firstByte = eepromdata >> 24;
  secondByte = eepromdata >> 16;
  thirdByte = eepromdata >> 8;
  forthByte = eepromdata & 0xFF;
  Serial.println("firstByte : " + String(firstByte)); 
  Serial.println("secondByte : " + String(secondByte));
  Serial.println("thirdByte : " + String(thirdByte)); 
  Serial.println("forthByte : " + String(forthByte));
  
  EEPROMWrite(disk, eepromaddress, firstByte);
  EEPROMWrite(disk, eepromaddress + 1, secondByte);
  EEPROMWrite(disk, eepromaddress + 2, thirdByte);
  EEPROMWrite(disk, eepromaddress + 3, forthByte);
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

int EEPROMReadInt(int disk, int startdatareadaddress){
  byte firstByte;
  byte secondByte;
  int returnInt;
    Wire.beginTransmission(disk1);
                                             //splits the address into 2 bytes for transmission
    Wire.write(startdatareadaddress >> 8);   // MSBthese two lines make sure the address gets sent correctly
    Wire.write(startdatareadaddress & 0xFF); // LSB
    Wire.endTransmission();
    Wire.requestFrom(disk, 2);               // request 2 bytes 
    firstByte = Wire.read();
    Serial.println(firstByte);
    secondByte = Wire.read();
    Serial.println(secondByte);
    returnInt =  firstByte * 256 + secondByte;
    Serial.println(returnInt);
    return returnInt;
}

long EEPROMReadLong(int disk, int startdatareadaddress){
  byte firstByte;
  byte secondByte;
  byte thirdByte;
  byte forthByte;
  long returnLong;
    Wire.beginTransmission(disk1);
                                             //splits the address into 2 bytes for transmission
    Wire.write(startdatareadaddress >> 8);   // MSBthese two lines make sure the address gets sent correctly
    Wire.write(startdatareadaddress & 0xFF); // LSB
    Wire.endTransmission();
    Wire.requestFrom(disk, 4);               // request 4 bytes 
    firstByte = Wire.read();
    Serial.println(firstByte);
    secondByte = Wire.read();
    Serial.println(secondByte);
    thirdByte = Wire.read();
    Serial.println(thirdByte);
    forthByte = Wire.read();
    Serial.println(forthByte);
    returnLong =  (firstByte * 16777216) +(secondByte * 65536) +(thirdByte * 256) + forthByte;
    Serial.println(returnLong);
    return returnLong;
}



void setup() {  
  Serial.begin(9600);
  Serial.println("EEPROM24LC256v2");
                                             //start the I2C wire library
  Wire.begin();
                                             //scans I2C and should return an address of 0x50 if all is well
  scani2c();

  int q;
  byte nextByte;
  for(q=0;q < 10;q++){
    Serial.println("q =: "+String(q));
    EEPROMRead(disk1, q * 32, 32);           //Read from disk1 starting at an address and read 32 bytes of data 

                                             //work through the bytes recieved
    while(Wire.available()){                 // slave may send less than requested
      nextByte = Wire.read();
      Serial.println(nextByte);;
    }
  }

  Serial.println("Writing first 5 bytes");
  for(q=0;q < 5;q++){
    EEPROMWrite(disk1, q, q);  
  }
  Serial.println("Reading back first 5 bytes");
  EEPROMRead(disk1, 0, 5);                   //Read from disk1 starting at an address and read 32 bytes of data 

    //work through the bytes recieved
    while(Wire.available()){                 // slave may send less than requested
      nextByte = Wire.read();
      Serial.println(nextByte);
    }



    Serial.println("Writing an integer to address 10");
    
                                             //IMPORTANT: as this is an integer it will use 2 bytes so address 10 and 11 will get used.
    int myAddress = 10;
    int myInt = 12345;
    EEPROMWriteInt(disk1, myAddress, myInt);

                                             //we now read back our stored value
    myInt = EEPROMReadInt(disk1, myAddress); 
    Serial.println("myInt : " + String(myInt));

                                             //IMPORTANT: long require 4 bytes so will use myAddress to myAddress + 3
    myAddress = 20;
    long myLong = 1234567890;
    Serial.println("Writing a long to address 20");
    EEPROMWriteLong(disk1, myAddress, myLong);
    myLong = EEPROMReadLong(disk1, myAddress); 
    Serial.println("myLong : " + String(myLong));
}

void loop() {
}
