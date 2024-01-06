/*
Project: 
      21_UNIR_thermal_infrared_sensor_GY_906_MLX90614_v1
      Link: https://medium.com/jungletronics/thermal-infrared-sensor-gy-906-f95710fe02d7
   Objective:       
      In this project we will be crafting Version 1 of a non-contact thermometer.
      This example reads from the MLX90614 and prints out ambient and object temperatures 
      every half-second or so. Open the serial monitor and set the baud rate to 9600.
      An LED can be attached to pin 8 to monitor for any read errors.
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
                 
   Connections:       MLX90614 ------------- Arduino
                           VDD ------------------ 3.3V
                           VSS ------------------ GND
                           SDA ------------------ SDA (A4 on older boards)
                           SCL ------------------ SCL (A5 on older boards)

   output: 
                  14:52:53.809 -> Object: 29.97*C
                  14:52:53.809 -> Ambient: 31.19*C
                  14:52:53.809 -> 
                  14:52:54.271 -> Object: 29.93*C
                  14:52:54.271 -> Ambient: 31.21*C

   Based on:    Jim Lindblom @ SparkFun Electronics
                October 23, 2015
                https://github.com/sparkfun/SparkFun_MLX90614_Arduino_Library
   
   Date: 04 jan 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
 
*/
#include <Wire.h>                // I2C library, required for MLX90614
#include <SparkFunMLX90614.h>    // SparkFunMLX90614 Arduino library

IRTherm therm;                   // Create an IRTherm object to interact with throughout

const byte LED_PIN = 8;          // Optional LED attached to pin 8 (active low)

void setup() 
{
  Serial.begin(9600);            // Initialize Serial to log output
  therm.begin();                 // Initialize thermal IR sensor
  therm.setUnit(TEMP_C);         // Set the library's units to Farenheit
                                 // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or
                                 // TEMP_K for Kelvin.
  
  pinMode(LED_PIN, OUTPUT);      // LED pin as output
  setLED(LOW);                   // LED OFF
}

void loop() 
{
  setLED(HIGH);                  //LED on
  
                                 // Call therm.read() to read object and ambient temperatures from the sensor.
  if (therm.read())              // On success, read() will return 1, on fail 0.
  {
                                 // Use the object() and ambient() functions to grab the object and ambient
	                         // temperatures.
	                         // They'll be floats, calculated out to the unit you set with setUnit().
    Serial.print("Object: " + String(therm.object(), 2));
    Serial.write('*');           // Degree Symbol
    Serial.println("C");
    Serial.print("Ambient: " + String(therm.ambient(), 2));
    Serial.write('*');           // Degree Symbol
    Serial.println("C");
    Serial.println();
  }
  setLED(LOW);
  delay(500);
}

void setLED(bool on)
{
  if (on)
    digitalWrite(LED_PIN, LOW);
  else
    digitalWrite(LED_PIN, HIGH);
}
