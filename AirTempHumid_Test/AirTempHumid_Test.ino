/*
  Air Temp and Humidity Sensor Test
  By: Daniel Noyes
  Kai Weather Monitoring Project
  Date: February 27th, 2015
  
  This Code I2C digital sensor data for both Ambient Temperature and Relative Humidity
  https://www.adafruit.com/products/1899

  SDL ───────┐
           HTU210
  SDA ───────┘

*/
#include <Wire.h>
#include "Adafruit_HTU21DF.h"

Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Initiating Air Temp and Humidity Sensor Test");
  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
  }
}

void loop() {

  // print the results to the serial monitor:
  Serial.print("ATemp = ");
  Serial.print(htu.readTemperature());
  Serial.print("\t| Hum = ");
  Serial.println(htu.readHumidity());
  // wait 2 seconds
  delay(2000);                     
}
