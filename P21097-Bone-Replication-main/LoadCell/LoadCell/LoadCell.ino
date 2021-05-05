/*
 Most scales require that there be no weight on the scale during power on. This sketch shows how to pre-load tare values
 so that you don't have to clear the scale between power cycles. This is good if you have something on the scale 
 all the time and need to reset the Arduino and not need to tare the scale.
 
 The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons.

-------------------------WIRING-------------------------------------         
HX711 pins -> Load Cell                                             |
 +EXCITATION -> RED                                                 |
 -EXCITATION -> BLK                                                 |
 +SIGNAL     -> GTN                                                 |
 -SIGNAL     -> WHT                                                 |
                                                                    |
Arduino pins -> HX711                                               |
 10 -> DOUT (PURPLE)                                                 |
 11 -> HX711 CLK (YELLOW)                                           |
 5V -> VCC (RED)                                                    |
 GND -> GND (BLACK)                                                 |
                                                                    |
The HX711 board will be powered by the Arduino Shield 5V power bus. |
BE SURE TO CHECK ALL PIN CONNECTIONS BEFORE CONNECTING ARDUINO BOARD!
'VERIFY' AND 'UPLOAD' PROGRAM. USE SERIAL MONITOR TO CHECK OUTPUT   |
ONCE PROGRAM IS COMPILED AND UPLOADED, CHANGE PORT TO UNUSED PORT   |
IT IS THEN SAFE TO CONNECT DEVICE TO MS EXCEL DATASTREAMER          |
*YOU WONT BE ABLE TO CONNECT DEVICE IF IT IS STILL CONNECTED HERE*  |
--------------------------------------------------------------------
*/
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include "HX711_t.h" 
#define calibration_factor 1780 //This value is obtained using the Calibration_LoadCell sketch
#define zero_factor 0  //This large value is obtained using the Calibration_LoadCell sketch (-50538) ; Can be used as permanent tearing solution

#define LOADCELL_DOUT_PIN  8 //DT PRP
#define LOADCELL_SCK_PIN   9 //SCK YEL
// VCC - RED  
// GND - BLK

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);


HX711 scale;
float newton = 4.44;

void setup() {
  //Start serial communication
  Serial.begin(9600);
  //Setting up LED Display
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  Serial.println("Force testing for P21096: Bone Testing");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the Calibration_LoadCell sketch (defined above)
  Serial.println("Setting calibration factor...");
  scale.tare(); //TEAR FOR NOW BUT REMOVE AFTER
  //scale.set_offset(zero_factor); //Zero out the scale using a previously known zero_factor ; obtained by using Calibration_LoadCell sketch (defined above)
  Serial.println("Setting zero factor...");
  
  //Setting up Serial display
  Serial.println("Waiting for reading to stabilize...");
  
  //wait for HX711 chips to stabilize
  delay(5000);
}

void loop() {
  //Take reading and convert it from lbs to newtons (Leaving in debug lines for lbs)
  Serial.print("Reading: ");
  //Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  //Serial.print(" lbs"); //You can change to kg but you'll need to change the calibration_factor
  //Serial.println();
  //Serial.println(scale.read()); This wasnt accurate either when tested ; get units is best bet. Will modify library more.
  //Serial.println(scale.read_average());
  float loadValue = (scale.get_units());
  //float finalValue = loadValue * newton;
  Serial.print(loadValue);
  //Serial.print(finalValue);
  //Serial.print(" N"); //You can change to kg but you'll need to change the calibration_factor
  Serial.print(" lbs");
  Serial.println();

  //Load sensor (LED output)
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Reading: ");
  display.setTextSize(2);
  display.setCursor(38,0);
  display.print(loadValue);
  //display.print(finalValue);
  display.print(" ");
  display.setTextSize(1);
  //display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("N");


  display.setTextSize(0.2);
  display.setCursor(0,57);
  display.print("P21097 Bone Testing");
  display.display(); 
  
  //Print values as quickly as possible - add delay (ms) if you change your mind
  delay(250);
}
