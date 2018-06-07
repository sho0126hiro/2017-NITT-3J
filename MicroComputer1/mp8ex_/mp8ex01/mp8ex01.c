/**********************************************************
���荞�݂�p�������v�@�N��������̌o�ߎ��ԁm�b�n��
SCI1�֏o�́CWINDOWS��HyperTerminal�ȂǂŎ�M�ł���B
�������C�ݒ��
38400baud, Async, 8bit , NoParity, stop1
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

volatile long int time=0;/*�����i1/100sec�ŃJ�E���g�j��ۑ�����ϐ�*/

volatile int countup=0;/*���v�𓮂������~�߂邩���R���g���[������ϐ�*/

main()
{
	long int time1;
	unsigned int t1,t2;
	char ch;
	initSCI1(); /*SCI-ch1�̏�����*/
	initTimer1Int(1000); /*ITUch1�̃C���^�[�o���^�C�}�������ݒ�*/
	                     /*�P�ʃ�s�Ȃ̂ŁC���Ԋ��荞��1msec*/
	E_INT();        /*CPU���荞�݋���*/
	startTimer1();  /*ITUch1�^�C�}�X�^�[�g*/
	while(1) {
		ch=SCI1_chkgetChar(); /*�����ɖ߂��Ă���*/
		if (ch=='a') countup=1;/*A�������ꂽ��^�C�}�[�X�^�[�g*/
		else if (ch=='b') countup=0;/*B�������ꂽ��^�C�}�[�X�g�b�v*/
		else if (ch=='c') time=0;/*C�������ꂽ�烊�Z�b�g*/
		time1=time; /*�\���̓r���ŕϐ�time���ύX���ꂽ�Ƃ��̑΍�*/
		SCI1_printf("%4ld.%02ld\r",time1/1000,time1%1000); 
		SCI1_printf("%d\r",time1);
	}
}

#pragma asm
	.SECTION    MYVEC, DATA, LOCATE=H'000070
	.ORG        H'000070  ;IMIA1
	.DATA.L     _TimerIntFunc
	.SECTION    P,CODE,ALIGN=2 ;�����Y��Ă͂����Ȃ�
#pragma endasm

#pragma interrupt (TimerIntFunc)
void TimerIntFunc() /*�C���^�[�o���^�C�}���荞�݃��[�`��*/
{
	time+=countup;/*countup��1�̂Ƃ�time�ɉ��Z�����*/
	clearTimer1Flag();  /*ITUch1�^�C�}�t���O�̃N���A �Y��Ȃ�����*/
}

