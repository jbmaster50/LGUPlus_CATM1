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

	/* Network Regsistraiton Check */
	while (BG96.canConnect() != 0) {
		DebugSerial.println("Network not Ready !!!");
		delay(2000);
	}

	if (BG96.actPDP() ) {
		DebugSerial.println("BG96 PDP Activation Error");
	}

	/* Network QoS Report to LGU+ (No-charge packet) */
	if (BG96.reportDevice() == 0)
	{
		DebugSerial.println("BG96 Device Report Success!!!");
	}

	DebugSerial.println("BG96 Module Ready!!!");
	DebugSerial.println("");
	DebugSerial.println("");
	DebugSerial.println("===[ LWM2M Server Input Data ]===");

	/* Get Phone Number */
	char szCIMI[16];
	if (BG96.getCIMI(szCIMI, sizeof(szCIMI)) == 0)
	{
		DebugSerial.print("Phone Number & Serial Number : ");
		DebugSerial.println(szCIMI);
	}

	/* Get ServingCell */
	char szUICCID[20];
	if (BG96.getUICCID(szUICCID, sizeof(szUICCID) ) == 0)
	{
		DebugSerial.print("UICCID : ");
		DebugSerial.println(szUICCID);
	}  

}

void loop() {

	delay(100);

}
