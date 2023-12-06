/*
  Project : 04 UNIR - LCD Menu PLUS Button  
  Ino File: 04_UNIR_LCD_Menu_PLUS_Button.ino
  link: https://www.tinkercad.com/things/hCIPRuBCSEj-04-unir-lcd-menu-plus-botton

   Objective: 
      
      This project simply initializes the LCD and simulates a menu. 
      The code is in development and boils down to project number 5.     It was developed by Group 3 encounters on a Sunday, December 2, in Porto Velho city. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   Based on : Exploring Arduino, Second Edition
              Code Listing 12-1: LCD Text with an Incrementing Number
              https://www.exploringarduino.com/content2/ch12
              Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
              Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )

   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                 (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
              
   Authors:     MARQUES, Ana P.; RIBEIRO, J.Antônio; OLIVEIRA, Gilberto Jr.
   
   Hardware:    Development Boards:
                   Arduino UNO:    Microcontroller board based on the ATmega328P (datasheet)                   
   
   Software:    Tinkercad : It is a free, easy-to-use app for 3D design, electronics, and coding.
                 LIB: LiquidCrystal.h (https://www.arduino.cc/reference/en/libraries/liquidcrystal/)
                                
   Connections:
   The LCD is connected to the microcontroller as follows:
                    Arduino UNO Rev.3 board:                
                    Microcontroller      LCD               
                    ===============      ===              
                          D4             DB4                 
                          D5             DB5                 
                          D6             DB6                   
                          D7             DB7                   
                          D3             E                     
                          D2             R/S                   
                          GND            RW   

   Date:   Dez 2023
*/
#include <LiquidCrystal.h>

#define B1 A1
#define B2 A2
#define B3 A3

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // Set the correct pins for your LCD


int m_state_level_one = 1;
int m_state_level_two = 1;
int state_selected = 0;
int submenu = 0;

void setup() {
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  Serial.begin(9600);

  										// splash init 5 seconds delay
  lcd.begin(16, 2);  					// Adjust the number of columns and rows on your LCD
  lcd.print("Navetec Group 03");
  lcd.setCursor(0, 1);
  lcd.print("****************");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(" ANA P. MARQUES");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("  GILBERTO JR");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("ANTONIO RIBEIRO");
  delay(2000);

  lcd.clear();
  lcd.noCursor();

  lcd.setCursor(0, 0);
  lcd.print(">MANUAL  [ENTER]");

  lcd.setCursor(0, 1);
  lcd.print(" AUTOMAT        ");
}

void loop() {
  int ENTER_MENU = digitalRead(B2);
  int SELECT_MENU = digitalRead(B1);
  int RETURN_MAIN_MENU = digitalRead(B3);

  if (SELECT_MENU == HIGH  && submenu == 0) {
    switch (m_state_level_one) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print(">");
        lcd.setCursor(9, 0);
        lcd.print("[ENTER]");
        m_state_level_one = 2;
        state_selected = 1;
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(9, 1);
        lcd.print("        ");
        break;
      case 2:
        lcd.setCursor(0, 1);
        lcd.print(">");
        lcd.setCursor(9, 1);
        lcd.print("[ENTER]");
        m_state_level_one = 1;
        state_selected = 2;
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(9, 0);
        lcd.print("                ");
        break;
    }
  }

 if (ENTER_MENU == HIGH) {
    switch (state_selected) {
      case 1:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" MANUAL");
      	lcd.setCursor(9, 0);
      	lcd.print(">   RED");
        lcd.setCursor(9, 1);
      	lcd.print("  GREEN");
        //lcd.setCursor(9, 1);
        //lcd.print("> BLUE");
        submenu = 1;
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" AUTOMAT");
        submenu = 1;
        int exit = 0;  					// Initialize exit as 0 to enter no loop
        for (int i = 0; i < 4; i++) {
          lcd.setCursor(9, 0);
          lcd.print(">   RED");
          								// simulate the logic for the pin here
          delay(1000);
          
          lcd.setCursor(9, 0);
          lcd.print("> GREEN");
  
          delay(1000);
          
          lcd.setCursor(9, 0);
          lcd.print(">  BLUE");

          delay(1000);
        }
        break;
    }
  }

  if (SELECT_MENU == HIGH && submenu == 1) {
    switch (m_state_level_two) {
      case 1:
        lcd.setCursor(9, 0);
        lcd.print(">");
        m_state_level_two = 2;
        lcd.setCursor(9, 1);
        lcd.print(" ");
        break;
      case 2:
        lcd.setCursor(9, 1);
        lcd.print(">");
        m_state_level_two = 3;
        lcd.setCursor(9, 0);
        lcd.print(" ");
        break;
      case 3:
        lcd.setCursor(9, 1);
        lcd.print(">");
        m_state_level_two = 1;
        lcd.setCursor(9, 0);
        lcd.print(" ");
        break;
    }
  }

  if (RETURN_MAIN_MENU == HIGH && submenu == 1) {
    									// Ação: Retornar ao menu principal
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">MANUAL  [ENTER]");
    lcd.setCursor(0, 1);
    lcd.print(" AUTOMAT        ");
    submenu = 0;  						// Set submenu back to 0 to indicate you are in the main menu
    m_state_level_one = 1;  			// Resets the state of the first menu level
    m_state_level_two = 1;  			// Resets the state of the second menu level
    state_selected = 0;     			// Resets the selected state
  }

  delay(250);  							// Necessary to treat debounce
}
