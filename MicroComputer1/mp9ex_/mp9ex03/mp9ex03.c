#include <3048fone.h>
#include "h8_3048fone.h"

volatile int count1=-1;/*LED0用カウンタ　-1の時は休止中*/
volatile int count2=-1;/*LED1用カウンタ　-1の時は休止中*/
volatile int count3=-1;

volatile int cmdstertptr=-1;

const char hello[]="                Hello, everyone!                  ";

main()
{
	int j;
	
	initLCD();
	initSCI1();
	initLed();
	initPushSW();/*PushSWの初期化*/
	initTimer1Int(10000);/*時間割り込み10000μsec=10msec ch1使用*/
	E_INT();        /*CPU割り込み許可*/
	startTimer1();  /*時間割り込みタイマスタートch1*/
	
	LCD_gotoxy(0,0);
	LCD_printf("pushSW status");
	
	while(1) {
		if ((count1==-1 || 50<count1) && checkPushSW(0)==1) {
			count1=0;
			turnOnLed(0);
		} else if (100<count1 && count1<200) { /*200カウントで2秒経過*/
			turnOffLed(0);
		} else if (200<count1 && count1<300){
			turnOnLed(0);
		} else if (300<count1){
			count1=-1;
			turnOffLed(0);
		}
		if ((count2==-1 || 50<count2) && checkPushSW(1)==1) {
			count2=0;
			turnOnLed(1);
		} else if (100<count2 && count2<200) { /*200カウントで2秒経過*/
			turnOffLed(1);
		} else if (200<count2 && count2<300){
			turnOnLed(1);
		} else if (300<count2){
			count2=-1;
			turnOffLed(1);
		}
		
		if ( (count3<0 || 10<count3) &&checkPushSW(2)==1) {
			count3 = 0;
			cmdstertptr = 0;
		}
		if(0<=cmdstertptr) {
			LCD_gotoxy(0,1);
			LCD_printf("<");
			for(j = 0; j < 14; j++) {
				LCD_printf("%c", hello[cmdstertptr+j]);
			}
			LCD_printf(">\r");
			if (cmdstertptr==34) {
				count3=-1;
			}
			cmdstertptr=-1;
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
	if (count3!=-1) count3++;
	if (count3%25==0) {/*0.25*/
		cmdstertptr=count3/25;
	}
}