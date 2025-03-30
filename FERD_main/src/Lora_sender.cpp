// ///////////////Connections of lora//////////////////
// // NodeMCU esp8266 Pins                     SX1278 Pins
// // GND                                       GND
// // 3.3V                                      VCC
// // D8                                        NSS
// // D7                                        MOSI
// // D6                                        MISO
// // D5                                        SCK
// // D0                                        RST
// // D2                                        DIO0
// /////////////////////////////////////////////////


// #include <SPI.h>
// #include <LoRa.h> // Or include the appropriate library header by sandeep mistry

// int counter = 0;
 
// // Define LoRa module pins (adjust as needed)
// #define SS 15  // LoRa module's SPI Slave Select (SS) pin
// #define RST 16  // LoRa module's Reset pin
// #define DI0 11  // LoRa module's Interrupt pin (DIO0)

// void setup() {
//   Serial.begin(115200); // Initialize serial communication for debugging
//   Serial.println("LoRa Sender");
  
//   // Initialize LoRa module
//   LoRa.setPins(SS, RST, DI0); // Set the LoRa module's pins
  
//   if (!LoRa.begin(915E6)) { // Or ayour desired frequency (e.g., 433MHz, 868MHz, 915MHz)
//     Serial.println("Starting LoRa failed!");
//     while (1);
//   }
//   Serial.println("LoRa Initialized OK!");
// }

// void loop() {
//   Serial.print("Sending packet: ");
//   Serial.println(counter);

//   // send packet
//   LoRa.beginPacket();
//   LoRa.print("hello ");
//   LoRa.print(counter);
//   LoRa.endPacket();

//   counter++;

//   delay(5000);
// }