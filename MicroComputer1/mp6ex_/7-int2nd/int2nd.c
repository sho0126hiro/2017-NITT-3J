/**********************************************************
�v�b�V���X�C�b�`�Ǝ��Ԋ��荞�݂ɂ����LED��PWM������s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

volatile int led0,led1;
const int period=10; /*����10msec*/
const int low=1;

main()
{
	initLed();
	initPushSW();
	led0=led1=0;
	initTimer1Int(1000); /*�^�C�}���荞��1msec */
	                     /*�P�ʂ̓�sec ITUch1�̂ݎg�p*/
	E_INT();        /*CPU���荞�݋���*/
	startTimer1();  /*���Ԋ��荞�݃^�C�}�X�^�[�g*/
	while(1){
		if (checkPushSW(0)==1) { /*PushSW��0��ON�̎�*/
			led0=period;
		} else if (checkPushSW(1)==1) { /*PushSW��1��ON�̎�*/
			led0=low;
		} else {
			led0=0;
		}
		if (checkPushSW(2)==1) { /*PushSW��2��ON�̎�*/
			led1=period;
		} else if (checkPushSW(3)==1) { /*PushSW��3��ON�̎�*/
			led1=low;
		} else {
			led1=0;
		}
	}
}

#pragma asm
    .SECTION    MYVEC, DATA, LOCATE=H'000070
    .ORG        H'000070  ;IMIA1
    .DATA.L     _TimerIntFunc
    .SECTION    P,CODE,ALIGN=2 ;�����Y��Ă͂����Ȃ�
#pragma endasm

#pragma interrupt (TimerIntFunc)
void TimerIntFunc() /*�^�C�}���荞�݃��[�`��*/
{
	static int tick=0;
	clearTimer1Flag();  /*�^�C�}�X�e�[�^�X�t���O�̃N���A �Y��Ȃ�����*/
	if (tick<led0) {
		turnOnLed(0);
	} else {
		turnOffLed(0);
	}
	if (tick<led1) {
		turnOnLed(1);
	} else {
		turnOffLed(1);
	}
	tick++;
	if (tick==period) tick=0;
}
