/* Project: 
      15_UNIR_AutoWaterBot_Ultimate_Version_v0.3
      Link: https://www.tinkercad.com/things/ehEDYXSSMlV-12-unir-autowaterbotultimateversionv02

   Objective: 
      
      From TimeNTP_ESP32WiFi.ino - Setting Real NTP TimeStamp
      Example showing time sync to NTP time source
      Time Lib: https://github.com/probonopd/ESP8266HueEmulator/issues/71
      This sketch uses the ESP32WiFi library
      This sketch uses the Time library https://github.com/PaulStoffregen/Time
      (The project is designed to function as an automatic irrigation system)
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
                                
   Output:   TimeNTP Example
             Connecting to EagleWireless
            ...IP number assigned by DHCP is 192.168.0.105
            Starting UDP
            Local port: waiting for sync
            Transmit NTP Request


   Connections:
   The Heltec_ESP32 is connected to the computer w/ USB Cable


   Based on:  lxyzn from HelTec AutoMation, ChengDu, China
              成都惠利特自动化科技有限公司
              https://heltec.org
   
   Date:    24 dez 2023
*/

#include <TimeLib.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char ssid[] = "EagleWireless";  //  your network SSID (name)
const char pass[] = "6LR614122";       // your network password

// NTP Servers:
static const char ntpServerName[] = "pool.ntp.org";

const int timeZone = -4;     // Amazon Standard Time Manaus - State of Amazonas (GMT-4) or Brazil: East UTC-4

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);

void setup()
{
  Serial.begin(115200);
  while (!Serial) ; // Needed for Leonardo only
  delay(250);
  Serial.println("TimeNTP Example");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("IP number assigned by DHCP is ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
//  Serial.println(Udp.localPort());
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
}

time_t prevDisplay = 0; // when the digital clock was displayed

void loop()
{
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();
    }
  }
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(".");
  Serial.print(month());
  Serial.print(".");
  Serial.print(year());
  Serial.println();
}

void printDigits(int digits)
{
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
