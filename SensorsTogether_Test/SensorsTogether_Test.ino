#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "Adafruit_HTU21DF.h"

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 4

// Pin Constaint for each device
const int WINDSPEED = A0;
const int WINDDIR = A1;
const int RAIN = 7;
//const int WATERTEMP = 4;

//setup onewire bus
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

Adafruit_HTU21DF htu = Adafruit_HTU21DF();

// Rain Variables
volatile float rainHour[60]; //60 floating numbers to keep track of 60 minutes of rain
float rainin = 0; // [rain inches over the past hour)] -- the accumulated rainfall in the past 60 min
volatile float dailyrainin = 0; // [rain inches so far today in local time]
volatile unsigned long raintime, rainlast, raininterval;

//Time Keeping Variables
long lastSecond; //The millis counter to see when a second rolls by
byte seconds; //When it hits 60, increase the current minute
byte seconds_2m; //Keeps track of the "wind speed/dir avg" over last 2 minutes array of data
byte minutes; //Keeps track of where we are in various arrays of data
byte minutes_10m; //Keeps track of where we are in wind gust/dir over last 10 minutes array of data

//Interrupt routines (these are called by the hardware interrupts, not by the main code)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void rainIRQ()
{
  raintime = millis(); // grab current time
  raininterval = raintime - rainlast; // calculate interval between this and last event
    if (raininterval > 10) // ignore switch-bounce glitches less than 10mS after initial edge
  {
    dailyrainin += 0.011; //Each dump is 0.011" of water
    rainHour[minutes] += 0.011; //Increase this minute's amount of rain

    rainlast = raintime; // set up for next event
  }
}


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  delay(200);
  Serial.println("Initiating Weather Monitor Test V 1");
  
  sensors.begin();
  if (!htu.begin()) {
    Serial.println("Couldn't find Humidity/Temp sensor!");
    while (1);
  }
  
  pinMode(RAIN, INPUT_PULLUP); // input from wind meters rain gauge sensor
  seconds = 0;
  lastSecond = millis();
  attachInterrupt(4, rainIRQ, FALLING);//http://arduino.cc/en/Reference/AttachInterrupt
  interrupts();
  Serial.println("Weather Test Online!");
  
}

void loop() {
  if(millis() - lastSecond >= 1000)
  {
    lastSecond += 1000;
    if(++seconds > 59)
    {
      seconds = 0;

      if(++minutes > 59) minutes = 0;
      if(++minutes_10m > 9) minutes_10m = 0;

      rainHour[minutes] = 0; //Zero out this minute's rainfall amount
    }
  }
  float cel,WSValue,WDValue;
  WSValue = analogRead(WINDSPEED) * (5.0/ 1023.0);
  WDValue = analogRead(WINDDIR) * (5.0/ 1023.0);
  
  sensors.requestTemperatures();
  cel = sensors.getTempCByIndex(0);

  // print the results to the serial monitor:
  Serial.print("WindSpeed = " );                       
  Serial.print(WSValue);      
  Serial.print("\t| WindDir = ");      
  Serial.print(WDValue);
  
  Serial.print("\t| WTemp = ");
  Serial.print(cel);
  Serial.print(" C ");
  
  Serial.print("\t| ATemp = : ");
  Serial.print(htu.readTemperature());
  Serial.print("\t| Hum = ");
  Serial.print(htu.readHumidity());
  
  Serial.print("\t| rainin=");
  Serial.print(rainin, 2);
  Serial.print("\t| dailyrainin=");
  Serial.print(dailyrainin, 2);

  Serial.println();
  // wait 2 seconds
  delay(2000);                     
}
  
  
