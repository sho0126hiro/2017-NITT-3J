/**********************************************************
割り込みを用いた時計　起動時からの経過時間［秒］を
SCI1へ出力，WINDOWSのHyperTerminalなどで受信できる。
ただし，設定は
38400baud, Async, 8bit , NoParity, stop1
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

volatile long int time=0;/*時刻（1/100secでカウント）を保存する変数*/

volatile int countup=0;/*時計を動かすか止めるかをコントロールする変数*/

main()
{
	long int time1;
	unsigned int t1,t2;
	char ch;
	initSCI1(); /*SCI-ch1の初期化*/
	initTimer1Int(1000); /*ITUch1のインターバルタイマ初期化設定*/
	                     /*単位μsなので，時間割り込み1msec*/
	E_INT();        /*CPU割り込み許可*/
	startTimer1();  /*ITUch1タイマスタート*/
	while(1) {
		ch=SCI1_chkgetChar(); /*すぐに戻ってくる*/
		if (ch=='a') countup=1;/*Aが押されたらタイマースタート*/
		else if (ch=='b') countup=0;/*Bが押されたらタイマーストップ*/
		else if (ch=='c') time=0;/*Cが押されたらリセット*/
		time1=time; /*表示の途中で変数timeが変更されたときの対策*/
		SCI1_printf("%4ld.%02ld\r",time1/1000,time1%1000); 
		SCI1_printf("%d\r",time1);
	}
}

#pragma asm
	.SECTION    MYVEC, DATA, LOCATE=H'000070
	.ORG        H'000070  ;IMIA1
	.DATA.L     _TimerIntFunc
	.SECTION    P,CODE,ALIGN=2 ;これを忘れてはいけない
#pragma endasm

#pragma interrupt (TimerIntFunc)
void TimerIntFunc() /*インターバルタイマ割り込みルーチン*/
{
	time+=countup;/*countupが1のときtimeに加算される*/
	clearTimer1Flag();  /*ITUch1タイマフラグのクリア 忘れないこと*/
}

