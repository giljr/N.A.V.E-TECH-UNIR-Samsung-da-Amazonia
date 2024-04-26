/*Project: 
      50_UNIR_Final_Project.ino
      Compact, Informative, and Visually Appealing 
      Weather Monitoring Solution (WMS) v 1.0 
      Link: [TODO: LINK TO JUNGLETRONICS GOES HERE]
   
   Objective: 
      This project utilizes an Arduino with sensors and an LCD display to create a weather monitoring system.
      It integrates a DHT11 sensor for temperature and humidity readings, displaying them on the LCD.
      Additionally, a TSL2561 sensor measures visible light intensity, presented in kilolux (kL) on the LCD.
      The system includes an analog rain sensor, indicating whether it's raining or dry on the display.
      A grid-based custom LCD interface enhances visual representation of weather data.
      The system uses I2C communication protocol for interfacing with the LCD and sensors.
      LED indicators provide real-time status feedback for rain detection.
      Wire library is employed for communication with the TSL2561 sensor.
      The project aims to offer a compact, informative, and visually appealing weather monitoring solution.
      With proper calibration and adjustments, it can be tailored for various indoor or outdoor applications.
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
                    TSL2561 sensor  
                    LCD 16x2
                    DHT11 sensor
                    YL_83 rain sensor
   
    Based on:   j3 Libraries
                https://github.com/giljr/N.A.V.E-TECH-UNIR-Samsung-da-Amazonia
   
   Date:  26 Apr, 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
*/
#include <LCD-I2C.h>
#include <DHT11.h>
#include <Wire.h>

DHT11 dht11(2);

#define Addr 0x39

LCD_I2C lcd(0x27, 16, 2);

uint8_t solar[8] = {0b11111, 0b10101, 0b11111, 0b10101, 0b11111, 0b10101, 0b11111, 0b00000};
uint8_t battery[8] = {0b01110, 0b11011, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b11111};
uint8_t termometer[8] = {0b00100, 0b01010, 0b01010, 0b01110, 0b01110, 0b11111, 0b11111, 0b01110};
uint8_t humiditySymbol[8] = {0b00100, 0b01010, 0b01010, 0b01110, 0b00100, 0b00000, 0b00100, 0b00000};
uint8_t current[8] = {0b00001, 0b00010, 0b00100, 0b01000, 0b11000, 0b00110, 0b00100, 0b01000};
uint8_t charge[8] = {0b01010, 0b11111, 0b10001, 0b10001, 0b10001, 0b01110, 0b00100, 0b00100};
uint8_t alarm[8] = {0b00000, 0b00100, 0b01110, 0b01110, 0b01110, 0b11111, 0b00000, 0b00100};
uint8_t full_battery[8] = {0b01110, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};

int rainPin = A0;
int greenLED = 6;
int redLED = 7;
bool raining = false;
int thresholdValue = 700;

void setup() {
    Wire.begin();
    pinMode(rainPin, INPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(redLED, OUTPUT);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    // Serial.begin(9600);

    Wire.beginTransmission(Addr);
    Wire.write(0x00 | 0x80);
    Wire.write(0x03);
    Wire.endTransmission();

    Wire.beginTransmission(Addr);
    Wire.write(0x01 | 0x80);
    Wire.write(0x02);
    Wire.endTransmission();
    delay(300);

    lcd.begin();
    lcd.display();
    lcd.backlight();

    lcd.createChar(0, solar);
    lcd.createChar(1, battery);
    lcd.createChar(2, termometer);
    lcd.createChar(3, humiditySymbol);
    lcd.createChar(4, current);
    lcd.createChar(5, charge);
    lcd.createChar(6, alarm);
    lcd.createChar(7, full_battery);
}

void loop() {
    unsigned int data[4];
    for (int i = 0; i < 4; i++) {
        Wire.beginTransmission(Addr);
        Wire.write((140 + i));
        Wire.endTransmission();

        Wire.requestFrom(Addr, 1);

        if (Wire.available() == 1) {
            data[i] = Wire.read();
        }
        delay(200);
    }

    double ch0 = ((data[1] & 0xFF) * 256) + (data[0] & 0xFF);
    double ch1 = ((data[3] & 0xFF) * 256) + (data[2] & 0xFF);
    // Serial.print("Visible Value :");
    // Serial.println(ch0 - ch1);

    int sensorValue = analogRead(rainPin);
    if (sensorValue < thresholdValue) {
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, HIGH);
        raining = true;
    } else {
        digitalWrite(greenLED, HIGH);
        digitalWrite(redLED, LOW);
        raining = false;
    }
    delay(500);

    int temperature = 0;
    int humidityValue = 0;
    int visibleLight = (int)(ch0 - ch1) / 1000; // Convert to L or kL
    int visibleLightDecimal = ((int)(ch0 - ch1) % 1000) / 100; // Get the decimal part

    int result = dht11.readTemperatureHumidity(temperature, humidityValue);

    lcd.clear();

    char temperatureStr[4];
    char humidityStr[4];
    itoa(temperature, temperatureStr, 10);
    itoa(humidityValue, humidityStr, 10);

    printMosaic(0, 0, 2, temperatureStr, "*C");
    printMosaic(8, 0, 3, humidityStr, "%");
    printMosaic(0, 1, 0, "", ""); // Print empty space instead of "10"
    lcd.setCursor(2, 2);
    lcd.print(visibleLight); // Print the integer part of visible light
    lcd.print(".");
    lcd.print(visibleLightDecimal); // Print the decimal part of visible light
    lcd.print("kL"); // Print unit

    lcd.setCursor(8, 1);
    if (raining) {
        lcd.print("Rain");
    } else {
        lcd.print("Dry");
    }
    delay(6000);
}

void printMosaic(int column, int row, uint8_t symbol, char* value, char* unit) {
    lcd.setCursor(column, row);
    lcd.write(symbol);
    lcd.setCursor(column + 2, row);
    lcd.print(value);
    lcd.print(unit);
}
