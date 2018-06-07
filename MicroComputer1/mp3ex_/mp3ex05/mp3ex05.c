#include <3048fone.h>

void waitmsec(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190は実測によって求めた値 25MHz駆動*/
	}
}

/* ------------------------------------------------- */
/* LED INITIALIZATION */
/* ------------------------------------------------- */
/**********************************************************
LED 0:P5-0
LED 1:P5-1
LED 2:P5-2
LED 3:P5-3
下位4ビットを出力にする
**********************************************************/
void initLed()
{
	P5.DDR = 0xf;
}

/* ------------------------------------------------- */
/* LET LED ON */
/* ------------------------------------------------- */
/*numberは0または1*/
void turnOnLed(short int number)
{ 
	static const unsigned char mask[]={1,2,4,8};
	P5.DR.BYTE |= mask[number];
}

/* ------------------------------------------------- */
/* LET LED OFF */
/* ------------------------------------------------- */
/*numberは0または1*/
void turnOffLed(short int number)
{
	static const unsigned char mask[]={0xfe,0xfd,0xfb,0xf7};
	P5.DR.BYTE &= mask[number];
}
main()
{
	initLed();
	while(1) {
		turnOnLed(0); /*LED0のON*/
		turnOffLed(1); /*LED1のOFF*/
		waitmsec(1000);
		turnOffLed(0); /*LED0のOFF*/
		turnOnLed(1); /*LED1のON*/
		waitmsec(1000);
	}
}
