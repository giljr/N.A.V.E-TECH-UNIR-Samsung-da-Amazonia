/*Project: 
      33_UNIR_TwoWayCom_HardwareBased_RX_nRF24L_arduino
      Link: [TODO: link to jungletronics page goes here ]
   
   Objective:       
      Demonstrates two-way communication using hardware features of the radio.  Using native hardware for two-way
      communication is much faster than the software-based approach shown in the 'TwoWayCom_SoftwareBased' example,
      but it is a little more complex and has some limitations.  

      The hardware-based approach requires the idea of a primary transmitter and primary receiver.  Data flows from
      the transmitter to receiver via normal data packets, while data moves from the receiver to the transmitter via
      acknowledgement *data* packets.  Receivers send normal acknowledgement packets to let transmitters know they
      received data, and this acknowledgement feature is utilized to provide data back to the transmitter.  Due to this
      implementation, the receiver cannot initiate two-way communication, it must be started by the transmitter.

      Another limitation is the receiver cannot process a data packet and then choose what data to include within the
      acknowledgement packet that is immediately sent back.  Instead, the receiver must be pre-loaded with acknowledgement
      data prior to receiving a data packet from the transmitter.  This can be worked around though and an approach is
      demonstrated in this example.  When the transmitter wants data from the receiver, the transmitter will send a
      'BeginGetData' packet.  When the receiver processes this packet, it will load itself with an acknowledgement data
      packet.  The transmitter then sends an 'EndGetData' packet in order to finally receive the data from the receiver.

      If you need the ability to initiate communication from either radio and do not require the higher-speed data
      transfer that is possible using acknowledgement data packets, see the software-based two-way communication example.
      
      It was developed during the N.A.V.E TECH UNIR Samsung Eletrônica da Amazônia LTDA
      In Porto Velho - RO - Brazil, Course from November 2023 to April 2024. 
      The project was supervised by Professor Dr. Ciro José Egoavil Montero 
      (https://www.linkedin.com/in/ciro-j-egoavil-210b7a44/?originalSubdomain=br), 
      an Associate Professor III in Electrical Engineering at the Federal University of Rondônia (UNIR).
      
   homePage :   (https://navetech.unir.br/)  EDITAL Nº 01/2023/NAVE-Tech-RO/UNIR
                (https://ciroegoavil.unir.br/homepage) Engenharia Elétrica da Fundação Universidade Federal de Rondônia (UNIR):
   
   Authors:     OLIVEIRA, Gilberto Jr (J3)
   
   Hardware:    Development Boards:
                    Arduino Uno R3
                    (https://docs.arduino.cc/hardware/uno-rev3 )                   
   
   Software:    Arduino IDE 2.2.1
                  
   Connections: 
               Arduino - Radio SPI - Wire Color
                   7   -  CE       - Black
                   8   -  CSN      - White
                  13   -  SCK      - Orange
                  11   -  MOSI     - Yellow
                  12   -  MISO     - Blue
                   3   -  IRQ      - Red

   output:      The radio receives an integer that increments by one. 

   Based on: 
          dparson
          NRFLite Arduino nRF24L01 library
          https://youtu.be/tWEgvS7Sj-8?si=zdPP_o1gHMPNGU54
          https://github.com/dparson55/NRFLite/tree/master

   Date: 14 jan 2024
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
 
*/

#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 0;
const static uint8_t DESTINATION_RADIO_ID = 1;
const static uint8_t PIN_RADIO_CE = 7;
const static uint8_t PIN_RADIO_CSN = 8;

enum RadioPacketType
{
    AcknowledgementData, // Produced by the primary receiver and provided to the transmitter via an acknowledgement data packet.
    Heartbeat,    // Sent by the primary transmitter.
    BeginGetData, // Sent by the primary transmitter to tell the receiver it should load itself with an acknowledgement data packet.
    EndGetData    // Sent by the primary transmitter to receive the acknowledgement data packet from the receiver.
};

struct RadioPacket
{
    RadioPacketType PacketType;
    uint8_t FromRadioId;
    uint32_t OnTimeMillis;
};

NRFLite _radio;

void setup()
{
    Serial.begin(115200);

    if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
    {
        Serial.println("Cannot communicate with radio");
        while (1); // Wait here forever.
    }
}

void loop()
{
    while (_radio.hasData())
    {
        RadioPacket radioData;
        _radio.readData(&radioData);

        if (radioData.PacketType == Heartbeat)
        {
            String msg = "Heartbeat from ";
            msg += radioData.FromRadioId;
            msg += ", ";
            msg += radioData.OnTimeMillis;
            msg += " ms";
            Serial.println(msg);
        }
        else if (radioData.PacketType == BeginGetData)
        {
            Serial.println("Received data request, adding ACK data packet");

            RadioPacket ackData;
            ackData.PacketType = AcknowledgementData;
            ackData.FromRadioId = RADIO_ID;
            ackData.OnTimeMillis = millis();

            // Add the data to send back to the transmitter into the radio.
            // The next packet we receive will be acknowledged with this data.
            _radio.addAckData(&ackData, sizeof(ackData));
        }
        else if (radioData.PacketType == EndGetData)
        {
            // The transmitter hopefully received the acknowledgement data packet at this point.
        }
    }
}