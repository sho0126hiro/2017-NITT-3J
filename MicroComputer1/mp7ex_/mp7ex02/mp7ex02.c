#include <3048fone.h>
#include "h8_3048fone.h"
volatile int P0count=0; /*P0のカウンタ*/
volatile int P1count=0; /*P0のカウンタ*/
volatile int P2count=0; /*P0のカウンタ*/
volatile int P3count=0; /*P0のカウンタ*/
volatile int request=0; /*割り込みルーチンからの表示要求*/

main(){
    int menu;
    initSCI1();
    initPushSW();
    
    initTimer1Int(1000);
    E_INT();
    startTimer1();
	while (1) {
	
		if(request) {     /*if (request!=0) {と同じ意味*/
			SCI1_printf("SW0->[%3d] SW1->[%3d] SW2->[%3d] SW3->[%3d]\n",P0count,P1count,P2count,P3count);
			request = 0;
		}
	}
}

#pragma asm
    .SECTION    MYVEC, DATA, LOCATE=H'000070
    .ORG        H'000070  ;IMIA1
    .DATA.L     _TimerIntFunc
    .SECTION    P,CODE,ALIGN=2 ;これを忘れてはいけない
#pragma endasm

void TimerIntFunc() /*タイマ割り込みルーチン*/
{
	int sw;
	static int status = 0; /*SW0の状態 0:押されていない 1:押されている*/
	/*
	statusは1になりやすく，0になりにくいようにする。（ヒステリシス）
	こうすることでチャタリング対策になる。
	スイッチが押されたら直ちに1にする
	スイッチが離された状態が10回（10msecになる）続いたら0にする
	この割り込み関数は1msec毎に起動するので，10回の実行で10msec経過したことになる
	*/
	const int Nantichatter = 10;
	static int statuscnt = 0;  /*スイッチが離された状態を数える変数*/
	clearTimer1Flag();  /*タイマステータスフラグのクリア 忘れないこと*/
	sw = getPushSW();
	if (status == 0) {
		if ((sw&1) == 1) {
			status = 1;
			P0count++;
			request = 1;
		}
		if ((sw&2) == 2) {
			status = 1;
			P1count++;
			request = 1;
		}
		if ((sw&4) == 4) {
			status = 1;
			P2count++;
			request = 1;
		}
		if ((sw&8) == 8) {
			status = 1;
			P3count++;
			request = 1;
		}
	} else { /*status == 1*/
		if ((sw&1) == 1 || (sw&2) == 2 || (sw&4) == 4 || (sw&8) == 8 ) {
			statuscnt = 0;
		} else {
			statuscnt++;
			if (Nantichatter < statuscnt) {
				status = 0;
			}
		}
	}
}
