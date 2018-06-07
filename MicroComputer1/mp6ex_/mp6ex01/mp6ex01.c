/**********************************************************
���Ԋ��荞�݂ɂ����LED��ON-OFF���s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	initLed();
	initTimer1Int(10000); /*���Ԋ��荞��10000��sec=10msec ITUch1�g�p*/
	E_INT();        /*CPU���荞�݋���*/
	startTimer1();  /*���Ԋ��荞�݃^�C�}�X�^�[�gch1*/
	while(1);       /*�Ȃɂ����Ȃ����[�v*/
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
	static int count=0;
	clearTimer1Flag();  /*�^�C�}�X�e�[�^�X�t���O�̃N���A �Y��Ȃ�����*/
	count++;
	if (count==50) {
		count=0;
		if (tick==1) {
			turnOnLed(0);
			turnOffLed(1);
		} else {
			turnOffLed(0);
			turnOnLed(1);
		}
		tick=1-tick;
	}
}
