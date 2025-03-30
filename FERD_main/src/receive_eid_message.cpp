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


#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2
#define NUMFLAKES     7 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   20
#define LOGO_WIDTH    20
static const unsigned char PROGMEM logo_bmp[] =
{   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x18, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x08, 0x0f, 
	0x00, 0x08, 0x0f, 0x00, 0x06, 0x3e, 0x00, 0x07, 0xfc, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};


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
  display.print("Waiting!"); // print "Lora init OK!" on the display
  display.display();               // update the display
}


  void testdrawrect(void) {
    display.clearDisplay();
  
    for(int16_t i=0; i<display.height()/2; i+=2) {
      display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
      display.display(); // Update screen with each newly-drawn rectangle
      delay(1);
    }
  
    delay(500);
  }
  
  void testfillrect(void) {
  
    for(int16_t i=0; i<display.height()/2; i+=3) {
      // The INVERSE color is used so rectangles alternate white/black
      display.fillRect(i, i, display.width()-i*2, display.height()-i*2, SSD1306_INVERSE);
      display.display(); // Update screen with each newly-drawn rectangle
      delay(1);
    }
  
    delay(1000);
  }

  void testfillcircle(void) {
    display.clearDisplay();
  
    for(int16_t i=0; i<max(display.width(),display.height())/2; i+=3) {
      // The INVERSE color is used so circles alternate white/black
      display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
      display.display(); // Update screen with each newly-drawn circle
      delay(1);
    }
  
    delay(100);
  }

  void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
    int8_t f, icons[NUMFLAKES][3];
  
    // Initialize 'snowflake' positions
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
      icons[f][YPOS]   = -LOGO_HEIGHT;
      icons[f][DELTAY] = random(1, 6);
      Serial.print(F("x: "));
      Serial.print(icons[f][XPOS], DEC);
      Serial.print(F(" y: "));
      Serial.print(icons[f][YPOS], DEC);
      Serial.print(F(" dy: "));
      Serial.println(icons[f][DELTAY], DEC);
    }
  
    for(;;) { // Loop forever...
      display.clearDisplay(); // Clear the display buffer
      display.setTextSize(2);          // set text size to 2
      display.setTextColor(SSD1306_WHITE); // set text color to white
      display.setCursor(40,10);          // set cursor to top left corner
      display.print("EID ");     // printa "Received: " on the display
      display.setCursor(15,30);         // set cursor to second line
      display.print("MUBARAK!");     // print the received data on the display
      //display.display();               // update the display
  
      // Draw each snowflake:
      for(f=0; f< NUMFLAKES; f++) {
        display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
      }
  
      display.display(); // Show the display buffer on the screen
      delay(150);        // Pause for 1/10 second
  
      // Then update coordinates of each flake...
      for(f=0; f< NUMFLAKES; f++) {
        icons[f][YPOS] += icons[f][DELTAY];
        // If snowflake is off the bottom of the screen...
        if (icons[f][YPOS] >= display.height()) {
          // Reinitialize to a random position, just off the top
          icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
          icons[f][YPOS]   = -LOGO_HEIGHT;
          icons[f][DELTAY] = random(1, 6);
        }
      }
    }
  }




void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket(); // returns 0 if no packet available else returns size of packet
  if (packetSize) {                     //// if packetSize > 0, it means we have a packet
    delay(3000);
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {          // while there is data available in the packet
      //display the data on the OLED display
      display.clearDisplay();           // clear the display
      display.setTextSize(2);          // set text size to 2
      display.setTextColor(SSD1306_WHITE); // set text color to white
      display.setCursor(0,0);          // set cursor to top left corner
      display.print("Data ");     // printa "Received: " on the display
      display.setCursor(0,20);         // set cursor to second line
      display.print("Received!");     // print the received data on the display
      display.setCursor(0,40);         // set cursor to third line
      display.print("Loading...");     // print the received data on the display
      display.display();               // update the display
      delay(2500);
      

      testdrawrect();      // Draw rectangles (outlines)

      testfillrect();      // Draw rectangles (filled)

      testfillcircle();    // Draw circles (filled)

      display.clearDisplay();           // clear the display
      display.setTextSize(2);          // set text size to 2
      display.setTextColor(SSD1306_WHITE); // set text color to white
      display.setCursor(40,10);          // set cursor to top left corner
      display.print("EID ");     // printa "Received: " on the display
      display.setCursor(15,30);         // set cursor to second line
      display.print("MUBARAK!");     // print the received data on the display
      display.display();               // update the display
      
        // Invert and restore display, pausing in-between
        display.invertDisplay(true);
        delay(500);
        display.invertDisplay(false);
        delay(500);
        // Invert and restore display, pausing in-between
        display.invertDisplay(true);
        delay(500);
        display.invertDisplay(false);
        delay(500);
        testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");      // print the RSSI (Received Signal Strength Indicator) of the packet
    Serial.println(LoRa.packetRssi());
  }
}

