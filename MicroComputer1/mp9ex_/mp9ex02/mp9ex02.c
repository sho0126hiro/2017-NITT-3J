#include <3048fone.h>
#include "h8_3048fone.h"

volatile int count1 = -1;/*LED0�p�J�E���^�@-1�̎��͋x�~��*/
volatile int count2 = -1;/*LED1�p�J�E���^�@-1�̎��͋x�~��*/
volatile int count3 = -1;/*LED1�p�J�E���^�@-1�̎��͋x�~��*/
volatile int cmdstertptr = -1;/*������\���J�n�ʒu�w��*/
const char hello[] = "                Hello, everyone!                  ";

main()
{
	int j;
	initSCI1();
	initLed();
	initPushSW();/*PushSW�̏�����*/
	initTimer1Int(10000); /*���Ԋ��荞��10000��sec=10msec ch1�g�p*/
	E_INT();        /*CPU���荞�݋���*/
	startTimer1();  /*���Ԋ��荞�݃^�C�}�X�^�[�gch1*/
	while (1) {
		if ((count1 == -1 || 50<count1) && checkPushSW(0) == 1) {
			count1 = 0;
			turnOnLed(0);
		}
		else if (100 < count1 && count1 <= 200) { /*100�J�E���g��1�b�o��*/
			turnOffLed(0);
		}
		else if (200 < count1 && count1 <= 300) { /*200�J�E���g��2�b�o��*/
			turnOnLed(0);
		}
		else if (300 < count1) { /*300�J�E���g��3�b�o��*/
			count1 = -1;
			turnOffLed(0);
		}

		if ((count2 == -1 || 50<count2) && checkPushSW(1) == 1) {
			count2 = 0;
			turnOnLed(1);
		}
		else if (100 < count2 && count2 <= 200) { /*100�J�E���g��1�b�o��*/
			turnOffLed(1);
		}
		else if (200 < count2 && count2 <= 300) { /*200�J�E���g��2�b�o��*/
			turnOnLed(1);
		}
		else if (300 < count2) { /*300�J�E���g��3�b�o��*/
			count2 = -1;
			turnOffLed(1);
		}

		if ((count3<0 || 10<count3) && checkPushSW(2) == 1) {
			count3 = 0;
			cmdstertptr = 0;
		}
		if (0 <= cmdstertptr) {
			SCI1_printf("<");
			for (j = 0; j < 16; j++) {
				SCI1_printf("%c", hello[cmdstertptr + j]);
			}
			SCI1_printf(">\r");
			if (cmdstertptr == 34) {/*34+16�ŕ\�������*/
				count3 = -1;
			}
			cmdstertptr = -1;
		}
	}
}

#pragma asm
	.SECTION    MYVEC, DATA, LOCATE = H'000070
	.ORG        H'000070  ;IMIA1
	.DATA.L     _TimerIntFunc
	.SECTION    P, CODE, ALIGN = 2; �����Y��Ă͂����Ȃ�
#pragma endasm

#pragma interrupt (TimerIntFunc)
void TimerIntFunc() /*�^�C�}���荞�݃��[�`��*/
{
	static int tick = 0;
	clearTimer1Flag();  /*�^�C�}�X�e�[�^�X�t���O�̃N���A �Y��Ȃ�����*/
	if (count1 != -1) count1++;
	if (count2 != -1) count2++;
	if (count3 != -1) count3++;
	if (count3 % 10 == 0) {
		cmdstertptr = count3 / 10;/*0.1�b���Ƃɑ�����*/
	}
}
