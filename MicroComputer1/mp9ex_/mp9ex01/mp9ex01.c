#include <3048fone.h>
#include "h8_3048fone.h"

volatile int count1=-1;/*LED0用カウンタ　-1の時は休止中*/
volatile int count2=-1;/*LED1用カウンタ　-1の時は休止中*/
volatile int count3=-1;

/*ON-OFF-ON-OFF*/

main()
{
	initLed();
	initPushSW();/*PushSWの初期化*/
	initTimer1Int(10000); /*時間割り込み10000μsec=10msec ch1使用*/
	E_INT();        /*CPU割り込み許可*/
	startTimer1();  /*時間割り込みタイマスタートch1*/
	while(1) {
		if ((count1==-1 || 50<count1) && checkPushSW(0)==1) { /*0~1s , on*/
			count1=0;
			turnOnLed(0);
		} else if (100<count1 && count1<200) { /*count 1~2s,off*/
			turnOffLed(0);
		} else if (200<count1 && count1<300){ /*count 2~3s,on*/
			turnOnLed(0);
		} else if (300<count1){ /*Off*/
			count1=-1;
			turnOffLed(0);
		}
		if ((count2==-1 || 50<count2) && checkPushSW(1)==1) { /*0~1s , on*/
			count2=0;
			turnOnLed(1);
		} else if (100<count2 && count2<200) { /*count 1~2s,off*/
			turnOffLed(1);
		} else if (200<count2 && count2<300){/*count 2~3s,on*/
			turnOnLed(1);
		} else if (300<count2){ /*Off*/
			count2=-1;
			turnOffLed(1);
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
	if (count1!=-1) count1++;
	if (count2!=-1) count2++;
}