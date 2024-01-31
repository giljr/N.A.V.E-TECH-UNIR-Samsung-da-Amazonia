/*Project: 
      44_UNIR_28BYJ48_12VDC_test_code.ino
      Link: https://medium.com/jungletronics/eeprom-24lc256-reading-and-writing-arduino-sketch-bdfb6e5a3b13
   
   Objective:   
      This code allows you to control the 28BYJ-48 stepper motor in different
      micro-stepping modes (full step, half step, quarter step, and sixteenth).
      The eighth and thirty-second step modes did not work, so they are commented out.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   https://www.digitaltown.co.uk/components1524LC256EEPROM.php
                Arduino UNO 24LC256 External EEPROM24LC256v1

   Author:      Digital Town
    Edited:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                     Arduino R3
                    (https://www.arduino.cc/)
                    Stepper Motor - 28BYJ-48
                    DRV8825 45-V, 2.5-A bipolar stepper motor driver with current regulation and 1/32 microstepping  
                    (https://www.ti.com/product/DRV8825?utm_source=google&utm_medium=cpc&utm_campaign=asc-null-null-GPN_EN-cpc-pf-google-wwe_cons&utm_content=DRV8825&ds_k=DRV8825+Datasheet&DCM=yes&gad_source=1&gclid=CjwKCAiA_OetBhAtEiwAPTeQZ7UEY9qKZbSNji_WYCjNKDLdjfRKbb8m2QQiJ7UeLOVOkT2Q8_WRKBoC-hoQAvD_BwE&gclsrc=aw.ds)
   
   Connections: See Fritzing
    Output:    
               Full Step Mode
               1/2 Step Mode
               1/4 Step Mode
               1/16 Step Mode
                ....
   Based on:    j3       
                DRV8825 Driver & Stepper Motor 24BYJ48
                Operation & Theory #basicTronics 09
                https://medium.com/jungletronics/drv8825-driver-stepper-motor-24byj48-bb14237f4066

   Date:  31 jan, 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
*/
// 28BYJ48 - 12VDC 
int ms1Pin   = A0;                          // Stepstick MS0 to Arduino digital pin 9
int ms2Pin   = A1;                          // Stepstock MS1 to Arduino digital pin 10
int ms3Pin   = A2;                          // Stepstick MS2 to Arduino digital pin 11

int stepPin  = A3;                          // Stepstick STEP pin to Arduino digital pin 12
int dirPin   = A4;                          // Stepstick DIR pin to Arduino digital  pin 13

int numSteps = 680;//708;                   //720/5.625 degree = 128/2 = 64 //int numSteps = 48;Number of steps in 360 degree rotation
int rotations = 3;                          // Number of rotations of the rotor for each

int delay1  =   2;                          // Delay between coil activations (ms)
int delay2  =   2000;                       // Delay between subsequent rotations
int i;                                      // int to use in for loop

//------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(ms1Pin,          OUTPUT);         // MS1 set to receive Arduino signals
  pinMode(ms2Pin,          OUTPUT);         // MS2 set to receive Arduino signals
  pinMode(ms3Pin,          OUTPUT);         // MS3 set to receive Arduino signals
  pinMode(stepPin,         OUTPUT);         // stepPin set to receive Arduino signals
  pinMode(dirPin,          OUTPUT);         // DIR set to receive Arduino signals
 
}

//------------------------------

void loop() {
  delay(delay2);
   
                                            // 1 step (Full)  M1, M2,M3 Step (low-low-low)  
  Serial.println("Full Step Mode");
  digitalWrite(dirPin, LOW); 
                                            // Rotate stepper rotatations revolutions, using full step method
  digitalWrite(ms1Pin, LOW);
  digitalWrite(ms2Pin, LOW);
  digitalWrite(ms3Pin, LOW);

  for (i = 1; i <= (numSteps * 1 * rotations); ++i) {
    digitalWrite(stepPin, LOW);             // Prepare to take a step
    digitalWrite(stepPin, HIGH) ;           // Take a step
    delay(delay1);                          // Allow some delay between energizing
                                            // the coils to allow stepper rotor time to respond.
  }
  delay(delay2);

                                            // 1/2 Step (half) M1, M2,M3 Step (high-low-low) 
  Serial.println("1/2 Step Mode");   
  digitalWrite(dirPin, HIGH); 
                                            // Rotate stepper rotatations revolutions, using half step method
  digitalWrite(ms1Pin, HIGH);
  digitalWrite(ms2Pin, LOW);
  digitalWrite(ms3Pin, LOW);
   
  for (i = 1; i <= (numSteps * 2 * rotations); ++i) {
    digitalWrite(stepPin, LOW);             // Prepare to take a step
    digitalWrite(stepPin, HIGH) ;           // Take a step
    delay(delay1);                          // Allow some delay between energizing
                                            // the coils to allow stepper rotor time to respond.
  }
  delay(delay2);

                                            // 1/4 Step (qurter) M1, M2,M3 Step (low-high-low) 
  digitalWrite(dirPin, LOW);
  Serial.println("1/4 Step Mode");
                                            // Rotate stepper a rotatations revolutions, using quarter stepping
  digitalWrite(ms1Pin, LOW);
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, LOW);
    
  for (i = 1; i <= (numSteps * 4 * rotations); ++i) {
    digitalWrite(stepPin, LOW);             // Prepare to take a step
    digitalWrite(stepPin, HIGH) ;           // Take a step
    delay(delay1);                          // Allow some delay between energizing
                                            // the coils to allow stepper rotor time to respond.
  }

                                            // Rotate stepper rotations revolution, using microstepping
                                            //  8 steps/step
  //  1/8 Step (eighth) M1, M2,M3 Step (high-high-low)
  // delay(delay2);
  // Serial.println("1/8 Step Mode");
  // digitalWrite(dirPin, HIGH);
  // digitalWrite(ms1Pin, HIGH);
  // digitalWrite(ms2Pin, HIGH);
  // digitalWrite(ms3Pin, LOW);  
    
  // for (i = 1; i <= (numSteps * 8 * rotations); ++i) {
   
  //   delay(delay1);                       // Allow some delay between energizing
  //                                        // the coils to allow stepper rotor time to respond.
  // }

//                                          // Rotate stepper rotations revolution, using microstepping
//                                          //  16 steps/step
  //16 Step
  delay(delay2);
  Serial.println("1/16 Step Mode");
  digitalWrite(dirPin, LOW);

  digitalWrite(ms1Pin, LOW);
  digitalWrite(ms2Pin, LOW);
  digitalWrite(ms3Pin, HIGH);
  
  for (i = 1; i <= numSteps * 16 * rotations; ++i) {
    digitalWrite(stepPin, LOW);             // Prepare to take a step
    digitalWrite(stepPin, HIGH) ;           // Take a step
    delay(delay1);                          // Allow some delay between energizing
                                            // the coils to allow stepper rotor time to respond.
  }

//                                          // Rotate stepper rotations revolution, using microstepping
//                                          //  32 steps/step
 // 32 Step
  // delay(delay2);
  // Serial.println("1/32 Step Mode");
  // digitalWrite(dirPin, HIGH);

  // digitalWrite(ms1Pin, HIGH);
  // digitalWrite(ms2Pin, HIGH);
  // digitalWrite(ms3Pin, HIGH);
  
  // for (i = 1; i <= numSteps * 32 * rotations; ++i) {
  //   digitalWrite(stepPin, LOW);          // Prepare to take a step
  //   digitalWrite(stepPin, HIGH) ;        // Take a step
  //   delay(delay1);                       // Allow some delay between energizing
  //                                        // the coils to allow stepper rotor time to respond.
  //}


}