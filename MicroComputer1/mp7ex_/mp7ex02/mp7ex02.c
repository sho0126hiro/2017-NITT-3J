#include <3048fone.h>
#include "h8_3048fone.h"
volatile int P0count=0; /*P0�̃J�E���^*/
volatile int P1count=0; /*P0�̃J�E���^*/
volatile int P2count=0; /*P0�̃J�E���^*/
volatile int P3count=0; /*P0�̃J�E���^*/
volatile int request=0; /*���荞�݃��[�`������̕\���v��*/

main(){
    int menu;
    initSCI1();
    initPushSW();
    
    initTimer1Int(1000);
    E_INT();
    startTimer1();
	while (1) {
	
		if(request) {     /*if (request!=0) {�Ɠ����Ӗ�*/
			SCI1_printf("SW0->[%3d] SW1->[%3d] SW2->[%3d] SW3->[%3d]\n",P0count,P1count,P2count,P3count);
			request = 0;
		}
	}
}

#pragma asm
    .SECTION    MYVEC, DATA, LOCATE=H'000070
    .ORG        H'000070  ;IMIA1
    .DATA.L     _TimerIntFunc
    .SECTION    P,CODE,ALIGN=2 ;�����Y��Ă͂����Ȃ�
#pragma endasm

void TimerIntFunc() /*�^�C�}���荞�݃��[�`��*/
{
	int sw;
	static int status = 0; /*SW0�̏�� 0:������Ă��Ȃ� 1:������Ă���*/
	/*
	status��1�ɂȂ�₷���C0�ɂȂ�ɂ����悤�ɂ���B�i�q�X�e���V�X�j
	�������邱�ƂŃ`���^�����O�΍�ɂȂ�B
	�X�C�b�`�������ꂽ�璼����1�ɂ���
	�X�C�b�`�������ꂽ��Ԃ�10��i10msec�ɂȂ�j��������0�ɂ���
	���̊��荞�݊֐���1msec���ɋN������̂ŁC10��̎��s��10msec�o�߂������ƂɂȂ�
	*/
	const int Nantichatter = 10;
	static int statuscnt = 0;  /*�X�C�b�`�������ꂽ��Ԃ𐔂���ϐ�*/
	clearTimer1Flag();  /*�^�C�}�X�e�[�^�X�t���O�̃N���A �Y��Ȃ�����*/
	sw = getPushSW();
	if (status == 0) {
		if ((sw&1) == 1) {
			status = 1;
			P0count++;
			request = 1;
		}
		if ((sw&2) == 2) {
			status = 1;
			P1count++;
			request = 1;
		}
		if ((sw&4) == 4) {
			status = 1;
			P2count++;
			request = 1;
		}
		if ((sw&8) == 8) {
			status = 1;
			P3count++;
			request = 1;
		}
	} else { /*status == 1*/
		if ((sw&1) == 1 || (sw&2) == 2 || (sw&4) == 4 || (sw&8) == 8 ) {
			statuscnt = 0;
		} else {
			statuscnt++;
			if (Nantichatter < statuscnt) {
				status = 0;
			}
		}
	}
}
