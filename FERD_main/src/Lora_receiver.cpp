///////////////Connections of lora//////////////////
// NodeMCU esp8266 Pins                     SX1278 Pins
// GND                                       GND
// 3.3V                                      VCC
// D8                                        NSS
// D7                                        MOSI
// D6                                        MISO
// D5                                        SCK
// D0                                        RST
// D2                                        DIO0 (not necessary)k
/////////////////////////////////////////////////


#include <SPI.h>                // Include the SPI library for SPI communication
#include <LoRa.h>               // Or include the appropriate library header by sandeep mistry
#include <Wire.h>               // Include the Wire library for I2C communication
#include <Adafruit_GFX.h>       // Include the Adafruit GFX library for graphics
#include <Adafruit_SSD1306.h>   // Include the Adafruit SSD1306 library for OLED display
 
// Define LoRa module pins (adjust as needed)
#define SS 15  // LoRa module's SPI Slave Select (SS) pin
#define RST 16  // LoRa module's Reset pin
#define DI0 11 // LoRa module's Interrupt pin (DIO0)

//setup the display
#define i2c_Address 0x3C //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET      -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String receivedData; // Variable to store received data
int RSSI = 0; // Variable to store the RSSI value of the received packet
int RPT_ONE_RSSI = 0; // int to store the data for each report
int RPT_TWO_RSSI = 0; // int to store the data for each report
int RPT_THREE_RSSI = 0; // int to store the data for each report

unsigned long previousMillis = 0; // Variable to store the time of the last update

String names[3] = {};


String getResult(int RPT1, int RPT2, int RPT3) {  //feeding the RSSI values
  int values[3] = {RPT1, RPT2, RPT3};
  String names[3] = {"R1", "R2", "R3"};     // Names for each report

  // Simple bubble sort
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {
      if (values[i] < values[j]) {  // Sort in descending order
        // Swap values
        int tempVal = values[i];
        values[i] = values[j];
        values[j] = tempVal;

        // Swap names
        String tempName = names[i];
        names[i] = names[j];
        names[j] = tempName;
      }
    }
  }
  return names[0] + "> " + names[1] + "> " + names[2];
}


void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  Serial.println("LoRa Receiver");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address)) {
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();           // clear the display
  Serial.println("Display Initialized OK!");
  
  // Initialize LoRa module
  LoRa.setPins(SS, RST, DI0); // Set the LoRa module's pins
  
  if (!LoRa.begin(433E6)) { // Or ayour desired frequency (e.g., 433MHz, 868MHz, 915MHz) 433 for AI-Thinker RA02
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initialized OK!");
}


void loop() {
  display.setTextSize(2);          // set text size to 2
  display.setTextColor(SSD1306_WHITE); // set text color to white
  display.setCursor(0,0);          // set cursor to top left corner
  display.print("Waiting!"); // print "Waiting!" on the display
  display.display();               // update the display

  // try to parse packet
  int packetSize = LoRa.parsePacket(); // returns 0 if no packet available else returns size of packet
  if (packetSize > 0) {                     // if packetSize > 0, it means we have a packet
    RSSI = LoRa.packetRssi(); // get the RSSI of the packet

    // read packet
    while (LoRa.available()) {
      //store the data in a variable
      receivedData = LoRa.readString(); // read the data as a string
    }
    //extract the string part from the received data
    String txtData = receivedData.substring(0, receivedData.indexOf(' ')); // get the string part of the data
    int RSSIData = receivedData.substring(receivedData.indexOf(' ') + 1).toInt(); // get the numeric part of the data and convert is to integer

    if(receivedData.length() > 0) { // if receivedData is not empty

        if(txtData == "S") { // if the received data is "S"
            Serial.println("Received 'S' command, ignoring.");
        }
        else if(txtData == "RPT1") { // if the received data is "RPT1"
            RPT_ONE_RSSI = RSSIData; // set RPT_ONE_RSSI to the RSSI of the packet
            Serial.println("Received RPT1 command. RSSI: " + String(RSSIData));
        }
        else if(txtData == "RPT2") { // if the received data is "RPT2"
            RPT_TWO_RSSI = RSSIData; // set RPT_TWO_RSSI to the RSSI of the packet
            Serial.println("Received RPT2 command. RSSI: " + String(RSSIData));
        }
        else if(txtData == "RPT3") { // if the received data is "RPT3"
            RPT_THREE_RSSI = RSSIData; // set RPT_THREE_RSSI to the RSSI of the packet
            Serial.println("Received RPT3 command. RSSI: " + String(RSSIData));
        }
        else { // if the received data is not "S", "RPT1", "RPT2" or "RPT3"
            Serial.print("Received data: ");
            Serial.println(receivedData); // print the received data
        }
    }
  }

  if(RPT_ONE_RSSI < 0 && RPT_TWO_RSSI < 0 && RPT_THREE_RSSI < 0) { // if all of the RPT RSSI values are less than 0
    display.clearDisplay();           // clear the display
    display.setTextSize(2);          // set text size to 2
    display.setCursor(0,0);          // set cursor to top left corner
    display.println("HELP!!");
    //display.println("No RPT RSSI values received!"); // print "No RPT RSSI values received!" on the display
    display.println(" ");
    String result = getResult(RPT_ONE_RSSI, RPT_TWO_RSSI, RPT_THREE_RSSI); // get the result of the RPT RSSI values
    Serial.println("Result: " + result); // print the result on the serial monitor
    display.println(result); // print the result on the display
    display.display();               // update the display
    delay(5000); // wait for 2 seconds before clearing the display
    display.clearDisplay();           // clear the display
  }

  unsigned long currentMillis = millis(); // get the current time in milliseconds
  if(currentMillis - previousMillis > 2000) { // if more than 2 seconds have passed since the last update
    previousMillis = currentMillis; // reset the previousMillis to the currentMillis
    RPT_ONE_RSSI = 0; // reset the RPT RSSI values to 0
    RPT_TWO_RSSI = 0; // reset the RPT RSSI values to
    RPT_THREE_RSSI = 0; // reset the RPT RSSI values to 0
  }

}
