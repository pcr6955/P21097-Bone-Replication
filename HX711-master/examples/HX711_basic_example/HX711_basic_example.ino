#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

//This is the test program for Senior Design
//We will need to take this measurement and convert it to Newtons
//This example assumes pounds (lbs). If you prefer kilograms, change the Serial.print(" lbs"); line to kg. The
//calibration factor will be significantly different but it will be linearly related to lbs (1 lbs = 0.453592 kg).

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.read();
    Serial.println("Force reading: ");
    Serial.print("Preparing to read");
    delay(5000);
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(250);
  
}
