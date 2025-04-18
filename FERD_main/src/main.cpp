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

// // NodeMCU esp8266 Pins                     Oled display pins
// // GND                                       GND
// // Vin                                       VCC
// // D1                                        SDA
// // D2                                        SCL
// /////////////////////////////////////////////////

// #include <SPI.h>
// #include <Wire.h>
// #include <LoRa.h> // Or include the appropriate library header by sandeep mistry
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define i2c_Address 0x3C //initialize with the I2C addr 0x3C Typically eBay OLED's
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// #define OLED_RESET      -1  // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
// // Define LoRa module pins (adjust as needed)
// #define SS 15  // LoRa module's SPI Slave Select (SS) pin
// #define RST 16  // LoRa module's Reset pin
// #define DI0 11  // LoRa module's Interrupt pin (DIO0)

// void setup() {
//   Serial.begin(115200); // Initialize serial communication for debugging

//   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//   if(!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address)) {
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;); // Don't proceed, loop forever
//   }

//   // Initialize LoRa module
//   LoRa.setPins(SS, RST, DI0); // Set the LoRa module's pins
//   if (!LoRa.begin(915E6)) { // Or your desired frequency (e.g., 433MHz, 868MHz, 915MHz)
//     Serial.println("Starting LoRa failed!");
//     display.clearDisplay();
//     display.setTextSize(2);
//     display.setTextColor(SSD1306_WHITE);
//     display.setCursor(0,0);
//     display.print("Lora init  Failed!");
//     display.display();
//     while (1);
//   }
//   Serial.println("LoRa Initialized OK!");
//     display.clearDisplay();
//     display.setTextSize(2);
//     display.setTextColor(SSD1306_WHITE);
//     display.setCursor(0,0);
//     display.print("Lora init  SUCCESS!");
//     display.display();
// }

// void loop() {
//   // Your LoRa communication code here
// }