/*
  Water Temperature Sensor Test
 By: Daniel Noyes
 Kai Weather Monitoring Project
 Date: February 26th, 2015
 
 This Code uses the dallas one wire bus
 
 This Code assumes a 1 Kohm pull up resistor on the digital line
 
 Based on the Dallas Temperature Example:
 https://github.com/milesburton/Arduino-Temperature-Control-Library
 
       ^ 5 volts
       │
 RED ──┘
 
       ^ 5 volts
       │
       R 1 Kohm - pull up
       │
 YLW ──┴────────── D4
 
 BLU ──┐
       │
       V GND
 */
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin D4 on the Arduino
#define ONE_WIRE_BUS 4

//setup onewire bus to communicate with other onewire devices
OneWire oneWire(ONE_WIRE_BUS);
//Init Dallas Temperature with the onewire bus.
DallasTemperature sensors(&oneWire);

//Temperature Address
DeviceAddress Temp_0;

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Initiating Water Temperature Sensor Test");

  Serial.print("Searching for any sensors...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" Devices");

  //test search for temperature sensor
  if (!sensors.getAddress(Temp_0, 0))
    Serial.println("Unable to find address for Device 0");

  Serial.print("Device 0 Address: ");
  printAddress(Temp_0);
  Serial.println();

  //Set Sensor to 12 bit resolution
  sensors.setResolution(Temp_0, 12);
  //Check the resolution of the sensor
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(Temp_0), DEC);
  Serial.println();

  Serial.println("Finished INIT");
}

void loop() {

  // print the results to the serial monitor:
  //Serial.print("WaterTemp = ");      
  //Serial.print(water_temp());
  //Serial.println();
  printTemperature(Temp_0);
  // wait 2 seconds
  delay(2000);                     
}

float water_temp() 
{
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void printTemperature(DeviceAddress deviceAddress)
{

  //tell sensor to update temperature
  sensors.requestTemperatures();
  float temp = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(temp);
  Serial.print(" Temp F: ");
  Serial.println(DallasTemperature::toFahrenheit(temp)); // Converts Celcius to Fahrenheit
}


//Help Routine to print address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16)
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

