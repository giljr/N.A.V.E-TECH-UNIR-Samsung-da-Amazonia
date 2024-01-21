/*Project: 
      36_UNIR_esp8266_low_power_demo_simplified
      Link: [TODO: link to jungletronics page goes here ]
   
   Objective:    
      This code is incredibly straightforward and uncomplicated.
      It will initiate a WiFi connection (test1) and transition the ESP8266 into Deep Sleep Mode (test2).
      Perform a reset (GND on pin RST) to restore its functionality.
      It is designed for an ESP8266 microcontroller using the Arduino framework. 
      It demonstrates low-power modes, specifically Deep Sleep mode, 
      and includes functionality to establish a WiFi connection.  
      Let's delves into the typical implementation of low-power modes on the ESP8266.              
      Feel free to use this sketch as a reference for comparing various professional power-saving strategies.
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
#include <ESP8266WiFi.h>
#include <PolledTimeout.h>
#include <include/WiFiState.h>              // WiFiState structure details

#define DEBUG                               // prints WiFi connection info to serial, uncomment if you want WiFi messages
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

#define WAKE_UP_PIN 0                       // D3/GPIO0, can also force a serial flash upload with RESET
                                            // you can use any GPIO for WAKE_UP_PIN except for D0/GPIO16 as it doesn't support interrupts

                                            // uncomment one of the two lines below for your LED connection (optional)
                                            // #define LED   // D1/GPIO5 external LED for modules with built-in LEDs so it doesn't add amperage
#define LED 2                               // D4/GPIO2 LED for ESP-01,07 modules; D4 is LED_BUILTIN on most other modules
                                            // you can use LED_BUILTIN, but it adds to the measured amperage by 0.3mA to 6mA.

ADC_MODE(ADC_VCC);                          // allows you to monitor the internal VCC level; it varies with WiFi load
                                            // don't connect anything to the analog input pin(s)!

                                            // enter your WiFi configuration below
const char* AP_SSID = "EagleWireless";      // your router's SSID here
const char* AP_PASS = "6LR614122";          // your router's password here
IPAddress staticIP(0, 0, 0, 0);             // parameters below are for your static IP address, if used
IPAddress gateway(0, 0, 0, 0);
IPAddress subnet(0, 0, 0, 0);
IPAddress dns1(0, 0, 0, 0);
IPAddress dns2(0, 0, 0, 0);
uint32_t timeout = 30E3;                    // 30 second timeout on the WiFi connection

//#define TESTPOINT                         //  used to track the timing of several test cycles (optional)
#ifdef TESTPOINT
#define testPointPin 2                      // D2/GPIO4, you can use any pin that supports interrupts
#define testPoint_HIGH digitalWrite(testPointPin, HIGH)
#define testPoint_LOW digitalWrite(testPointPin, LOW)
#else
#define testPoint_HIGH
#define testPoint_LOW
#endif


uint32_t resetCount = 0;                    // keeps track of the number of Deep Sleep tests / resets

const uint32_t blinkDelay = 100;                           // fast blink rate for the LED when waiting for the user
esp8266::polledTimeout::periodicMs blinkLED(blinkDelay);   // LED blink delay without delay()
esp8266::polledTimeout::oneShotMs altDelay(blinkDelay);    // tight loop to simulate user code
// esp8266::polledTimeout::oneShotMs wifiTimeout(timeout); // 30 second timeout on WiFi connection
                                                           // use fully qualified type and avoid importing all ::esp8266 namespace to the global namespace
void wakeupCallback();
void setup();
void loop() ;
void runTest1();
void runTest2();
void runTest3();  
void resetTests();
void waitPushbutton(bool, unsigned int);
void readVoltage();
void initWiFi();

void wakeupCallback() {                     // unlike ISRs, you can do a print() from a callback function
  testPoint_LOW;                            // testPoint tracks latency from WAKE_UP_PIN LOW to testPoint LOW
  // printMillis();                         // show time difference across sleep; millis is wrong as the CPU eventually stops
  Serial.println(F("Woke from Light Sleep - this is the callback"));
}

void setup() {
#ifdef TESTPOINT
  pinMode(testPointPin, OUTPUT);            // test point for Light Sleep and Deep Sleep tests
  testPoint_LOW;                            // Deep Sleep reset doesn't clear GPIOs, testPoint LOW shows boot time
#endif
  pinMode(LED, OUTPUT);                     // activity and status indicator
  digitalWrite(LED, LOW);                   // turn on the LED
  pinMode(WAKE_UP_PIN, INPUT_PULLUP);       // polled to advance tests, interrupt for Forced Light Sleep
  Serial.begin(115200);
  Serial.println();
  Serial.print(F("\nReset reason = "));
  String resetCause = ESP.getResetReason();
  Serial.println(resetCause);
  resetCount = 0;
  if ((resetCause == "External System") || (resetCause == "Power on")) { Serial.println(F("I'm awake and starting the Low Power tests")); }

}                                           // end of setup()

void loop() {
  if (resetCount == 0) {                    // if first loop() since power on or external reset
    runTest1();
    runTest2();
  }
  
}                                           // end of loop()


void runTest1() {
  Serial.println(F("\n1nd test - WiFi Connection Establishment - an over simplification method!"));
  Serial.println(F("connecting WiFi, please wait until the LED blinks"));
  initWiFi();
  if (WiFi.localIP()) {                     // won't go into Automatic Sleep without an active WiFi connection
    Serial.println(F("The amperage will drop in 7 seconds."));
    readVoltage();                          // read internal VCC
    Serial.println(F("press the switch to continue"));
    waitPushbutton(true, 90);               /* This is using a special feature: below 100 mS blink delay,
                                               the LED blink delay is padding 100 mS time with 'program cycles' to fill the 100 mS.
                                               At 90 mS delay, 90% of the blink time is delay(), and 10% is 'your program running'.
                                               Below 90% you'll see a difference in the average amperage: less delay() = more amperage.
                                               At 100 mS and above it's essentially all delay() time.  On an oscilloscope you'll see the
                                               time between beacons at > 67 mA more often with less delay() percentage. You can change
                                               the '90' mS to other values to see the effect it has on Automatic Modem Sleep. */
  } else {
    Serial.println(F("no WiFi connection, test skipped"));
  }
}

void runTest2() {
  Serial.println(F("\n2th test - Enter In Deep Sleep Mode, reset and wake with RF_DEFAULT."));
  Serial.println(F("The ESP8266 will enter Deep Sleep Mode. \nUse the RST pin to wake it with RF_DEFAULT in just 10 seconds."));

  readVoltage();                            // read internal VCC
  Serial.println(F("press the switch to continue"));
  while (!digitalRead(WAKE_UP_PIN)) {       // wait for them to release the switch from the previous test
    delay(10);
  }
  delay(50);                                // debounce time for the switch, pushbutton released
  waitPushbutton(false, blinkDelay);        // set true if you want to see Automatic Modem Sleep
  digitalWrite(LED, LOW);                   // turn the LED on, at least briefly

  Serial.println(F("going into Deep Sleep now..."));
  printMillis();                            // show time difference across sleep
  testPoint_HIGH;                           // testPoint set HIGH to track Deep Sleep period, cleared at startup()
  ESP.deepSleep(10E6, WAKE_RF_DEFAULT);     // good night!  D0 fires a reset in 10 seconds...
                                            // if you do ESP.deepSleep(0, mode); it needs a RESET to come out of sleep (RTC is disconnected)
                                            // maximum timed Deep Sleep interval ~ 3 to 4 hours depending on the RTC timer, see the README
                                            // the 2 uA GPIO amperage during Deep Sleep can't drive the LED so it's not lit now, although
                                            // depending on the LED used, you might see it very dimly lit in a dark room during this test
  Serial.println(F("What... I'm not asleep?!?"));  // it will never get here
}

void waitPushbutton(bool usesDelay, unsigned int delayTime) {  // loop until they press the switch
                                                               // note: 2 different modes, as 3 of the power saving modes need a delay() to activate fully
  if (!usesDelay) {                         // quick interception of pushbutton press, no delay() used
    blinkLED.reset(delayTime);
    while (digitalRead(WAKE_UP_PIN)) {      // wait for a pushbutton press
      if (blinkLED) {
        digitalWrite(LED, !digitalRead(LED));                  // toggle the activity LED
      }
      yield();                                                 // this would be a good place for ArduinoOTA.handle();
    }
  } else {                                  // long delay() for the 3 modes that need it, but it misses quick switch presses
    while (digitalRead(WAKE_UP_PIN)) {      // wait for a pushbutton press
      digitalWrite(LED, !digitalRead(LED));  // toggle the activity LED
      delay(delayTime);                      // another good place for ArduinoOTA.handle();
      if (delayTime < 100) {
        altDelay.reset(100 - delayTime);    // pad the time < 100 mS with some real CPU cycles
        while (!altDelay) {                 // this simulates 'your program running', not delay() time
        }
      }
    }
  }
  delay(50);                                // debounce time for the switch, pushbutton pressed
  while (!digitalRead(WAKE_UP_PIN)) {       // now wait for them to release the pushbutton
    delay(10);
  }
  delay(50);                                // debounce time for the switch, pushbutton released
}

void readVoltage() {                        // read internal VCC
  float volts = ESP.getVcc();
  Serial.printf("The internal VCC reads %1.2f volts\n", volts / 1000);
}

void printMillis() {
  Serial.print(F("millis() = "));           // show that millis() isn't correct across most Sleep modes
  Serial.println(millis());
  Serial.flush();                           // needs a Serial.flush() else it may not print the whole message before sleeping
}

void initWiFi() {
  digitalWrite(LED, LOW);                   // give a visual indication that we're alive but busy with WiFi
  uint32_t wifiBegin = millis();            // how long does it take to connect

  WiFi.persistent(false);                   // don't store the connection each time to save wear on the flash
  WiFi.mode(WIFI_STA);
  WiFi.setOutputPower(10);                  // reduce RF output power, increase if it won't connect
  WiFi.config(staticIP, gateway, subnet);   // if using static IP, enter parameters at the top
  WiFi.begin(AP_SSID, AP_PASS);

  Serial.print(F("connecting to WiFi "));
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);                             // wait for 500 milliseconds for the WiFi connection
    Serial.print(".");
  }

  Serial.println();
  Serial.println(F("WiFi connected"));

  uint32_t wifiEnd = millis();
  Serial.print(F("WiFi connection established in "));
  Serial.print(wifiEnd - wifiBegin);
  Serial.println(F(" milliseconds"));
                                            // Use this data to configure your static IP address for faster connection.
  DEBUG_PRINT(F("WiFi Gateway IP: "));
  DEBUG_PRINTLN(WiFi.gatewayIP());
  DEBUG_PRINT(F("my IP address: "));
  DEBUG_PRINTLN(WiFi.localIP());
  DEBUG_PRINT(F("my Subnet mask: "));
  DEBUG_PRINTLN(WiFi.subnetMask());
  DEBUG_PRINT(F("my dns1: "));
  DEBUG_PRINTLN(WiFi.dnsIP());
  DEBUG_PRINT(F("my dns2: "));
  DEBUG_PRINTLN(WiFi.dnsIP(1));

}



