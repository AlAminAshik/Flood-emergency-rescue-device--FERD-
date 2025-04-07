///////////////Connections of lora//////////////////
// NodeMCU esp8266 Pins                     SX1278 Pins
// GND                                       GND
// 3.3V                                      VCC
// D8                                        NSS
// D7                                        MOSI
// D6                                        MISO
// D5                                        SCK
// D0                                        RST
// D2                                        DIO0
/////////////////////////////////////////////////


#include <SPI.h>                // Include the SPI library for SPI communication
#include <LoRa.h>               // Or include the appropriate library header by sandeep mistry
#include <Wire.h>               // Include the Wire library for I2C communication
#include <Adafruit_GFX.h>       // Include the Adafruit GFX library for graphics
#include <Adafruit_SSD1306.h>   // Include the Adafruit SSD1306 library for OLED display

int counter = 0;
 
// Define LoRa module pins (adjust as needed)
#define SS 15  // LoRa module's SPI Slave Select (SS) pin
#define RST 16  // LoRa module's Reset pin
#define DI0 11  // LoRa module's Interrupt pin (DIO0)

//setup the display
#define i2c_Address 0x3C //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET      -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  Serial.println("LoRa Receiver");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address)) {
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); // Don't proceed, loop forever
  }
  Serial.println("Display Initialized OK!");
  
  // Initialize LoRa module
  LoRa.setPins(SS, RST, DI0); // Set the LoRa module's pins
  
  if (!LoRa.begin(915E6)) { // Or ayour desired frequency (e.g., 433MHz, 868MHz, 915MHz)
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initialized OK!");

  display.clearDisplay();           // clear the display
  display.setTextSize(2);          // set text size to 2
  display.setTextColor(SSD1306_WHITE); // set text color to white
  display.setCursor(0,0);          // set cursor to top left corner
  display.print("Lora init SUCCESS!"); // print "Lora init OK!" on the display
  display.display();               // update the display
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket(); // returns 0 if no packet available else returns size of packet
  if (packetSize) {                     //// if packetSize > 0, it means we have a packet
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {          // while there is data available in the packet
      Serial.print((char)LoRa.read());  // read the data byte by byte
      //store the data in a variable
      String receivedData = LoRa.readString(); // read the data as a string
      //display the data on the OLED display
      display.clearDisplay();           // clear the display
      display.setTextSize(2);          // set text size to 2
      display.setTextColor(SSD1306_WHITE); // set text color to white
      display.setCursor(0,0);          // set cursor to top left corner
      display.print("Received: ");     // printa "Received: " on the display
      display.setCursor(0,20);         // set cursor to second line
      display.print(receivedData);     // print the received data on the display
      display.display();               // update the display
    }
  }
}