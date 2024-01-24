/*Project: 
      38_UNIR_pir_sensor_interruption_approuch
      Link: [TODO: link to jungletronics page goes here ]
   
   Objective:          
      This implementation relying on interrupts offers distinct advantages over the previous code(#37), 
      especially in scenarios involving time-sensitive events, such as motion detection. 
      Interrupts empower the microcontroller to swiftly react to changes in the sensor state without 
      the necessity for continuous monitoring within the primary program loop, 
      distinguishing it from conventional polling techniques (#37). 
      This approach enhances efficiency and responsiveness in handling real-time events, making it 
      particularly well-suited for applications where timely detection and response are critical.
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
                Motion ended! lapse time = 3014
                Motion detected!
                Motion ended! lapse time = 5878
                Motion detected!
                Motion ended! lapse time = 10775
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

 * PIR sensor tester w/ interruption
 */
 
const int ledPin = 13;    // choose the pin for the LED
const int inputPin = 2;   // choose the input pin (for PIR sensor)
volatile int pirState = LOW; // we start, assuming no motion detected
volatile int val = 0;      // variable for reading the pin status
unsigned long motionStartTime = 0;  // variable to store the start time of motion
unsigned long motionEndTime = 0;  // variable to store the end time of motion
unsigned long timeLapse = 0;  // variable to store the time lapse between motion and no motion

void setup() {
  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(inputPin, INPUT); // declare sensor as input

  attachInterrupt(digitalPinToInterrupt(inputPin), interrupt_routine, CHANGE);

  Serial.begin(9600);
}

void loop() {
  // Your main loop can be empty or do other tasks.
}

void interrupt_routine() {
  val = digitalRead(inputPin); // read input value

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH); // turn LED ON
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      motionStartTime = millis();  // record the start time of motion
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH) {
      Serial.print("Motion ended! lapse time = ");
      motionEndTime = millis();  // record the end time of motio
      Serial.println(timeLapse = motionEndTime - motionStartTime);
      pirState = LOW;
    }
  }
}
