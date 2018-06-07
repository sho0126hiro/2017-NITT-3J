/**********************************************************
LEDのPWM(PulseWidthModulation)駆動
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void waitmsec(int msec)
/*msec間なにもしない時間稼ぎ関数*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190は実測によって求めた値 25MHz駆動*/
	}
}

main()
{
	int i,t=12;/*t=周期/2*/
	initLed(); /*LEDの初期化*/
	turnOnLed(0); /*LED0のON*/
	while(1) {
		/*デューティ比50%*/
		turnOnLed(1); /*LED1のON*/
		waitmsec(t);
		turnOffLed(1); /*LED1のOFF*/
		waitmsec(t);
	}
}
/*t=13
ほんのわずかの点滅が確認できる
t=12
点滅見えない
*/
