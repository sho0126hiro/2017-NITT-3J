/**********************************************************
マザーボードの8ビットスイッチによってLEDのON-OFFを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	initLed();
	P2.DDR=0;
	P2.PCR.BYTE=0xff;
	while(1) {
		if (P2.DR.BIT.B0==0) { /*8bitSWの0がONの時*/
			turnOnLed(0);
			turnOnLed(1);
		} else if (P2.DR.BIT.B1==0) { /*8bitSWの1がONの時*/
			turnOnLed(0);
			turnOffLed(1);
		} else if (P2.DR.BIT.B2==0) { /*8bitSWの2がONの時*/
			turnOffLed(0);
			turnOnLed(1);
		} else {
			turnOffLed(0);
			turnOffLed(1);
		}
	}
}