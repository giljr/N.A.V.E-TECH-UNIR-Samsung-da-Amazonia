/*
  Project : 03 UNIR - LCD menu 
  Ino File: 03_UNIR_LCD_menu.ino
  link: https://www.tinkercad.com/things/aNrWzjOpfV9-03-unir-lcd-menu-

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

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // Defina os pinos corretos para o seu LCD

int SELECT_MENU = 0;
int ENTER_MENU = 0;
int RETURN_MAIN_MENU = 0;
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
  lcd.begin(16, 2);  // Ajuste o número de colunas e linhas do seu LCD
  lcd.print("Navetec Group 03");
  delay(5000);

  lcd.clear();
  lcd.noCursor();

  lcd.setCursor(0, 0);
  lcd.print(">OPTION1 [ENTER]");

  lcd.setCursor(0, 1);
  lcd.print(" OPTION2        ");
}

void loop() {
  int enter = digitalRead(B2);
  int ld_esq = digitalRead(B1);
  int ld_dir = digitalRead(B3);
  int estadoBotao; 

  // Faz algo com o estado do botão
  if (estadoBotao == HIGH) {
    Serial.println("Botão pressionado!");
    
  }

  delay(100);
  
  
  
  //if (SELECT_MENU == 0 && submenu == 0)
  if (enter == HIGH){
    switch (m_state_level_one) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print(">");
        lcd.setCursor(9, 0);
        lcd.print(" [ENTER]");
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
        lcd.print(" [ENTER]");
        m_state_level_one = 1;
        state_selected = 2;
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(9, 0);
        lcd.print("                ");
        break;
    }
  }

  if (ENTER_MENU == 0) {
    switch (state_selected) {
      case 1:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" OPTION1");
        lcd.setCursor(9, 0);
        lcd.print(">SENSOR1");
        lcd.setCursor(9, 1);
        lcd.print(" EQUIP1");
        submenu = 1;
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" OPTION2");
        lcd.setCursor(9, 0);
        lcd.print(">SENSOR2");
        lcd.setCursor(9, 1);
        lcd.print(" EQUIP2");
        submenu = 1;
        break;
    }
  }

  if (ld_esq == HIGH || ld_dir == HIGH) {
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
        m_state_level_two = 1;
        lcd.setCursor(9, 0);
        lcd.print(" ");
        break;
    }
  }

  if (RETURN_MAIN_MENU == 0 && submenu == 1) {
    //ReturnToDefaultMenu();
  }

  delay(250);  // Necessário para tratar o debounce*/
}
