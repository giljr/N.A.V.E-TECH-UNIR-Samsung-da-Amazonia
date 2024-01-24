/*Project: 
      37_UNIR_pir_sensor_polling_approuch
      Link: [TODO: link to jungletronics page goes here ]
   
   Objective:           
      This first code utilizes a polling approach, where the detection of motion relies on repeatedly checking 
      the sensor state within a loop and waiting for changes. This code employs a PIR sensor to identify motion 
      and adjusts an LED accordingly. Messages indicating the initiation and cessation of motion are printed to 
      the serial monitor. The pirState variable is employed to track the motion detection state, 
      preventing the generation of redundant messages.
      In contrast, the subsequent code (#38) leverages interrupts for a more efficient and responsive operation in 
      comparison to the initial polling code. Interrupts enable the microcontroller to promptly respond to alterations
      in the sensor state without the need for continuous checks within the main loop.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):
   
   Authors:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                    ESP8266 - ESP-01
                    (https://www.espressif.com/)
                    Arduino Uno R3
                    (https://docs.arduino.cc/hardware/uno-rev3 )                   
   
   Software:    Arduino IDE 2.2.1

   Output: 
                Motion detected!
                Motion ended!
                Motion detected!
                Motion ended!
                ....
                  
   Connections: 
                  Arduino  - ESP 8266                       
                   1(TX)   -  TX0     
                   -       -  CHP0     
                   -       -  RST    
                   -       -  VCC  
                   -       -  GND
                   -       -  GP2
                   -       -  GP0
                   0(RX)   -  RX0 
                   
   output:      Please see this file [TODO].txt 
   Based on: 
          LowPowerDemo.ino from unofficial board support URLs Library Manager:
          http://arduino.esp8266.com/stable/package_esp8266com_index.json
   Date:  20 jan, 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
 
*/
/*
 * PIR sensor tester
 */
 
int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}