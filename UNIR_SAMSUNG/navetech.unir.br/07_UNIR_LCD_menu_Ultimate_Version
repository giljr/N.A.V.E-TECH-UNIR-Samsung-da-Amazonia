/* Project: 
      05 UNIR - LCD menu Ultimate Version
      Link: https://www.tinkercad.com/things/gL5unE1WIcH-copy-of-05-unir-lcd-menu-ultimate-version
   
   Objective: 
      This project explains how to create a three-level menu and control an RGB LED :).
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                 (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   Authors:     MARQUES, Ana p., RIBEIRO, Antônio J.; OLIVEIRA, Gilberto O.
   
   Hardware:    Development Boards:
                   Arduino UNO:    Microcontroller board based on the ATmega328P (datasheet)                   
   
   Software:    Tinkercad
                     Tinkercad is a free, easy-to-use app for 3D design, electronics, and coding.
                                
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

   The RGB's Star is connected to the microcontroller as follows: 
                    Arduino UNO Rev.3 board:                
                    Microcontroller      LCD               
                    ===============      ===      
                          ~D9            RGB (red)
                          ~D10           RGB (green)
                          ~D11           RGB (blue)     
   Presented 
   www.canva.com: https://www.canva.com/design/DAF1mXAJyeE/Iv0X65QcByHk04a267UFZA/edit?utm_content=DAF1mXAJyeE&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton
   Date:   6 Dez 2023
*/
#include <LiquidCrystal.h>

#define B1 A1
#define B2 A2
#define B3 A3
#define B4 A4

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // Defina os pinos corretos para o seu LCD


int m_state_level_one = 1;
int m_state_level_two = 1;
int state_selected = 0;
int submenu = 0;
int x = 0, y = 0;

void setup() {
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
  Serial.begin(9600);

  // splash init 5 seconds delay
  lcd.begin(16, 2);  // Ajuste o número de colunas e linhas do seu LCD
  lcd.print("Navetec Group 03");
  lcd.setCursor(0, 1);
  lcd.print("****************");
  delay(2000);
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
  int STOP = digitalRead(B4);
  // Pin definitions for LEDs
  const int redPin = 9;    // Replace with your actual pin numbers
  const int greenPin = 11;  // Replace with your actual pin numbers
  const int bluePin = 10;   // Replace with your actual pin numbers

  // Set the LED pins as OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
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
        submenu = 1;
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" AUTOMAT");
        submenu = 1;
        for (int i = 0; i < 4; i++) {
          lcd.setCursor(9, 0);
          lcd.print(">   RED");
          digitalWrite(redPin, HIGH);   // Turn on RED LED
          delay(1000);
          digitalWrite(redPin, LOW);    // Turn off RED LED

          lcd.setCursor(9, 0);
          lcd.print("> GREEN");
          digitalWrite(greenPin, HIGH); // Turn on GREEN LED
          delay(1000);
          digitalWrite(greenPin, LOW);  // Turn off GREEN LED

          lcd.setCursor(9, 0);
          lcd.print(">  BLUE");
          digitalWrite(bluePin, HIGH);  // Turn on BLUE LED
          delay(1000);
          digitalWrite(bluePin, LOW);   // Turn off BLUE LED
        }
        break;
    }
  }
  if (STOP == HIGH) {
    if (m_state_level_two == 1){digitalWrite(greenPin, LOW);} 
    if (m_state_level_two == 3){digitalWrite(bluePin, LOW);}
    if (m_state_level_two == 2){digitalWrite(redPin, LOW);}
    
  }

  if (SELECT_MENU == HIGH && submenu == 1) {
    switch (m_state_level_two) {
      case 1:
      	if (m_state_level_two == 1){digitalWrite(redPin, LOW);}
      	lcd.setCursor(9, 1);
      	lcd.print("> GREEN");
      	m_state_level_two = 3;
      	lcd.setCursor(9, 0);
        lcd.print("    RED");
        digitalWrite(greenPin, HIGH);   // Turn on RED LED
        //delay(1000); 	
      	break;
      case 2:
      	if (m_state_level_two == 2){digitalWrite(bluePin, LOW);}
        m_state_level_two = 1;
      	lcd.setCursor(9, 0);
      	lcd.print(">   RED");
      	lcd.setCursor(9, 1);
        lcd.print("  GREEN");
        digitalWrite(redPin, HIGH);   // Turn on RED LED
        //delay(1000); 
        break;
      case 3:
      	if (m_state_level_two == 3){digitalWrite(greenPin, LOW);} 
        m_state_level_two = 2;
      	lcd.setCursor(9, 0);
      	lcd.print("  GREEN");
      	lcd.setCursor(9, 1);
        lcd.print(">  BLUE");
      	digitalWrite(bluePin, HIGH);   // Turn on RED LED
        //delay(1000);
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
    submenu = 0;  // Defina submenu de volta para 0 para indicar que está no menu principal
    m_state_level_one = 1;  // Reinicia o estado do primeiro nível do menu
    m_state_level_two = 1;  // Reinicia o estado do segundo nível do menu
    state_selected = 0;     // Reinicia o estado selecionado
  }

  delay(250);  // Necessário para tratar o debounce
}

