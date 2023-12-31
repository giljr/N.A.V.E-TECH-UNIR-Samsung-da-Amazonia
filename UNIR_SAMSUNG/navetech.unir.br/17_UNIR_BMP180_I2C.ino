/* Project: 
      17_UNIR_BMP180_I2C simple test.
      Link: https://www.tinkercad.com/things/ehEDYXSSMlV-12-unir-autowaterbotultimateversionv02

   Objective:       
      This sketch simply outputs the result of a BMP180 Sensor. Using Heltec_ESP32 Board.
      shows how to use the BMP180MI library with the sensor connected using I2C.
      Please observe the results in the Serial terminal.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage : (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                 (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   Authors:     MARQUES, Ana p., RIBEIRO, Antônio J.; OLIVEIRA, Gilberto O.; FREIRE, Angelina
   
   Hardware:    Development Boards:
                    HelTec WiFi Lora Automation(TM) ESP32(V2) Series Dev boards OLED                   
   
   Software:    Arduino & Heltec Libs
                     Expressif:    https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
                                   https://dl.espressif.com/dl/esp-idf/?idf=4.4
                     Heltec_ESP32: https://github.com/HelTecAutomation/Heltec_ESP32/tree/master
                                   https://github.com/HelTecAutomation/Heltec_ESP32
                     For more informations, please vist www.heltec.cn or mail to support@heltec.cn
                                
  Output:     16:15:46.293 -> Temperature: 30.00 degC
              16:15:46.370 -> Pressure: 100.30 kPa
              16:15:47.509 -> Temperature: 30.00 degC
              16:15:47.602 -> Pressure: 100.31 kPa

   Connections: 
              The Heltec_ESP32 is connected to the computer w/ USB Cable
              BMP180 is connected on PIN GPIO21 - SDA
                                     PIN GPIO22 - SCL
                                     GND        - GND
                                     VIN        - 3V3

              https://www.ktron.in/product/1k-ohms-3296-multiturn-trimpot-potentiometer/

   Based on:  Copyright (c) 2018 Gregor Christandl
              https://heltec.org
   
   Date:    25 dez 2023
*/

#include <Arduino.h>
#include <Wire.h>

#include <BMP180I2C.h>

#define I2C_ADDRESS 0x77

//create an BMP180 object using the I2C interface
BMP180I2C bmp180(I2C_ADDRESS);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);

	//wait for serial connection to open (only necessary on some boards)
	while (!Serial);

	Wire.begin();

	//begin() initializes the interface, checks the sensor ID and reads the calibration parameters.  
	if (!bmp180.begin())
	{
		Serial.println("begin() failed. check your BMP180 Interface and I2C Address.");
		while (1);
	}

	//reset sensor to default parameters.
	bmp180.resetToDefaults();

	//enable ultra high resolution mode for pressure measurements
	bmp180.setSamplingMode(BMP180MI::MODE_UHR);
}

void loop() {
  // put your main code here, to run repeatedly:

	delay(1000);

	//start a temperature measurement
	if (!bmp180.measureTemperature())
	{
		Serial.println("could not start temperature measurement, is a measurement already running?");
		return;
	}

	//wait for the measurement to finish. proceed as soon as hasValue() returned true. 
	do
	{
		delay(100);
	} while (!bmp180.hasValue());

	Serial.print("Temperature: "); 
	Serial.print(bmp180.getTemperature()); 
	Serial.println(" degC");

	//start a pressure measurement. pressure measurements depend on temperature measurement, you should only start a pressure 
	//measurement immediately after a temperature measurement. 
	if (!bmp180.measurePressure())
	{
		Serial.println("could not start perssure measurement, is a measurement already running?");
		return;
	}

	//wait for the measurement to finish. proceed as soon as hasValue() returned true. 
	do
	{
		delay(100);
	} while (!bmp180.hasValue());

	Serial.print("Pressure: "); 
	Serial.print(bmp180.getPressure()/1000);
	Serial.println(" kPa");
}
