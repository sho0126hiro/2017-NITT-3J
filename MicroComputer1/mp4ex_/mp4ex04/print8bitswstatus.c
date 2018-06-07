/**********************************************************
マザーボードの8ビットスイッチがつながっているP2の各ビットを
直接見てみよう。
また，関数get8BitSW()が得る値を見てみよう。
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	unsigned char sw1,sw2;
	initLed();
	initSCI1();
	init8BitSW();/*8bitSWの初期化*/
	while(1) {
		sw1=P2.DR.BYTE;
		sw2=get8BitSW();
		SCI1_printf("P2.DR.BYTE=%08b get8BitSW()=%08b\n",sw1,sw2);
	}
}
