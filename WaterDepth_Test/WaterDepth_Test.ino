/*
	Water Depth Test
	By: Daniel Noyes
	Kai Weather Monitoring Project
	Date: April 26th, 2015

	This code calculates the water depth based on the referance resistance.
	Two voltage dividers are used, one for the depth and another for the referance.

	https://www.adafruit.com/product/464
	http://www.milonetech.com/
	
        ^ 5 volts      ^ 5 volts
        │              │
        R 560          R 560
		│              │
   A3 ──┴────┐    A4 ──┴────┐
          Depth Res       Ref Res
        ┌────┘         ┌────┘
        │              │
        V GND          V GND
*/

#define SERIESRESISTOR 560
//Water depth pin config
#define WATER_DEPTH A3
#define WATER_DEPTH_REF A4

// What pin to connect the sensor to
#define NUMSAMPLES 15
float WD_REF;
//#define FLAP 1
//#define FUDGE 0.3

void setup(void) {
	Serial.begin(9600);
	delay(200);
	Serial.println("Initiating Water Depth Test");
	WD_REF = CalcRes(WATER_DEPTH_REF);
	Serial.print("Sensor Referance ");
	Serial.println(WD_REF);
}

void loop(void) {
	float ETAPE_REF;
	float waterlevel;
	float lastwaterlevel=0;

	Serial.print("Sensor resistance ");
	Serial.println(CalcRes(WATER_DEPTH));
	/*waterlevel = 0;
	waterlevel= -1 * 0.006958 * average + 11.506958+ FUDGE;
	if (lastwaterlevel<(waterlevel-FLAP)||lastwaterlevel>(waterlevel+FLAP))
	{
		Serial.print("Water level (inches) ");
		Serial.println(waterlevel);
	}*/
	delay(1000);
	//lastwaterlevel=waterlevel;
}

float CalcRes(int SENSORPIN)
{
	uint8_t i;
	float average;
	int samples[NUMSAMPLES];

	// take N samples in a row, with a slight delay
	for (i=0; i< NUMSAMPLES; i++) {
		samples[i] = analogRead(SENSORPIN);
		delay(10);
	}

	// average all the samples out
	average = 0;
	for (i=0; i< NUMSAMPLES; i++) {
		average += samples[i];
	}
	average /= NUMSAMPLES;

	// convert the value to resistance
	average = 1023 / average - 1;
	average = SERIESRESISTOR / average;

	return average;
}
