/*Project: 
      47_UNIR_tls2561_Light_to_Digital_converter_v1.ino      
      Link: [TODO: LINK TO JUNGLETRONICS GOES HERE]
   
   Objective: 
      This code demonstrates how to initialize and read data from the TSL2561 
      light sensor module over the I2C bus, providing insight into the ambient 
      light conditions in terms of Full Spectrum, Infrared, and Visible light.  
      It is designed to work with the TSL2561_I2CS I2C Mini Module GY2561.
      It uses a chip TSL2561 which is a 16-bit digital I2C light sensor from 
      Texas Advanced Optoelectronic Solutions, Incorporated (TAOS Inc) based in Plano, Texas.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   https://medium.com/jungletronics/drv8825-driver-stepper-motor-24byj48-bb14237f4066        

   Author:      OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                     Arduino R3
                    (https://www.arduino.cc/)
                   I2C Mini Module GY2561
                   (https://www.amazon.com/Luminosity-TSL2561-Digital-Breakout-Integrating/dp/B0925YP1JV)
   
   Connections: See Fritzing (Link above)

    Output:    Visible Value :605.00
               Visible Value :605.00
               ....

   Based on:   Measuring illuminance using GY-2561 and ESP-WROOM-02
               DECEMBER 14, 2016 OKIRAKU-CAMERA by OKIRAKU-CAMERA
               https://okiraku-camera.tokyo/blog/?p=5390
   
   Date:  3 Feb, 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
*/

#include<Wire.h>

                                       // TSL2561 I2C address is 0x39(57)
#define Addr 0x39

void setup()
{
                                       // Initialise I2C communication as MASTER 
  Wire.begin();
                                       // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

                                       // Starts I2C communication
  Wire.beginTransmission(Addr);
                                       // Select control register
  Wire.write(0x00 | 0x80);
                                       // Power ON mode
  Wire.write(0x03);
                                       // Stop I2C Transmission
  Wire.endTransmission();

                                       // Starts I2C communication
  Wire.beginTransmission(Addr);
                                       // Select timing register
  Wire.write(0x01 | 0x80);
                                       // Nominal integration time = 402ms
  Wire.write(0x02);
                                       // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
  
}

void loop()
{ 
  unsigned int data[4];
  for(int i = 0; i < 4; i++)
  {
                                       // Starts I2C communication
    Wire.beginTransmission(Addr);
                                       // Select data register
    Wire.write((140 + i));
                                       // Stop I2C Transmission
    Wire.endTransmission();
    
                                       // Request 1 byte of data
    Wire.requestFrom(Addr, 1);
    
                                       // Read 1 bytes of data
    if(Wire.available() == 1)
    {
      data[i] = Wire.read();
     }
     delay(200);
  }
  
                                        // Convert the data
  double ch0 = ((data[1] & 0xFF) * 256) + (data[0] & 0xFF);
  double ch1 = ((data[3] & 0xFF) * 256) + (data[2] & 0xFF);

                                        // Output data to serial monitor
  Serial.print("Full Spectrum(IR + Visible) :");
  Serial.println(ch0);
  Serial.print("Infrared Value :");
  Serial.println(ch1);
  Serial.print("Visible Value :");
  Serial.println(ch0-ch1);
}
