/* Project: 
      14_UNIR_AutoWaterBot_Ultimate_Version_v0.2
      Link: https://www.tinkercad.com/things/ehEDYXSSMlV-12-unir-autowaterbotultimateversionv02

   Objective: 
      
      The purpose of this series of Arduino code is to establish a connection using 
      LoRa communication through a LoRa radio. We begin with the simplest code designed 
      for the Heltec ESP32. By accessing the terminal and entering "on" and "off" commands,
      you can control the on-board LED, causing it to illuminate or turn off accordingly.
      (The project is designed to function as an automatic irrigation system)
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                 (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   Authors:     MARQUES, Ana p., RIBEIRO, Antônio J.; OLIVEIRA, Gilberto O.; FREIRE, Angelina
   
   Hardware:    Development Boards:
                    HelTec WiFi Lora Automation(TM) ESP32(V2) Series Dev boards OLED                   
   
   Software:    Arduino & Heltec Libs
                     Expressif:    https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
                                   https://dl.espressif.com/dl/esp-idf/?idf=4.4
                     Heltec_ESP32: https://github.com/HelTecAutomation/Heltec_ESP32/tree/master
                                   https://github.com/HelTecAutomation/Heltec_ESP32
                     For more informations, please vist www.heltec.cn or mail to support@heltec.cn
                                
   Output:    Hello Heltec!
              Serial initial done
              you can see OLED printed OLED initial done!
              LoRa Initial success! (both on Serial as well as OLED096)

   Connections:
   The Heltec_ESP32 is connected to the computer w/ USB Cable


   Based on:  lxyzn from HelTec AutoMation, ChengDu, China
              成都惠利特自动化科技有限公司
              https://heltec.org
   
   Date:    24 dez 2023
*/

#include <heltec.h>

int ledPin = 25;
String cmd;
// the setup routine runs once when starts up
void setup() {

    Serial.begin(115200);
    Serial.println("Hello Heltec!");
    pinMode(ledPin, OUTPUT);
    // Initialize the Heltec ESP32 object
    // https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/heltec.cpp#L22
    Heltec.begin(true /*DisplayEnable Enable*/ , true /*LoRa Disable*/ , true /*Serial Enable*/ , true /*PABOOST Enable*/ , 921E6 /**/ );
}

// the loop routine runs over and over again forever
void loop() {
    if (Serial.available()) {
        cmd = Serial.readString();
        if (cmd == "on") {
            digitalWrite(ledPin, HIGH);
        } else if (cmd == "off") {
            digitalWrite(ledPin, LOW);
        }
    }
}