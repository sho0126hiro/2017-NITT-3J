/**********************************************************
�v�b�V���X�C�b�`�Ǝ��Ԋ��荞�݂ɂ����LED��PWM������s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

volatile int led0,led1;
const int high=10; /*����10msec*/
const int mid_h=5;
const int mid_l=2;
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
			led0=mid_l;
			led1=0;
			if(checkPushSW(1)==1){/*sw1,0:ON*/
				led0=high;
				led1=0;
			}
		} else if (checkPushSW(1)==1) { /*PushSW0:OFF,PushSW1:ON*/
			led0=mid_h;
			led1=0;
		} else {/*sw0:off,sw1:0ff*/
			if(checkPushSW(2)==0 && checkPushSW(3)==0){/*all off*/
				led0=low;
				led1=low;
			}else{/*sw0,1=off,sw2or3=on*/
				led0=0;
				led1=1;
			}
		}
		if (checkPushSW(2)==1) { /*PushSW��2��ON�̎�*/
			led1=mid_l;
			led0=0;
			if(checkPushSW(3)==1){/*2:on,3:on*/
				led1=high;
				led0=0;
			}
		}else if(checkPushSW(3)==1){
				led1=mid_h;
				led0=0;
		} else {
			led1=0;
			led0=0;
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
	if (tick==high) tick=0;
}
