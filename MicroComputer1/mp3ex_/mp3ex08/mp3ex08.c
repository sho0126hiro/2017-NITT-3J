/**********************************************************
LED��PWM(PulseWidthModulation)�쓮
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void waitmsec(int msec)
/*msec�ԂȂɂ����Ȃ����ԉ҂��֐�*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190�͎����ɂ���ċ��߂��l 25MHz�쓮*/
	}
}

main()
{
	int i,t=12;/*t=����/2*/
	initLed(); /*LED�̏�����*/
	turnOnLed(0); /*LED0��ON*/
	while(1) {
		/*�f���[�e�B��50%*/
		turnOnLed(1); /*LED1��ON*/
		waitmsec(t);
		turnOffLed(1); /*LED1��OFF*/
		waitmsec(t);
	}
}
/*t=13
�ق�̂킸���̓_�ł��m�F�ł���
t=12
�_�Ō����Ȃ�
*/
