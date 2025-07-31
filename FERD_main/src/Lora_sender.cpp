// ///////////////Connections of lora//////////////////
// // NodeMCU esp8266 Pins                     SX1278 Pins
// // GND                                       GND
// // 3.3V                                      VCC
// // D8                                        NSS (chip select)
// // D7                                        MOSI (Master Out Slave In)
// // D6                                        MISO (Master In Slave Out)
// // D5                                        SCK (Serial Clock)
// // D0                                        RST (Reset)
// /////////////////////////////////////////////////

// //include all the libraries
// #include <SPI.h>                // Include the SPI library for SPI communication (LORA module)
// #include <LoRa.h>               // Or include the appropriate library header by sandeep mistry
// #include <Wire.h>               // Include the Wire library for I2C communication
// #include <Adafruit_GFX.h>       // Include the Adafruit GFX library for graphics
// #include <Adafruit_SSD1306.h>   // Include the Adafruit SSD1306 library for OLED display

// // Define LoRa module pins (adjust as needed)
// #define SS 15  // LoRa module's SPI Slave Select (NSS) pin
// #define RST 16  // LoRa module's Reset pin
// //#define DI0 11  // LoRa module's Interrupt pin (DIO0)

// //setup the display
// #define i2c_Address 0x3C //initialize with the I2C addr 0x3C Typically eBay OLED's
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// #define OLED_RESET      -1  // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// #define Button 2 // Button pin to send data


// //Main Setup and initialization
// void setup() {
//   Serial.begin(115200); // Initialize serial communication for debugging
//   Serial.println("LoRa Sender");

//   //pin 2 is used as a button to send data
//   pinMode(Button, INPUT_PULLUP);
  
//   // Display initialization
//   display.begin(SSD1306_SWITCHCAPVCC, i2c_Address);
//   Serial.println("Display Initialized OK!");
//   display.clearDisplay();           // clear the display  

//   // Initialize LoRa module
//   LoRa.setPins(SS, RST); // Set the LoRa module's pins

//   if (!LoRa.begin(433E6)) { // Or your desired frequency (e.g., 433MHz, 868MHz, 915MHz)
//     Serial.println("Starting LoRa failed!");
//     while (1);
//   }
//   Serial.println("LoRa Initialized OK!");
// }

// //Main runs indefinitely
// void loop() {   
//   display.setTextSize(2);          // set text size to 2
//   display.setTextColor(SSD1306_WHITE); // set text color to white
//   display.setCursor(0,0);          // set cursor to top left corner
//   display.print("Press For Help!"); // print "Lora init OK!" on the display
//   display.display();               // update the display

//   if(digitalRead(Button) == LOW){
//     //Show the message on the display
//     display.clearDisplay();           // clear the display
//     display.setTextSize(2);           // set text size to 2
//     display.setTextColor(SSD1306_WHITE); // set text color to white
//     display.setCursor(0,0);           // set cursor to top left corner
//     display.print("Data Sent!");      // print "Lora init OK!" on the display
//     display.display();                // update the display
//     // send packet
//     LoRa.beginPacket();
//     LoRa.print("S ");
//     LoRa.endPacket();
//     delay(1000); // wait for 1 second before sending the next packet
//     display.clearDisplay();           // clear the display
//   }
// }