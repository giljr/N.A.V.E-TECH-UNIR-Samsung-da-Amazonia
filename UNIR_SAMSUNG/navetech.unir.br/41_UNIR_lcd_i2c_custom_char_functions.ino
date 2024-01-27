/*Project: 
      41_UNIR_lcd_i2c_custom_char_functions.ino
      Link: [TODO: link to jungletronics page goes here ]
   
   Objective:          
      Defines a set of custom characters and functions to display them on an LCD screen.
      It utilizes the prior project and refactors the code to achieve the same outcome with
      greater efficiency and conciseness. LCD 16x2 I2C Library: LCD-I2C by Frank Hafele(v0.2.0)
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):
   
   Authors:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                    Arduino R3
                    (https://heltec.org/project/wifi-lora-32-v3/)

   Connections:    LCD I2C
                SCL - A5
                SDA - A4 
                GND - GND
                VCC - 5V
                  
   Based on: 
          
         Custom_Chars.ino
         Author: Frank Häfele

   Date:  27 jan, 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by

*/

#include <LCD-I2C.h>

// Default address of most PCF8574 modules, change according

LCD_I2C lcd(0x27, 16, 2);


uint8_t solar[8] = {0b11111,0b10101,0b11111,0b10101,0b11111,0b10101,0b11111,0b00000};
uint8_t battery[8] = {0b01110,0b11011,0b10001,0b10001,0b10001,0b10001,0b10001,0b11111};
uint8_t termometer[8] = {0b00100,0b01010,0b01010,0b01110,0b01110,0b11111,0b11111,0b01110};
uint8_t humidity[8] = {0b00100,0b01010,0b01010,0b01110,0b00100,0b00000,0b00100,0b00000};
uint8_t current[8] = {0b00001,0b00010,0b00100,0b01000,0b11000,0b00110,0b00100,0b01000};
uint8_t charge[8] = {0b01010,0b11111,0b10001,0b10001,0b10001,0b01110,0b00100,0b00100};
uint8_t alarm[8] = {0b00000,0b00100,0b01110,0b01110,0b01110,0b11111,0b00000,0b00100};
uint8_t full_battery[8] = {0b01110,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
// uint8_t negate[8] = {0b00000,0b10001,0b01010,0b00100,0b01010,0b10001,0b00000,0b00000};
// uint8_t degree[8] = { 0b00110,0b01001,0b01001,0b00110,0b00000,0b00000,0b00000,000000,};

void setup()
{
    lcd.begin();
    lcd.display();
    lcd.backlight();

    lcd.createChar(0, solar);
    lcd.createChar(1, battery);
    lcd.createChar(2, termometer);
    lcd.createChar(3, humidity);
    lcd.createChar(4, current);
    lcd.createChar(5, charge);
    lcd.createChar(6, alarm);
    lcd.createChar(7, full_battery);

    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print(" Energy Custom");
    lcd.setCursor(0, 1);
    lcd.print("     Characters ");
    delay(2000);

}

/*
 Displays a custom character along with a description, value, and unit on the LCD.
*/
void displaySymbol(int symbol, const char* description, char* value, char* unit) {
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.print(description);
    lcd.setCursor(0, 1);
    lcd.write(symbol);
    lcd.setCursor(2, 1);
    lcd.print(value);
    lcd.print(unit);
    delay(3000);
}
/*
  Prints a custom character along with a value and unit at a specified position on the LCD.
*/
void printMosaic(int column, int row, uint8_t symbol, char* value, char* unit) {
    lcd.setCursor(column, row);
    lcd.write(symbol);
    lcd.setCursor(column+2, row);    
    lcd.print(value);
    lcd.print(unit);
}

void loop()
{
    // Presentation: 
    // Sequentially showcasing each symbol along with a descriptive explanation of its significance.
    displaySymbol(0, "Solar Grid", "12.2", "v");
    displaySymbol(1, "Battery Status", "10.1", "v");
    displaySymbol(2, "Temperature (C)", "12.2", "c");
    displaySymbol(3, "Humidity (%)", "10.1", "%");
    displaySymbol(4, "Current(A)", "12.2", "a");
    displaySymbol(5, "Charging", "10.1", "v");
    


   // Mosaic: 
   // A visual arrangement formed by combining the symbol and its corresponding value;
   // This technique maximizes information display within a compact area like an LCD 16x2.
    lcd.clear();
    printMosaic(0, 0, 0, "12.2", "v");
    printMosaic(8, 0, 1, "10.1", "v");
    printMosaic(0, 1, 2, "10.1", "C" );
    printMosaic(8, 1, 3, "10.1", "%");

    delay(6000);
    lcd.clear();

    printMosaic(0, 0, 4, "4.7", "a");
    printMosaic(8, 0, 5, "10.1", "v");
    printMosaic(0, 1, 6, "Off", "  " );
    printMosaic(8, 1, 7, " full ", " - ");
    delay(6000);

}

