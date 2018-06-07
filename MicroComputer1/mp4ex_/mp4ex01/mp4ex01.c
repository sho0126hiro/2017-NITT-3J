/**********************************************************
マザーボードの8ビットスイッチによってLEDのON-OFFを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void waitmsec(int msec)
/*mesc間なにもしない時間稼ぎ関数*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190は実測によって求めた値 25MHz駆動*/
	}
}

main()
{
	initLed();
	P2.DDR=0;
	P2.PCR.BYTE=0xff;
	while(1) {
		if(check8BitSW(1)) { /*8bitSWの1がONの時*/
			while(1){
				turnOnLed(0);
				turnOnLed(1);
				waitmsec(500);
				turnOffLed(0);
				turnOffLed(1);
				waitmsec(500);
				if(!check8BitSW(1))break;
			}
		} else { /*8bitSWの1がOFFの時*/
			while(1){
				turnOnLed(0);
				turnOnLed(1);
				waitmsec(250);
				turnOffLed(0);
				turnOffLed(1);
				waitmsec(250);
				if(check8BitSW(1))break;
			}
		}
	}
}