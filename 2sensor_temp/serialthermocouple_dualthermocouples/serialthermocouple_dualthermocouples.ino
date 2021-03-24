// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include "max6675.h"


/*Variables*/
int thermo1DO = 5;
int thermo1CS = 6;
int thermo1CLK = 7;
int thermo2DO = 8;
int thermo2CS = 9;
int thermo2CLK = 10;

/*Function Declaration*/
MAX6675 thermocouple1(thermo1CLK, thermo1CS, thermo1DO);
MAX6675 thermocouple2(thermo2CLK, thermo2CS, thermo2DO);

/*Baud rate communication for serial monitor*/
/*Wait 5 seconds before taking inital reading*/
void setup() {
  Serial.begin(9600);

  Serial.println("Temapture testing for P21097: Bone Replication");
  // wait for MAX chip to stabilize
  delay(500);
}

/*Begin reading of two seperate thermocouples : Check pin connections above! */
void loop() {
  // basic readout test, just print the current temp
  
   Serial.print("Thermocouple 1: C = "); 
   Serial.println(thermocouple1.readCelsius());
   Serial.print("Thermocouple 1: F = ");
   Serial.println(thermocouple1.readFahrenheit());
   delay(100);
   Serial.println("");
   Serial.print("Thermocouple 2: C = "); 
   Serial.println(thermocouple2.readCelsius());
   Serial.print("Thermocouple 2: F = ");
   Serial.println(thermocouple2.readFahrenheit());
   Serial.println(""); 
 
   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   //Delay readings by '3' seconds
   delay(1000);
}
