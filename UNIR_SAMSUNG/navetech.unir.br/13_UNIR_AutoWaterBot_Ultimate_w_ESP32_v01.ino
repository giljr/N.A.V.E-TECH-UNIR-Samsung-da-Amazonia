/* Project: 
      13 UNIR - AutoWaterBot Ultimate With ESP32 v0.1
      Link: https://www.tinkercad.com/things/ehEDYXSSMlV-12-unir-autowaterbotultimateversionv02

   Objective: 
      The intention of this code is to achieve the step-by-step implementation of the Autobot. 
      This initial code only displays the splash screen 
      and introduces the professionals working on the automatic irrigation project.
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
                                
   Connections:
   The Heltec_ESP32 is connected to the computer w/ USB Cable


   Based on:  lxyzn from HelTec AutoMation, ChengDu, China
              成都惠利特自动化科技有限公司
              https://heltec.org
   
   Date:    21 dez 2023
*/

#include "Arduino.h"
#include "heltec.h"

// Adapted from Adafruit_SSD1306
void fillRect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<DISPLAY_HEIGHT/2; i+=3) {
    Heltec.display->setColor((color % 2 == 0) ? BLACK : WHITE); // alternate colors
    Heltec.display->fillRect(i, i, DISPLAY_WIDTH - i*2, DISPLAY_HEIGHT - i*2);
    Heltec.display->display();
    delay(100);
    color++;
  }
  // Reset back to WHITE
  Heltec.display->setColor(WHITE);
}

void printGroup(void) {
  // Initialize the log buffer
  // allocate memory to store 6 lines of text and 16 chars per line.
  Heltec.display->setLogBuffer(6, 16);

  // Some test data
  const char* names[] = {
  "Navetec GROUP 03  ",
  "proudly",
  " Present: ",
  "  ",
  "AutoWaterBot_Ultimate_0.1 "
  };

  for (uint8_t i = 0; i < 5; i++) {
    Heltec.display->clear();
    // Print to the screen
    Heltec.display->println(names[i]);
    // Draw it to the internal screen buffer
    Heltec.display->drawLogBuffer(0, 0);
    // Display it on the screen
    Heltec.display->display();
    delay(500);
  }
}

void printBuffer(void) {
  // Initialize the log buffer
  // allocate memory to store 6 lines of text and 16 chars per line.
  Heltec.display->setLogBuffer(6, 16);

  // Some test data
  const char* names[] = {
  "  Professionals:  ",
  // "****************",
  " ANA P. MARQUES",
  " GILBERTO JR",
  " ANTONIO RIBEIRO",
  " ANGELINA FREIRE"
  };

  for (uint8_t i = 0; i < 5; i++) {
    Heltec.display->clear();
    // Print to the screen
    Heltec.display->println(names[i]);
    // Draw it to the internal screen buffer
    Heltec.display->drawLogBuffer(0, 0);
    // Display it on the screen
    Heltec.display->display();
    delay(1000);
  }
}

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  
  Heltec.display->setContrast(255);

  fillRect();
  delay(2000);
  Heltec.display->clear();

  printGroup();
  delay(2000);
  Heltec.display->clear();

  printBuffer();
  delay(2000);
  Heltec.display->clear();
}

void loop() { }