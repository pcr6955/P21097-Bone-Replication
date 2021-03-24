#include <SPI.h>
#include "max6675.h" 
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);


//Sensor data appears to be about 5 degrees higher than expected

// Temperature Sensor1
int thermo1D0 = 5; // so
int thermo1CS = 6; 
int thermo1CLK = 7; // sck
float temp1 = 0; 
MAX6675 thermocouple1(thermo1CLK, thermo1CS, thermo1D0); 

/*
// Temperature Sensor2
int thermo2D0 = 8; // so
int thermo2CS = 9; 
int thermo2CLK = 10; // sck
float temp2 = 0; 
MAX6675 thermocouple2(thermo2CLK, thermo2CS, thermo2D0); 
*/
/*
// Temperature Sensor3
int thermo3D0 = 11; // so
int thermo3CS = 12; 
int thermo3CLK = 13; // sck
float temp3 = 0; 
MAX6675 thermocouple3(thermo3CLK, thermo3CS, thermo3D0);
*/

void setup()
{
  //Start serial communication
  Serial.begin(9600);
  //Setting up LED Display 
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

  //Setting up Serial display
  Serial.println("Tempature testing for P21096: Bone Testing");
  //wait for MAX chips to stabilize
  delay(5000);
}

void loop()
{
  
  //Serial Capture and display for Temp 1
  temp1 = (thermocouple1.readFarenheit()) - 5; 
  Serial.print("Thermocouple 1: F = ");
  Serial.println(temp1);
  delay(100);
  Serial.println("");
/*  
  //Serial Capture and display for Temp 2
  temp2 = thermocouple2.readFarenheit();
  Serial.print("Thermocouple 2: F = ");
  Serial.println(temp2);
  delay(100);
  Serial.println("");
  delay(100);
*/
/*
  //Serial Capture and display for Temp 3
  temp3 = thermocouple3.readFarenheit();
  Serial.print("Thermocouple 3: F = ");
  Serial.println(temp3);
  delay(100);
  Serial.println("");
  delay(100);
*/
 
  //clear display
  display.clearDisplay();

// tempature sensor 1 (LED)
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temp1: ");
  display.setTextSize(2);
  display.setCursor(38,0);
  display.print(temp1);
  display.print(" ");
  display.setTextSize(1);
  //display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("F");
/*
// temperature sensor 2 (LED)
  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("Temp2: ");
  display.setTextSize(2);
  display.setCursor(38,20);
  display.print(temp2);
  display.print(" ");
  display.setTextSize(1);
  //display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("F");
*/
/*
  // temperature sensor 3
  display.setTextSize(1);
  display.setCursor(0,40);
  display.print("Temp3: ");
  display.setTextSize(2);
  display.setCursor(38,40);
  display.print(temp3);
  display.print(" ");
  display.setTextSize(1);
  //display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("F");
*/  


  display.setTextSize(0.2);
  display.setCursor(0,57);
  display.print("P21097 Bone Testing");
  display.display(); 

    //For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   //Delay readings by '1' seconds
   delay(1000);
}
