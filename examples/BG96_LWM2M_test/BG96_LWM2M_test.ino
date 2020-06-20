#include "BG96.h"

#define DebugSerial Serial
#define M1Serial	Serial1
#define PWR_PIN		2
#define STAT_PIN	3

BG96 BG96(M1Serial, DebugSerial, PWR_PIN, STAT_PIN);
int value = 0;

void setup() {
	// put your setup code here, to run once:
	M1Serial.begin(115200);
	DebugSerial.begin(115200);

	/* Power On Sequence */
	if ( BG96.isPwrON() )
	{
		DebugSerial.println("BG96 Power ON Status");
		if ( BG96.pwrOFF() ) {
			DebugSerial.println("BG96 Power Off Error");
		} else {
			DebugSerial.println("BG96 Power Off Success");
			DebugSerial.println("Module Power ON Sequence Start");
			if ( BG96.pwrON() ) {
				DebugSerial.println("BG96 Power ON Error");
			} else
				DebugSerial.println("BG96 Power ON Success");
		}
	}
	else
	{
		DebugSerial.println("BG96 Power OFF Status");
		if ( BG96.pwrON() ) {
			DebugSerial.println("BG96 Power ON Error");
		} else
			DebugSerial.println("BG96 Power ON Success");
	}

	/* BG96 Module Initialization */
	if (BG96.init()) {
		DebugSerial.println("BG96 Module Error!!!");
	}

	if (BG96.lwm2mInit() == 0 )
		DebugSerial.println("LWM2M Initialization!!!");

}

void loop() {
	/* LWM2M Communication Code Here !!! */

	delay(100);

}
