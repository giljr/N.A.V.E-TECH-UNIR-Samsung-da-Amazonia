/* Project: 
      16_UNIR_ADC_Read_Voltage via GPIO13 simple test.
      Link: https://www.tinkercad.com/things/ehEDYXSSMlV-12-unir-autowaterbotultimateversionv02

   Objective:       
      This sketch simply outputs the result of a potentiometer. Using Heltec_ESP32 Board.
      Please use a screw to give multiple turns to the device and observe the results in the Serial terminal.
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
                                
  Output:     16:54:38.297 -> 992
              16:54:38.297 -> 997
              16:54:38.297 -> 997
              16:54:38.297 -> 993
              16:54:38.297 -> 996
              16:54:38.297 -> 996
              ...
              16:55:17.533 -> 1023
              16:55:17.533 -> 1022
              16:55:17.533 -> 1021
              16:55:17.533 -> 1023
              16:55:17.533 -> 1019
   Connections: 
              The Heltec_ESP32 is connected to the computer w/ USB Cable
              1K Ohms 3296 Multiturn Trimpot Potentiometer on ANALOG PIN GPIO13
              https://www.ktron.in/product/1k-ohms-3296-multiturn-trimpot-potentiometer/

   Based on:  by Aaron.Lee from HelTec AutoMation, ChengDu, China
              成都惠利特自动化科技有限公司
              https://heltec.org
   
   Date:    25 dez 2023
*/

void setup() {
  Serial.begin(115200);
  analogReadResolution(10);             // Sets the sample bits and read resolution, default is 9-bit (0 - 1023), range is 9 - 12 bits
  analogSetWidth(10);                   // Sets the sample bits and read resolution, 10-bit gives an ADC range of 0-1023 (like Arduino)
  /*
  analogReadResolution(12);             // Sets the sample bits and read resolution, default is 12-bit (0 - 4095), range is 9 - 12 bits
  analogSetWidth(12);                   // Sets the sample bits and read resolution, default is 12-bit (0 - 4095), range is 9 - 12 bits
                                        //  9-bit gives an ADC range of 0-511
                                        // 10-bit gives an ADC range of 0-1023
                                        // 11-bit gives an ADC range of 0-2047
                                        // 12-bit gives an ADC range of 0-4095
  analogSetCycles(8);                   // Set number of cycles per sample, default is 8 and provides an optimal result, range is 1 - 255
  analogSetSamples(1);                  // Set number of samples in the range, default is 1, it has an effect on sensitivity has been multiplied
  analogSetClockDiv(1);                 // Set the divider for the ADC clock, default is 1, range is 1 - 255
  analogSetAttenuation(ADC_11db);       // Sets the input attenuation for ALL ADC inputs, default is ADC_11db, range is ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
  analogSetPinAttenuation(VP,ADC_11db); // Sets the input attenuation, default is ADC_11db, range is ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
                                        // ADC_0db provides no attenuation so IN/OUT = 1 / 1 an input of 3 volts remains at 3 volts before ADC measurement
                                        // ADC_2_5db provides an attenuation so that IN/OUT = 1 / 1.34 an input of 3 volts is reduced to 2.238 volts before ADC measurement
                                        // ADC_6db provides an attenuation so that IN/OUT = 1 / 2 an input of 3 volts is reduced to 1.500 volts before ADC measurement
                                        // ADC_11db provides an attenuation so that IN/OUT = 1 / 3.6 an input of 3 volts is reduced to 0.833 volts before ADC measurement
  adcAttachPin(VP);                     // Attach a pin to ADC (also clears any other analog mode that could be on), returns TRUE/FALSE result 
  adcStart(VP);                         // Starts an ADC conversion on attached pin's bus
  adcBusy(VP);                          // Check if conversion on the pin's ADC bus is currently running, returns TRUE/FALSE result 
  adcEnd(VP);                           // Get the result of the conversion (will wait if it have not finished), returns 16-bit integer result
  */
  adcAttachPin(13);
  analogSetClockDiv(255); // 1338mS
}

void loop() {
  //  int timer  = micros();
   Serial.println(analogRead(13));
  //  Serial.print("  ");
  //  Serial.println(micros() - timer);
   
}

//See more APIs about ADC here: https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/master/esp32/cores/esp32/esp32-hal-adc.h

