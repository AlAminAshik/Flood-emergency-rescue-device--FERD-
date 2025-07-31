//this code takes a signal from a LoRa module and repeats it to another LoRa module

#include <SPI.h>                // Include the SPI library for SPI communication
#include <LoRa.h>               // Or include the appropriate library header by sandeep mistry
#include <Wire.h>               // Include the Wire library for I2C communication
 
// Define LoRa module pins (adjust as needed)
#define SS 15  // LoRa module's SPI Slave Select (SS) pin
#define RST 16  // LoRa module's Reset pin
#define DI0 11 // LoRa module's Interrupt pin (DIO0)

#define LED 4 // LED pin for indicating received data

int delayTime = 400; // Delay time for repeating data (100ms for RPT1, 400ms for RPT2, 600ms for RPT3)

String receivedData; // Variable to store received data

//main setup and initialization
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

  // Wait for a packet
  int packetSize = LoRa.parsePacket(); // returns 0 if no packet available else returns size of packet
  if (packetSize > 0) {                // if packetSize > 0, it means we have a packet
    // received a packet
    digitalWrite(LED, HIGH); // Turn on LED to indicate data received
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {          // while there is data available in the packet
      //store the data in a variable
      receivedData = LoRa.readString(); // copy and read the data as a string
    }

    digitalWrite(LED, LOW); // Turn off LED after reading data

    // Print the received data "S " is sent by the sender
    if(receivedData == "S "){
      Serial.println("Repeater 2: Received 'S' command, repeating data.");
      delay(delayTime); // Delay to ensure the LED is visible (200ms for RPT1, 400ms for RPT2, 600ms for RPT3)
      digitalWrite(LED, HIGH); // Turn on LED to indicate data is being repeated
        //repeat the data
        LoRa.beginPacket();
        LoRa.print("RPT2 " + String(LoRa.packetRssi())); // Send the received data with RPT2 and RSSI
        LoRa.endPacket();
    } else {
      Serial.print(receivedData); // print the received data
    }
  }
}


