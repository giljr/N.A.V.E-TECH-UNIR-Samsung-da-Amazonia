/* Project: 
      12 UNIR AutoWaterBot_Ultimate_Version_v0.2 
      Link:    
      
   Objective: 
      This code, developed by Jose Antonio, aims to evolve into a real irrigation project. This marks the first prototype.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                 (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   Authors:     MARQUES, Ana p., RIBEIRO, Antônio J.; OLIVEIRA, Gilberto O.; FREIRE, Angelina.
   
   Hardware:    Development Boards:
                   Arduino UNO:    Microcontroller board based on the ATmega328P (datasheet)                   
   
   Software:    Tinkercad
                     Tinkercad is a free, easy-to-use app for 3D design, electronics, and coding.
                                
   Connections:
   The COMPONENTS is connected to the microcontroller as follows:
                    Arduino UNO Rev.3 board:                
                    Microcontroller      PART               
                    ===============      ===              
                          A0             SOIL MOISTURE SENSOR                 
                          A1             LU-5-R                 
                          A2             LU-5-R                
                          D2             BUZZER  
                          A3             Photoresistor  
                           

   The LCD's Is connected to the microcontroller as follows: 
                    Arduino UNO Rev.3 board:                
                    Microcontroller      LCD               
                    ===============      ===                                               
                          A4             SDA
                          A5             SCL      

   Presentation: https://www.canva.com/design/DAF1mXAJyeE/Iv0X65QcByHk04a267UFZA/edit?utm_content=DAF1mXAJyeE&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton
   Date:   20 Dez 2023
*/
// Incluindo bibliotecas necessárias

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Definindo pinos
const int sensorPin = A0;
const int alertPin = 2;
const int relayPowerPin = A3;
const int relayIrrigationPin = A2;
const int lightSensorPin = A1; 

// Constantes
const int moistureThreshold = 500;
const int lightThreshold = 500;  
const int alertDuration = 1000; 

const int i2cAddr = 0x20;  
LiquidCrystal_I2C lcd(i2cAddr, 16, 2); 

void setup() {  
  // Definindo pinos para o LCD I2C
  Wire.begin();
  lcd.begin(16, 2);
  lcd.print("Navetec Group 03");
  lcd.setCursor(0, 1);
  lcd.print("****************");
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
  Serial.begin(9600);
  
  pinMode(alertPin, OUTPUT);
  pinMode(relayPowerPin, OUTPUT);
  pinMode(relayIrrigationPin, OUTPUT);
}

void loop() {
  int soilMoisture = analogRead(sensorPin);
  int lightSensorValue = analogRead(lightSensorPin);

  
  lcd.setCursor(0, 0);
  lcd.print("Umidade do Solo: ");
  lcd.setCursor(0, 1);
  lcd.print(soilMoisture);
  delay(2000);
  lcd.clear();

  
  lcd.setCursor(0, 0);
  lcd.print("Claridade do Ambi: ");
  lcd.setCursor(0, 1);
  lcd.print(lightSensorValue);
  delay(2000);
  lcd.clear();

  if (soilMoisture < moistureThreshold && lightSensorValue < lightThreshold) 
  	{
    // Solo seco e há luz solar
    digitalWrite(relayIrrigationPin, HIGH);
    digitalWrite(relayPowerPin, HIGH);
    lcd.setCursor(0, 0);
  	lcd.print("Irrigando...");
    delay(6000);
    lcd.clear();
    delay(alertDuration);
    digitalWrite(relayIrrigationPin, LOW);
  	}
  else if(soilMoisture < moistureThreshold && lightSensorValue > lightThreshold) 
  	{
    digitalWrite(relayIrrigationPin, HIGH);
    digitalWrite(relayPowerPin, LOW); 
    lcd.setCursor(0, 0);
  	lcd.print("Irrigando...");
    delay(6000);
    lcd.clear();
    delay(alertDuration);
    digitalWrite(relayIrrigationPin, LOW); 
  	}

  delay(3000);
}
