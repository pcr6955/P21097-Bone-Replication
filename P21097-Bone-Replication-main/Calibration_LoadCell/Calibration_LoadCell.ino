/*
 This is the calibration sketch. Use it to determine the calibration_factor that the main example uses. It also
 outputs the zero_factor useful for projects that have a permanent mass on the scale in between power cycles.
 
 Setup your scale and start the sketch WITHOUT a weight on the scale
 Once readings are displayed place the weight on the scale
 Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
 Use this calibration_factor on the example sketch
 
 This example assumes pounds (lbs). If you prefer kilograms, change the Serial.print(" lbs"); line to kg. The
 calibration factor will be significantly different but it will be linearly related to lbs (1 lbs = 0.453592 kg).
 
 Your calibration factor may be very positive or very negative. It all depends on the setup of your scale system
 and the direction the sensors deflect from zero state.
 
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE

-------------------------WIRING----------------------------
HX711 pins                                                |
 +EXCITATION -> RED                                       |
 -EXCITATION -> BLK                                       |
 +SIGNAL     -> GTN                                       |
 -SIGNAL     -> WHT                                       |
                                                          |
Arduino pins                                              |
 7 -> DOUT                                                |
 6 -> HX711 CLK                                           |
 5V -> VCC                                                |
 GND -> GND                                               |
                                                          |
 The HX711 board will be powered by the Arduino 5V power. |
-----------------------------------------------------------
*/

#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711
#define LOADCELL_DOUT_PIN  8 //DT PRP 10 FOR LC
#define LOADCELL_SCK_PIN  9
//SCK YEL 11 FOR LC
// VCC - RED  
// GND - BLK

HX711 scale;

float calibration_factor = 1780; //1780 worked for my button load cell - Does 3000 work?; -301309 worked for my load cell bar (1) --40000 worked for my load cell bar (2) ; Will need to recalibrate for final setup.
//1.14 lbs

void setup() {
  Serial.begin(9600);
  Serial.println("P21097 calibration for load cell");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(); //-50538 zero facture from last read
  scale.tare();  //Reset the scale to 0 ; 


  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
delay(1000);
}
