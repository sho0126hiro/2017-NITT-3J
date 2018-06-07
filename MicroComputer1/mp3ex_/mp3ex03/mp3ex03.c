/**********************************************************
msecwaitŠÖ”‚Å1•b‚²‚Æ‚ÌLED‚ÌON-OFF‚ğs‚¤
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void waitmsec(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190‚ÍÀ‘ª‚É‚æ‚Á‚Ä‹‚ß‚½’l 25MHz‹ì“®*/
	}
}

main()
{
	int i;
	initLed();

	while(1) {
		for(i=0;i<2;i++){
			turnOnLed(1); /*LED1‚ÌON*/
			waitmsec(500);
			turnOffLed(1); /*LED1‚ÌOFF*/
			waitmsec(500);
		}
		for(i=0;i<2;i++){
			turnOnLed(0); /*LED0‚ÌOFF*/
			waitmsec(500);
			turnOffLed(0); /*LED1‚ÌON*/
			waitmsec(500);
		}
		turnOnLed(1);
		waitmsec(500);
		turnOffLed(1);
		waitmsec(500);
		turnOnLed(0);
		waitmsec(500);
		turnOffLed(0);
		waitmsec(500);
	}
}
