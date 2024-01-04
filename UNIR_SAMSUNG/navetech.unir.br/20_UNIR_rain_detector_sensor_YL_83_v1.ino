/*
Project: 
      20_UNIR_rain_detector_sensor_YL_83_v1
      Link: [TODO: link to jungletronics goes here!]
   Objective:       
      In this sketch, our goal is to create a simple rain detector – a basic version for now (V1).
      In the future, we plan to introduce a crucial feature that will enhance 
      the accuracy of intensity calculations. Stay tuned for updates!
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
                 
   Connections:       YL_83    Arduino        
                        A0	   A0 - Analog pin
                        D0	   D0 - Digital pin - Multimeter
                        GND	   GND
                        VCC	   5V

   Based on:    All the resources for this project:
                https://randomnerdtutorials.com/
                Copyright 2018 https://randomnerdtutorials.com/
                link: https://randomnerdtutorials.com/guide-for-rain-sensor-fc-37-or-yl-83-with-arduino/
   
   Date: 04 jan 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
 
*/

int rainPin = A0;
int greenLED = 6;
int redLED = 7;
bool rainning = false;

                                    // you can adjust the threshold value
int thresholdValue = 700;

void setup(){
  pinMode(rainPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  Serial.begin(9600);
}

void loop() {
                                    // read the input on analog pin 0:
  int sensorValue = analogRead(rainPin);
  Serial.print(sensorValue);
  if(sensorValue < thresholdValue){
    Serial.println(" - It's wet");
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    rainning = true; 
  }
  else {
    Serial.println(" - It's dry");
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    rainning = false; 
  }
  delay(500);
  if(rainning) Serial.println("RAINNING NOW!"); 
}
