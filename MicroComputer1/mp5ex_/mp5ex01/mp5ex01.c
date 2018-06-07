/**********************************************************
プッシュスイッチによってLEDのON-OFFを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	unsigned char sw1,sw2;
	initLed();
	initSCI1();
	initPushSW();
	while(1) {
		sw1=P4.DR.BYTE;
		sw2=getPushSW();
		SCI1_printf("P4.DR.BYTE=%08b getPushSW()=%08b\n",sw1,sw2);
	}
}

