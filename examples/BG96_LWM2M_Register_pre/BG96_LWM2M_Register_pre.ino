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

	DebugSerial.println("BG96 Module Ready!!!");
	DebugSerial.println("");
	DebugSerial.println("");
	DebugSerial.println("===[ LWM2M Register Pre ]===");

	/* Disable LWM2M */
	if (BG96.disableLWM2M() == 0)
	{
		DebugSerial.println("Disable LWM2M...");
	}

	/* Set LWM2M Server 106.103.233.155:5783 */
	if (BG96.setLWM2M_Server() == 0)
	{
		DebugSerial.println("Set LWM2M Server : OK");
	}

	/* Select LWM2M */
	if (BG96.selectLWM2M() == 0)
	{
		DebugSerial.println("Select LWM2M : OK");
	}

	/* Enable LWM2M */
	if (BG96.enableLWM2M() == 0)
	{
		DebugSerial.println("Enable LWM2M : OK");
	}

	/* Reboot BG96 */
	DebugSerial.println("Reboot BG96...");
	BG96.resetModule();

	delay(10000);

	DebugSerial.println("BG96 LWM2M Register Pre Complete!!!");  

}

void loop() {

	delay(100);

}
