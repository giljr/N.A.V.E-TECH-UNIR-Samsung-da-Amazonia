/*Project: 
      39_UNIR_esp32_bluetooth_hello_world
      Link: [TODO: link to jungletronics page goes here ]
   
   Objective:          
      Our proposal involves utilizing a cellular phone to establish a connection
      with the Bluetooth Module of ESP32 and subsequently regulate the LED functionality. 
      Specifically, we aim to control the LED situated on the Heltec WiFi 32 board, 
      which is directly linked to PIN25/GPIO25.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):
   
   Authors:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                    ESP32 - WiFi LoRa 32(V2)
                    (https://heltec.org/project/wifi-lora-32-v3/)

   Software:    Arduino IDE 2.2.1
                  
   Connections: Built-in LED PIN 25

   output:      Connecting to ESP32-BT
                Connected
                1
                0 
   Based on: 
          
          Enjoy Mechatronics
          https://youtu.be/EWxM8Ixnrqo?si=gEplBRE-d6_V6clq

   Date:  26 jan, 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
 */
#include "BluetoothSerial.h"
char cmd;
BluetoothSerial serialBT;

void setup() {
  pinMode(25, OUTPUT);
  serialBT.begin("ESP32-BT");

}

  void loop() {
    if(serialBT.available()){
      cmd = serialBT.read();
    }
    if(cmd == '1'){
      digitalWrite(25, HIGH);
    }
    if(cmd ==  '0'){
      digitalWrite(25, LOW);
    }
    delay(20);

  }
