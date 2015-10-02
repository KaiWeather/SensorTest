/*
  Wind Speed Sensor Test
  By: Daniel Noyes
  Kai Weather Monitoring Project
  Date: April 11th, 2015

  This Code uses the Anerometer from Adafruit
  https://www.adafruit.com/products/1733
  
         ^ 7-24 DC
         │
 BROWN ──┴───── VIN

 BLUE  ──────── A0

 BLACK ──┐
         │
         V GND
*/

const int WINDSPEED = A5;

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Initiating Wind Speed Sensor Test");
}

void loop() {

  printSpeed(WINDSPEED);
  // wait 2 seconds
  delay(2000);                     
}

float WSPD(int pin) 
{
  float WS;
  WS = analogRead(pin)* (5.0/ 1023.0);
  WS -= 0.4;
  if (WS > 0)
  {
    WS /= 0.049382716;//(2-0.4)/32.4 = 0.049382716
  }
  else
  {
    WS = 0;
  }
  return WS;
}

void printSpeed(int pin)
{
  float Speed = WSPD(pin);
  Serial.print("Wind Speed: ");
  Serial.print(Speed);
  Serial.println(" m/s");
}
