/*Project: 
      40_UNIR_lcd_i2c_custom_char.ino
      Link: [TODO: link to jungletronics page goes here ]
   
   Objective:          
      Defines a set of custom characters and functions to display them on an LCD screen.
      LCD 16x2 I2C Library: LCD-I2C by Frank Hafele(v0.2.0)
      Please see the next project #41.
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


uint8_t solar[8]  = {0b11111,0b10101,0b11111,0b10101,0b11111,0b10101,0b11111,0b00000};
uint8_t battery[8]  = {0b01110,0b11011,0b10001,0b10001,0b10001,0b10001,0b10001,0b11111};
uint8_t termometer[8]  = {0b00100,0b01010,0b01010,0b01110,0b01110,0b11111,0b11111,0b01110};
uint8_t humidity[8]  = {0b00100,0b01010,0b01010,0b01110,0b00100,0b00000,0b00100,0b00000};
uint8_t current[8] = {0b00001,0b00010,0b00100,0b01000,0b11000,0b00110,0b00100,0b01000};
uint8_t charge[8]  = {0b01010,0b11111,0b10001,0b10001,0b10001,0b01110,0b00100,0b00100};
uint8_t alarm[8] = {0b00000,0b00100,0b01110,0b01110,0b01110,0b11111,0b00000,0b00100};
uint8_t degree[8] = { 0b00110,0b01001,0b01001,0b00110,0b00000,0b00000,0b00000,000000,};
uint8_t _not[8] = {0b00000,0b10001,0b01010,0b00100,0b01010,0b10001,0b00000,0b00000};
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
    lcd.createChar(7, degree);


    // lcd.write(0);
    // lcd.write(1);
    // lcd.write(2);
    // lcd.write(3);
    // lcd.write(4);
    // lcd.write(5);
    // lcd.write(6);
    // lcd.write(7);

    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print(" Energy Custom");
    lcd.setCursor(0, 1);
    lcd.print("     Characters ");
    delay(2000);


}

void loop()
{

  // Present each symbol - it displays symbols and values individually.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Solar Grid");
  lcd.setCursor(0, 1);
  lcd.write(0);  // solar grid
  lcd.setCursor(2, 1);
  lcd.print("*"); 
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Battery Status");
  lcd.setCursor(0, 1);
  lcd.write(1);  // battery status
  lcd.setCursor(2, 1);
  lcd.print("*");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print(" Temperature (C)");
  lcd.setCursor(0, 1);
  lcd.write(2);
  lcd.setCursor(2, 1);
  lcd.print("*");   //lcd.write(7); lcd.print("C"); 
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print(" Humidity (%)");
  lcd.setCursor(0, 1);
  lcd.write(3);
  lcd.setCursor(2, 1);
  lcd.print("*");   
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print(" Current(A)");
  lcd.setCursor(0, 1);
  lcd.write(4);
  lcd.setCursor(2, 1);
  lcd.print("*");  
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print(" Charging");
  lcd.setCursor(0, 1);
  lcd.write(5);
  lcd.setCursor(2, 1);
  lcd.print("*");   
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print(" Alarm ");
  lcd.setCursor(0, 1);
  lcd.write(6);
  lcd.setCursor(2, 1);
  lcd.print("*");   
  delay(3000);
  
  // "Mosaic: A visual composition created by merging the symbol with its associated value.
  // This technique maximizes information display within a compact area."
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.setCursor(2, 0);
  lcd.print("*");

  lcd.setCursor(8, 0);
  lcd.write(0);
  lcd.setCursor(10, 0);
  lcd.print("*");
    
  lcd.setCursor(0, 1);
  lcd.write(0);
  lcd.setCursor(2, 1);
  lcd.print("*");

  lcd.setCursor(8, 1);
  lcd.write(0);
  lcd.setCursor(10, 1);
  lcd.print("*");
  delay(3000);
  lcd.clear();
}
