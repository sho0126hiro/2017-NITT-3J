/**********************************************************
�}�U�[�{�[�h��8�r�b�g�X�C�b�`�ɂ����LED��ON-OFF���s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void waitmsec(int msec)
/*mesc�ԂȂɂ����Ȃ����ԉ҂��֐�*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190�͎����ɂ���ċ��߂��l 25MHz�쓮*/
	}
}

main()
{
	initLed();
	P2.DDR=0;
	P2.PCR.BYTE=0xff;
	while(1) {
		if(check8BitSW(1)) { /*8bitSW��1��ON�̎�*/
			while(1){
				turnOnLed(0);
				turnOnLed(1);
				waitmsec(500);
				turnOffLed(0);
				turnOffLed(1);
				waitmsec(500);
				if(!check8BitSW(1))break;
			}
		} else { /*8bitSW��1��OFF�̎�*/
			while(1){
				turnOnLed(0);
				turnOnLed(1);
				waitmsec(250);
				turnOffLed(0);
				turnOffLed(1);
				waitmsec(250);
				if(check8BitSW(1))break;
			}
		}
	}
}