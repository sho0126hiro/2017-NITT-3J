#include <3048fone.h>
#include "h8_3048fone.h"

volatile int count1=-1;/*LED0�p�J�E���^�@-1�̎��͋x�~��*/
volatile int count2=-1;/*LED1�p�J�E���^�@-1�̎��͋x�~��*/
volatile int count3=-1;

/*ON-OFF-ON-OFF*/

main()
{
	initLed();
	initPushSW();/*PushSW�̏�����*/
	initTimer1Int(10000); /*���Ԋ��荞��10000��sec=10msec ch1�g�p*/
	E_INT();        /*CPU���荞�݋���*/
	startTimer1();  /*���Ԋ��荞�݃^�C�}�X�^�[�gch1*/
	while(1) {
		if ((count1==-1 || 50<count1) && checkPushSW(0)==1) { /*0~1s , on*/
			count1=0;
			turnOnLed(0);
		} else if (100<count1 && count1<200) { /*count 1~2s,off*/
			turnOffLed(0);
		} else if (200<count1 && count1<300){ /*count 2~3s,on*/
			turnOnLed(0);
		} else if (300<count1){ /*Off*/
			count1=-1;
			turnOffLed(0);
		}
		if ((count2==-1 || 50<count2) && checkPushSW(1)==1) { /*0~1s , on*/
			count2=0;
			turnOnLed(1);
		} else if (100<count2 && count2<200) { /*count 1~2s,off*/
			turnOffLed(1);
		} else if (200<count2 && count2<300){/*count 2~3s,on*/
			turnOnLed(1);
		} else if (300<count2){ /*Off*/
			count2=-1;
			turnOffLed(1);
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
	if (count1!=-1) count1++;
	if (count2!=-1) count2++;
}