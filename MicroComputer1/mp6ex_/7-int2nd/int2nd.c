/**********************************************************
プッシュスイッチと時間割り込みによってLEDのPWM制御を行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

volatile int led0,led1;
const int period=10; /*周期10msec*/
const int low=1;

main()
{
	initLed();
	initPushSW();
	led0=led1=0;
	initTimer1Int(1000); /*タイマ割り込み1msec */
	                     /*単位はμsec ITUch1のみ使用*/
	E_INT();        /*CPU割り込み許可*/
	startTimer1();  /*時間割り込みタイマスタート*/
	while(1){
		if (checkPushSW(0)==1) { /*PushSWの0がONの時*/
			led0=period;
		} else if (checkPushSW(1)==1) { /*PushSWの1がONの時*/
			led0=low;
		} else {
			led0=0;
		}
		if (checkPushSW(2)==1) { /*PushSWの2がONの時*/
			led1=period;
		} else if (checkPushSW(3)==1) { /*PushSWの3がONの時*/
			led1=low;
		} else {
			led1=0;
		}
	}
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
	clearTimer1Flag();  /*タイマステータスフラグのクリア 忘れないこと*/
	if (tick<led0) {
		turnOnLed(0);
	} else {
		turnOffLed(0);
	}
	if (tick<led1) {
		turnOnLed(1);
	} else {
		turnOffLed(1);
	}
	tick++;
	if (tick==period) tick=0;
}
