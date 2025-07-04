//this code takes a signal from a LoRa module and repeats it to another LoRa module

#include <SPI.h>                // Include the SPI library for SPI communication
#include <LoRa.h>               // Or include the appropriate library header by sandeep mistry
#include <Wire.h>               // Include the Wire library for I2C communication
 
// Define LoRa module pins (adjust as needed)
#define SS 15  // LoRa module's SPI Slave Select (SS) pin
#define RST 16  // LoRa module's Reset pin
#define DI0 11 // LoRa module's Interrupt pin (DIO0)

#define LED 5 // LED pin for indicating received data


void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  Serial.println("LoRa Receiver");

  pinMode(LED, OUTPUT);
  
  // Initialize LoRa module
  LoRa.setPins(SS, RST, DI0); // Set the LoRa module's pins
  
  if (!LoRa.begin(433E6)) { // Or ayour desired frequency (e.g., 433MHz, 868MHz, 915MHz) 433 for AI-Thinker RA02
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initialized OK!");

}

void loop() {
  // try to parse packet
  digitalWrite(LED, LOW); // Turn on LED to indicate data received
  int packetSize = LoRa.parsePacket(); // returns 0 if no packet available else returns size of packet
  if (packetSize) {                     //// if packetSize > 0, it means we have a packet
    // received a packet
    digitalWrite(LED, HIGH); // Turn on LED to indicate data received
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {          // while there is data available in the packet
      Serial.print((char)LoRa.read());  // read the data byte by byte
      //store the data in a variable
      String receivedData = LoRa.readString(); // read the data as a string
    }

    delay(2000); 
    //repeat the data
    LoRa.beginPacket();
    LoRa.print(" Data From repeater: 1");
    //LoRa.print(counter);
    LoRa.endPacket();
  }
}