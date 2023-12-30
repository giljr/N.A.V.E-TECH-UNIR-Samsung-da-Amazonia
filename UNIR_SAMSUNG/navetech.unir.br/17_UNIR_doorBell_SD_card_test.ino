/*
Project:  
      17_UNIR_doorBell_SD_card_test for Seeeduino Stalker v2.3
      DS3231 - Real Time Clock with Digital Temperature sensor on board Seeeduino Stalker v2.1
      Link: https://wiki.seeedstudio.com/Seeeduino_Stalker_v2.3/

   Objective:       
      The code demonstrates basic SD card functionality, including initialization, 
      file and folder creation, listing, and optional removal operations.
      Example use of chdir(), ls(), mkdir(), and  rmdir(). 
      It serves as an example for interacting with an SD card using the SdFat library.
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):

   Authors:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                    DS3231 - Real Time Clock with Digital Temperature sensor on board Seeeduino Stalker v2.1
                    Seeeduino Stalker v2.3
                    (https://wiki.seeedstudio.com/Seeeduino_Stalker_v2.3/#stalker-v23-schematic-online-viewer)
                    (https://www.openhacks.com/uploadsproductos/seeeduino_stalker_v2.pdf)
                    Arduino Uno R3
                    (https://docs.arduino.cc/hardware/uno-rev3 )                   
   
   Software:    Tutorial: https://wiki.seeedstudio.com/Seeeduino_Stalker_v2.3/
                                
  Output:       This sketch is designed to test SD Card in Seeeduino Stalker v2.3

   Connections: 


   Based on:    Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
                Exploring Arduino - Code Listing 11-6: Receiving Arduino
                http://www.exploringarduino.com/content/ch11
   
   Date: 29 dez 2023

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

/*
 * 
 */
#include "SdFat.h"
#include "sdios.h"

                            // SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h,
                            // 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 0
/*
  Change the value of SD_CS_PIN if you are using SPI and
  your hardware does not use the default value, SS.
  Common values are:
  Arduino Ethernet shield: pin 4
  Sparkfun SD shield: pin 8
  Adafruit SD shields and modules: pin 10
*/

                            // SDCARD_SS_PIN is defined for the built-in SD on some boards.
#ifndef SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SS;
#else                       // SDCARD_SS_PIN
                            // Assume built-in SD is used.
const uint8_t SD_CS_PIN = SDCARD_SS_PIN;
#endif                      // SDCARD_SS_PIN

                            // Try max SPI clock for an SD. Reduce SPI_CLOCK if errors occur.
#define SPI_CLOCK SD_SCK_MHZ(50)

                            // Try to select the best SD card configuration.
#if HAS_SDIO_CLASS
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_CLOCK)
#else                       // HAS_SDIO_CLASS
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_CLOCK)
#endif                      // HAS_SDIO_CLASS
//------------------------------------------------------------------------------

#if SD_FAT_TYPE == 0
SdFat sd;
File file;
File root;
#elif SD_FAT_TYPE == 1
SdFat32 sd;
File32 file;
File32 root;
#elif SD_FAT_TYPE == 2
SdExFat sd;
ExFile file;
ExFile root;
#elif SD_FAT_TYPE == 3
SdFs sd;
FsFile file;
FsFile root;
#endif                      // SD_FAT_TYPE

                            // Create a Serial output stream.
ArduinoOutStream cout(Serial);
//------------------------------------------------------------------------------
                            // Store error strings in flash to save RAM.
#define error(s) sd.errorHalt(&Serial, F(s))
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

                            // Wait for USB Serial
  while (!Serial) {
    yield();
  }
  delay(1000);
  cout << F("Type any character to start\n");
  while (!Serial.available()) {
    yield();
  }

                            // Initialize the SD card.
  if (!sd.begin(SD_CONFIG)) {
    sd.initErrorHalt(&Serial);
  }
  if (sd.exists("Folder1") || sd.exists("Folder1/file1.txt") ||
      sd.exists("Folder1/File2.txt")) {
    error("Please remove existing Folder1, file1.txt, and File2.txt");
  }

  int rootFileCount = 0;
  if (!root.open("/")) {
    error("open root");
  }
  while (file.openNext(&root, O_RDONLY)) {
    if (!file.isHidden()) {
      rootFileCount++;
    }
    file.close();
    if (rootFileCount > 10) {
      error("Too many files in root. Please use an empty SD.");
    }
  }
  if (rootFileCount) {
    cout << F("\nPlease use an empty SD for best results.\n\n");
    delay(1000);
  }
  // Create a new folder.
  if (!sd.mkdir("Folder1")) {
    error("Create Folder1 failed");
  }
  cout << F("Created Folder1\n");

                            // Create a file in Folder1 using a path.
  if (!file.open("Folder1/file1.txt", O_WRONLY | O_CREAT)) {
    error("create Folder1/file1.txt failed");
  }
  file.close();
  cout << F("Created Folder1/file1.txt\n");

                            // Change volume working directory to Folder1.
  if (!sd.chdir("Folder1")) {
    error("chdir failed for Folder1.\n");
  }
  cout << F("chdir to Folder1\n");

                            // Create File2.txt in current directory.
  if (!file.open("File2.txt", O_WRONLY | O_CREAT)) {
    error("create File2.txt failed");
  }
  file.close();
  cout << F("Created File2.txt in current directory\n");

  cout << F("\nList of files on the SD.\n");
  sd.ls("/", LS_R);

                          // Remove files from current directory.
  // if (!sd.remove("file1.txt") || !sd.remove("File2.txt")) {
  //   error("remove failed");
  // }
  // cout << F("\nfile1.txt and File2.txt removed.\n");

                          // Change current directory to root.
  if (!sd.chdir()) {
    error("chdir to root failed.\n");
  }

  cout << F("\nList of files on the SD.\n");
  sd.ls(LS_R);

                          // Remove Folder1.
//   if (!sd.rmdir("Folder1")) {
//     error("rmdir for Folder1 failed\n");
//   }
//   cout << F("\nFolder1 removed.\n");
//   cout << F("\nList of files on the SD.\n");
//   sd.ls(LS_R);
//   cout << F("Done!\n");
}
//------------------------------------------------------------------------------
                          // Nothing happens in loop.
void loop() {}
