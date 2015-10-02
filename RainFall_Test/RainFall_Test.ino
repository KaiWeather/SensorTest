/*
	Rain Fall Test
	By: Daniel Noyes
	Kai Weather Monitoring Project
	Date: March 2nd, 2015
	
	This Code increment everytime the rain toggles from 0.011” or 0.2794 mm of rain
	https://www.sparkfun.com/products/8942
	
	This Code assumes a 1 Kohm pull up resistor on the analog line
	
       ^ 5 volts
       │
    ^Diode^
       │
  D8 ──┼── R 1K ───────────┐
       │                    \ Rain bucket toggle switch
    vDiodev    ┌── R 1K ───┘
       │       │
       V GND   V GND
			 
	Notes: Diode use recomended from sparkfun weather sheild schematic.
*/

#include <PinChangeInt.h>
const int RAIN = 12;

// Rain Variables
volatile float dailyrainin = 0; // [rain inches so far today in local time]
volatile unsigned long raintime, rainlast, raininterval;

//Interrupt routines (these are called by the hardware interrupts, not by the main code)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void rainIRQ()
{
	raintime = millis(); // grab current time
	raininterval = raintime - rainlast; // calculate interval between this and last event
		if (raininterval > 10) // ignore switch-bounce glitches less than 10mS after initial edge
	{
		//Serial.println("IRQ");
		dailyrainin += 0.011; //Each dump is 0.011" of wate

		rainlast = raintime; // set up for next event
	}
}


void setup() {
	// initialize serial communications at 9600 bps:
	Serial.begin(9600);
	delay(200);
	Serial.println("Initiating Rain Fall Test");
	
	pinMode(RAIN, INPUT_PULLUP); // input from wind meters rain gauge sensor
	attachPinChangeInterrupt(RAIN, rainIRQ, FALLING);
}

void loop() {
	Serial.print("dailyrainin=");
	Serial.print(dailyrainin,3);

	Serial.println();
	// wait 2 seconds
	delay(2000);										 
}
	
	
