/**********************************************************
�v�b�V���X�C�b�`�ɂ����LED��ON-OFF���s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void waitmsec(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190�͎����ɂ���ċ��߂��l 25MHz�쓮*/
	}
}

main()
{
	initLed();
	initPushSW();
	while(1) {
		if (checkPushSW(0)==1 && checkPushSW(1)==0 && checkPushSW(2)==0 && checkPushSW(3)==0) { /*PushSW��0�݂̂�ON�̎�*/
			turnOnLed(0);
			turnOnLed(1);
			waitmsec(250);
			turnOffLed(0);
			turnOffLed(1);
			waitmsec(250);
		}
		if (checkPushSW(1)==1 && checkPushSW(0)==0 && checkPushSW(2)==0 && checkPushSW(3)==0) { /*PushSW��1�݂̂�ON�̎�*/
			turnOnLed(0);
			turnOffLed(1);
			waitmsec(500);
			turnOffLed(0);
			turnOnLed(1);
			waitmsec(500);
		}
		if (checkPushSW(2)==1 && checkPushSW(0)==0 && checkPushSW(1)==0 && checkPushSW(3)==0) { /*PushSW��2��ON�̎�*/
			turnOnLed(0);
			turnOffLed(1);
			waitmsec(1000);
			turnOffLed(0);
			turnOnLed(1);
			waitmsec(1000);
		}
		turnOffLed(0);
		turnOffLed(1);
	}
}

