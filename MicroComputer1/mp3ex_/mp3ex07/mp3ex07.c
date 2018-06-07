#include <3048fone.h>
#include "h8_3048fone.h"

void wait_m4sec(int m4_sec)
/*10^-4secで指示する間なにもしない時間稼ぎ関数*/
/*たとえばwait_m4sec(15);を呼ぶと1.5msec後にこの関数から戻る*/
{
	int i,j;
	for (i=0;i<m4_sec;i++) {
		for (j=0;j<419;j++); /*419の根拠を考えてみよう*/
	}
}

main()
{
	int i=2,j;
	initLed();
	while(1) {
		turnOnLed(0); /*LED0のON*/
		for(j=0;j<400;j++){
			/*デューティー比2^i%*/
			turnOnLed(1); /*LED1のON*/
			wait_m4sec(i);
			turnOffLed(1); /*LED1のOFF*/
			wait_m4sec(100-i);
		}
		if(i==64)i=2;
		else i=i*2;
	}
}
