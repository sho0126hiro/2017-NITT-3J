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
	initLed();
	while(1) {
		turnOnLed(0); /*LED0‚ÌON*/
		turnOffLed(1); /*LED1‚ÌOFF*/
		waitmsec(250);
		turnOffLed(0); /*LED0‚ÌOFF*/
		turnOnLed(1); /*LED1‚ÌON*/
		waitmsec(250);
	}
}
