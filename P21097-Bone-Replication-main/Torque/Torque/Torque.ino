
/*

 The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons. Fortunately,
 the TRT-25 also uses a wheatstone bridge configuration.

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
#include "HX711.h" //This library needed to modified ; Original header file (HX711.h.orig) included. 

#define LOADCELL_DOUT_PIN 10 //DT PRP 10
#define LOADCELL_SCK_PIN  11 //SCK YEL 11
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1

Adafruit_SH1106 display(OLED_RESET);
HX711 scale;
float torque;
float raw_count = 0.0;        // raw read from ADC
float full_scale = 25.0;      // full scale of output for TRT-25 (see specs)
float sensitivity = 0.00252;  // mV/V value (see calibration certificate)
float gain = 128.0;           // gain set explicity to 128 
float aToD = 16777216.0;      // 2 ^ 24 since HX711 is a 24-bit ADC
float offset_value = -0.36;    // Still finding some small error. This value might need to be adjusted in the future.



void setup() {
  Serial.begin(9600); //BAUD RATE TO BE SET IN SERIAL MONITOR
  Serial.println("Torque testing for P21096: Bone Testing");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.tare();
  //Setting up Serial display
  Serial.println("Waiting for reading to stabilize...");
  //wait for HX711 chips to stabilize
  delay(5000);
}

void loop() {
  //Take reading and convert it from lbs to newtons (Leaving in debug lines for lbs)
  Serial.print("Reading: ");
  raw_count = (scale.read());
  //NO KNOWN WAY TO CALIBRATE WITH KNOWN TORQUE VALUES TO INTERPOLATE/EXTRAPOLATE
  //APPROXIMATE TORQUE = (((raw_count * full_scale) / (sensitvity * gain * (2^24))) - offset_value);
  torque = (((raw_count * full_scale) / (sensitivity * gain * aToD)) + offset_value);
  Serial.print(torque);
  Serial.print(" IN LBS"); //Default units for sensor (Can always be changed)
  Serial.println();
  /*
  //Torque sensor (LED output)
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Reading: ");
  display.setTextSize(2);
  display.setCursor(38,0);
  display.print(torque);
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
  */
  
  //Print values as quickly as possible - add delay (ms) if you change your mind (4 readings a second)
  delay(250);
}
