/*Project: 
      45_UNIR_NEMA17_12VDC_test_code.ino
      Link: https://medium.com/jungletronics/28byj-48-12-v-stepper-motor-test-fbaa972dfea5
   
   Objective:   
      This code allows you to control the NEMA 17 stepper motor in full micro-stepping mode.
      It is the hello world for NEMA motor.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   https://medium.com/jungletronics/drv8825-driver-stepper-motor-24byj48-bb14237f4066        

   Author:      OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                     Arduino R3
                    (https://www.arduino.cc/)
                    Nema 17 Stepper Motor 42-34
                    (https://www.amazon.ca/iMetrx-Creality-Printers-Extruder-Y-Axtruder/dp/B092QXLJHT/ref=pd_lpo_sccl_3/146-5301297-0385118?pd_rd_w=xpwcv&content-id=amzn1.sym.135c60bb-68cb-4d34-ae94-a6f8d634fb42&pf_rd_p=135c60bb-68cb-4d34-ae94-a6f8d634fb42&pf_rd_r=SKD3JHEZWCEP6N7910F8&pd_rd_wg=zM6pX&pd_rd_r=d730d0f7-ea20-4ec2-b036-88783ab81aae&pd_rd_i=B092QXLJHT&th=1)
                    DRV8825 45-V, 2.5-A bipolar stepper motor driver with current regulation and 1/32 microstepping  
                    (https://www.ti.com/product/DRV8825?utm_source=google&utm_medium=cpc&utm_campaign=asc-null-null-GPN_EN-cpc-pf-google-wwe_cons&utm_content=DRV8825&ds_k=DRV8825+Datasheet&DCM=yes&gad_source=1&gclid=CjwKCAiA_OetBhAtEiwAPTeQZ7UEY9qKZbSNji_WYCjNKDLdjfRKbb8m2QQiJ7UeLOVOkT2Q8_WRKBoC-hoQAvD_BwE&gclsrc=aw.ds)
   
   Connections: See Fritzing (Link above)

    Output:    Full Step Mode
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

int ms1Pin   = A0;                          // Stepstick MS0 to Arduino pin A0
int ms2Pin   = A1;                          // Stepstock MS1 to Arduino pin A1
int ms3Pin   = A2;                          // Stepstick MS2 to Arduino pin A2

                                            // defines pins
#define stepPin A3 
#define dirPin  A4 

int numSteps = 200;                         // 360 / 1.8° = 200 steps per revolution
int rotations = 1;                          // Number of rotations of the rotor for each


int delay1  =   700;                        // Delay between coil activations (ms)
int delay2  =   2000; 
 
void setup() {
  pinMode(ms1Pin,          OUTPUT);         // MS1 set to receive Arduino signals
  pinMode(ms2Pin,          OUTPUT);         // MS2 set to receive Arduino signals
  pinMode(ms3Pin,          OUTPUT);         // MS3 set to receive Arduino signals
  
                                            // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  digitalWrite(dirPin,HIGH);                // Enables the motor to move in a particular direction
                                            // Makes 200 pulses for making one full cycle rotation
  digitalWrite(ms1Pin, LOW);
  digitalWrite(ms2Pin, LOW);
  digitalWrite(ms3Pin, LOW);
  for(int x = 0; x < numSteps * 1 * rotations; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(delay1);              // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(delay1); 
  }
  delay(delay2);                            // Two second delay
  
  digitalWrite(dirPin,LOW);                 // Changes the rotations direction
                                            // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < numSteps * 1 * rotations; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(delay1);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(delay1);
  }
  delay(delay2);
}