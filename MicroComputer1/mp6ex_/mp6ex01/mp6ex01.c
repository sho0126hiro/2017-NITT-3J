/**********************************************************
時間割り込みによってLEDのON-OFFを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	initLed();
	initTimer1Int(10000); /*時間割り込み10000μsec=10msec ITUch1使用*/
	E_INT();        /*CPU割り込み許可*/
	startTimer1();  /*時間割り込みタイマスタートch1*/
	while(1);       /*なにもしないループ*/
}

#pragma asm
    .SECTION    MYVEC, DATA, LOCATE=H'000070
    .ORG        H'000070  ;IMIA1
    .DATA.L     _TimerIntFunc
    .SECTION    P,CODE,ALIGN=2 ;これを忘れてはいけない
#pragma endasm

#pragma interrupt (TimerIntFunc)
void TimerIntFunc() /*タイマ割り込みルーチン*/
{
	static int tick=0;
	static int count=0;
	clearTimer1Flag();  /*タイマステータスフラグのクリア 忘れないこと*/
	count++;
	if (count==50) {
		count=0;
		if (tick==1) {
			turnOnLed(0);
			turnOffLed(1);
		} else {
			turnOffLed(0);
			turnOnLed(1);
		}
		tick=1-tick;
	}
}
