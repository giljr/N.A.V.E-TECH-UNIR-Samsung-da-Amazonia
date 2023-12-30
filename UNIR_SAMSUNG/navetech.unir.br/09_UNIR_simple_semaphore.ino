/* Project: 
      09 - UNIR - Simple Semaphore
      Link: https://www.tinkercad.com/things/0fnAGGkzqpq-06-unir-single-dice
   
      The code defines a button pin (BUT) and an enumeration (but_state) for button states: active and disable.
	  It initializes the button state variable (buttonState) to disable.
	  In the setup function, it configures pin modes and attaches an interrupt to the button pin using the rising edge trigger.
      The main loop checks if the button is pressed and updates the button state accordingly, controlling the behavior of three output pins (5, 6, and 7) accordingly.
      An interrupt function toggles the button state when triggered by a rising edge on the button pin, allowing for a responsive state change without polling in the main loop.
      It was developed during the N.A.V.E TECH UNIR Samsung Porto Velho Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Marcelo Ribeiro 
      Professor in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
              
   Authors:     BARBOSA, Assis; FERNANDES, Breno D.; OLIVEIRA, Gilberto O.
   
   Hardware:    Development Boards:
                   Arduino UNO:    Microcontroller board based on the ATmega328P (datasheet)                   
   
   Software:    Tinkercad : It is a free, easy-to-use app for 3D design, electronics, and coding.
                 LIB: Adafruit_LEDBackpack.h (7-Segment board - HT16K33)    
                      (https://learn.adafruit.com/adafruit-led-backpack/downloads)
                                
   Connections:
   The LCD is connected to the microcontroller as follows:
                    Arduino UNO Rev.3 board:                
                    Microcontroller      LED               
                    ===============      ===              
                          D5            Green  
                          D6            Yellow 
                          D7            Red 
 

   The Momentary Button is connected to the microcontroller as follows: 
                    Arduino UNO Rev.3 board:                
                    Microcontroller      LCD               
                    ===============      ===      
                           D2            1k Ohms

   Date:   12 Dez 2023
*/
#define BUT 2

enum but_state { active, disable };

but_state buttonState = disable;

void setup() {
  pinMode(BUT, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUT), interrupt, RISING); // Corrected the interrupt declaration
}

void loop() {
  if (digitalRead(BUT) == HIGH) {
    buttonState = active;
  }

  if (buttonState == disable) {
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
  } else if (buttonState == active) {
    digitalWrite(7, LOW);
    digitalWrite(5, HIGH);
    delay(800);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    delay(800);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    delay(800);
  }
}

void interrupt() {
  buttonState = (buttonState == disable) ? active : disable; // Toggle buttonState
}
