#include <3048fone.h>

void waitmsec(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190�͎����ɂ���ċ��߂��l 25MHz�쓮*/
	}
}

/* ------------------------------------------------- */
/* LED INITIALIZATION */
/* ------------------------------------------------- */
/**********************************************************
LED 0:P1-0
LED 1:P1-1
LED 2:P1-2
LED 3:P1-3
����4�r�b�g���o�͂ɂ���
**********************************************************/
void initLed_P1()
{
	P1.DDR = 0xf;
}

/* ------------------------------------------------- */
/* LET LED ON */
/* ------------------------------------------------- */
/*number��0�܂���1*/
void turnOnLed_P1(short int number)
{ 
	static const unsigned char mask[]={1,2,4,8};
	P1.DR.BYTE |= mask[number];
}

/* ------------------------------------------------- */
/* LET LED OFF */
/* ------------------------------------------------- */
/*number��0�܂���1*/
void turnOffLed_P1(short int number)
{
	static const unsigned char mask[]={0xfe,0xfd,0xfb,0xf7};
	P1.DR.BYTE &= mask[number];
}
main()
{
	initLed_P1();
	while(1) {
		turnOnLed_P1(0); /*LED0��ON*/
		turnOffLed_P1(3); /*LED3��OFF*/
		waitmsec(2000);
		turnOnLed_P1(1); /*LED1��ON*/
		turnOffLed_P1(0); /*LED0��OFF*/
		waitmsec(2000);
		turnOnLed_P1(2); /*LED2��ON*/
		turnOffLed_P1(1); /*LED1��OFF*/
		waitmsec(2000);
		turnOnLed_P1(3); /*LED3��ON*/
		turnOffLed_P1(2); /*LED2��OFF*/
		waitmsec(2000);
	}
}
