/*
  Wind Direction Test
 By: Daniel Noyes
 Kai Weather Monitoring Project
 Date: February 26th, 2015
 
 This Code reads the analog value off Sparkfun's Wind Direction unit.
 https://www.sparkfun.com/products/8942
 
 This Code assumes a 1 Kohm pull up resistor on the analog line
 
      ^ 5 volts
      │
      R 1 Kohm
      │
 A1 ──┴── WindPin1 ───┐
                      R - Variable Resistance Based on Wind Direction
      ┌── WindPin2 ───┘
      │
      V GND
 */

// Pin Constaint for each device
const int WINDDIR = A1;

void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println("Initiating Wind Direction Test");
}

void loop() {

  // print the results to the serial monitor:
  Serial.print("WindDir = ");      
  Serial.print(wind_direction());
  Serial.println();
  // wait 2 seconds
  delay(2000);                     
}

float wind_direction() 
{
  int WDValue;
  WDValue = analogRead(WINDDIR);// * (5.0/ 1023.0);

  if (WDValue < 75)
    return 112.5;
  if (WDValue < 88)
    return 67.5;
  if (WDValue < 109)
    return 90;
  if (WDValue < 155)
    return 157.5;
  if (WDValue < 215)
    return 135;
  if (WDValue < 267)
    return 202.5;
  if (WDValue < 348)
    return 180;
  if (WDValue < 435)
    return 22.5;
  if (WDValue < 531)
    return 45;
  if (WDValue < 615)
    return 247.5;
  if (WDValue < 665)
    return 225;
  if (WDValue < 743)
    return 337.5;
  if (WDValue < 804)
    return 0;
  if (WDValue < 854)
    return 292.5;
  if (WDValue < 914)
    return 315;
  if (WDValue < 982)
    return 270;

  return (-1); // does not exist, sensor not found
}


