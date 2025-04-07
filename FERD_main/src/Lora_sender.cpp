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


// #include <SPI.h>                // Include the SPI library for SPI communication
// #include <LoRa.h>               // Or include the appropriate library header by sandeep mistry
// #include <Wire.h>               // Include the Wire library for I2C communication
// #include <Adafruit_GFX.h>       // Include the Adafruit GFX library for graphics
// #include <Adafruit_SSD1306.h>   // Include the Adafruit SSD1306 library for OLED display

// int counter = 0;
 
// // Define LoRa module pins (adjust as needed)
// #define SS 15  // LoRa module's SPI Slave Select (SS) pin
// #define RST 16  // LoRa module's Reset pin
// #define DI0 11  // LoRa module's Interrupt pin (DIO0)

// //setup the display
// #define i2c_Address 0x3C //initialize with the I2C addr 0x3C Typically eBay OLED's
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// #define OLED_RESET      -1  // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// void setup() {
//   Serial.begin(115200); // Initialize serial communication for debugging
//   Serial.println("LoRa Sender");

//   //pin 2 is used as a button to send data
//   pinMode(2, INPUT_PULLUP);
  
//     // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//     if(!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address)) {
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;); // Don't proceed, loop forever
//     }
//     Serial.println("Display Initialized OK!");

//   // Initialize LoRa module
//   LoRa.setPins(SS, RST, DI0); // Set the LoRa module's pins
  
//   if (!LoRa.begin(915E6)) { // Or ayour desired frequency (e.g., 433MHz, 868MHz, 915MHz)
//     Serial.println("Starting LoRa failed!");
//     while (1);
//   }
//   Serial.println("LoRa Initialized OK!");
//   display.clearDisplay();           // clear the display    
// }


// void loop() {
//   display.setTextSize(2);          // set text size to 2
//   display.setTextColor(SSD1306_WHITE); // set text color to white
//   display.setCursor(0,0);          // set cursor to top left corner
//   display.print("Press the Button!"); // print "Lora init OK!" on the display
//   display.display();               // update the display

//   if(digitalRead(2) == LOW){
//     display.clearDisplay();           // clear the display
//     display.setTextSize(2);           // set text size to 2
//     display.setTextColor(SSD1306_WHITE); // set text color to white
//     display.setCursor(0,0);           // set cursor to top left corner
//     display.print("Data Sent!");      // print "Lora init OK!" on the display
//     display.display();                // update the display
//     // send packet
//     LoRa.beginPacket();
//     LoRa.print(" Sending Data: ");
//     LoRa.print(counter);
//     LoRa.endPacket();
//     counter++;
//     delay(1000); // wait for 1 second before sending the next packet
//     display.clearDisplay();           // clear the display
//   }
// }