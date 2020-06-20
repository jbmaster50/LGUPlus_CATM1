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

	delay(10000);

	DebugSerial.println("BG96 Module Ready!!!");
	DebugSerial.println("");
	DebugSerial.println("");
	DebugSerial.println("===[ LWM2M Register ]===");

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

	/* Select Check */
	if (BG96.chkLWM2M() == 0)
	{
		DebugSerial.println("Selected...");    
	}else
	{
		if (BG96.selectLWM2M() == 0)
			DebugSerial.println("Selected...");
		else
		{
			DebugSerial.println("Not Selected...");
			while(1);
		}
	}

	/* Make LWM2M HashCode */
	char HashCode[32];
	if (BG96.makeHashLWM2M(HashCode, sizeof(HashCode), "CZM1") == 0)
	{
		DebugSerial.println("Make LWM2M HashCode : OK");
		DebugSerial.println(HashCode);
	}  

	/* EPNS Enable */
	if (BG96.epnsEnable(HashCode) == 0)
	{
		DebugSerial.println("EPNS Enable : OK");
	}

	/* MBSPS Enable */
	if (BG96.makeMBSPSEnable("CZM1", szCIMI, szUICCID, "M1-SMS-Test-Dev") == 0)
	{
		DebugSerial.println("MBSPS Enable : OK");
	}

	/* Enable LWM2M */
	if (BG96.enableLWM2M() == 0)
	{
		DebugSerial.println("Enable LWM2M : OK");
	}

	if (BG96.registerLWM2M() == 0)
	{
		DebugSerial.println("Register LWM2M : OK");
	}  

	DebugSerial.println("Reboot BG96...");
	BG96.resetModule();

	delay(10000);

	DebugSerial.println("BG96 LWM2M Register Complete!!!");

}

void loop() {

	delay(100);

}
