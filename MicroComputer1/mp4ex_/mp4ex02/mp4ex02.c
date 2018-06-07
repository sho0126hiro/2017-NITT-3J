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
		if(check8BitSW(0)) { /*8bitSW��0��ON*/
			turnOnLed(0);
			turnOnLed(1);
			waitmsec(250);
			turnOffLed(0);
			turnOffLed(1);
			waitmsec(250);
		} else{/*8bitSW��0��OFF*/
			if(check8BitSW(1)){ /*8bitSW��0��OFF,8bitSW��1��ON*/
				turnOnLed(0);
				turnOnLed(1);
				waitmsec(500);
				turnOffLed(0);
				turnOffLed(1);
				waitmsec(500);
			}else{/*8bitSW��0��1��OFF*/
				if(check8BitSW(2)){/*8bitSW��0��1��OFF,8bitSW��2��ON*/
					turnOnLed(0);
					turnOnLed(1);
					waitmsec(1000);
					turnOffLed(0);
					turnOffLed(1);
					waitmsec(1000);
				}
			}
		}
		turnOffLed(0);
		turnOffLed(1);
	}
}