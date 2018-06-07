/**********************************************************
プッシュスイッチによってLEDのON-OFFを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	initLed();
	initPushSW();
	while(1) {
		if (checkPushSW(0)==1) { /*PushSWの0がONの時*/
			turnOnLed(0);
			turnOffLed(1);
		} else if (checkPushSW(1)==1) { /*PushSWの1がONの時*/
			turnOffLed(0);
			turnOnLed(1);
		} else {
			turnOffLed(0);
			turnOffLed(1);
		}
	}
}
