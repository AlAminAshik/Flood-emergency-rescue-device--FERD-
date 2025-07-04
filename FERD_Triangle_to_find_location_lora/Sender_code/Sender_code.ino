#include <LoRa.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>       // Include the Adafruit GFX library for graphics
#include <Adafruit_SSD1306.h>   // Include the Adafruit SSD1306 library for OLED display

#define ss 15
#define rst 16
#define dio0 11


//setup the display
#define i2c_Address 0x3C //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET      -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() 
{
  Serial.begin(115200); 
  Serial.println("LoRa Sender");
  
  //pin 2 is used as a button to send data
  pinMode(2, INPUT_PULLUP);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address)) {
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); // Don't proceed, loop forever
  }
  Serial.println("Display Initialized OK!");

  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
  Serial.println("LoRa Started");
  display.clearDisplay();           // clear the display
}

void loop() 
{
  Blynk.run();
  String str1="",str2="";
  int packetSize = LoRa.parsePacket(),i=0,len;
  if (packetSize) 
  {
    Serial.print("Received packet ");
    while (LoRa.available()) 
    {
      str1=str1+((char)LoRa.read()); 
    }
    Serial.println(str1);
    len=str1.length();
    //We can print only 15 characters in a single line. 
    //If there are more than 15 characters, we print them on next line.
    if(len-15 > 0)
    {
      str2=str1.substring(15,len);      
      str1=str1.substring(0,14);
    }
    lcd.clear();  
    lcd.print(0,0,str1);
    lcd.print(0,1,str2);
   }
}