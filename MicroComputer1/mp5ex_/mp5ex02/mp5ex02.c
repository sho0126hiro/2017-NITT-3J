/**********************************************************
プッシュスイッチによってLEDのON-OFFを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void waitmsec(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190は実測によって求めた値 25MHz駆動*/
	}
}

main()
{
	initLed();
	initPushSW();
	while(1) {
		if (checkPushSW(0)==1 && checkPushSW(1)==0 && checkPushSW(2)==0 && checkPushSW(3)==0) { /*PushSWの0のみがONの時*/
			turnOnLed(0);
			turnOnLed(1);
			waitmsec(250);
			turnOffLed(0);
			turnOffLed(1);
			waitmsec(250);
		}
		if (checkPushSW(1)==1 && checkPushSW(0)==0 && checkPushSW(2)==0 && checkPushSW(3)==0) { /*PushSWの1のみがONの時*/
			turnOnLed(0);
			turnOffLed(1);
			waitmsec(500);
			turnOffLed(0);
			turnOnLed(1);
			waitmsec(500);
		}
		if (checkPushSW(2)==1 && checkPushSW(0)==0 && checkPushSW(1)==0 && checkPushSW(3)==0) { /*PushSWの2がONの時*/
			turnOnLed(0);
			turnOffLed(1);
			waitmsec(1000);
			turnOffLed(0);
			turnOnLed(1);
			waitmsec(1000);
		}
		turnOffLed(0);
		turnOffLed(1);
	}
}

