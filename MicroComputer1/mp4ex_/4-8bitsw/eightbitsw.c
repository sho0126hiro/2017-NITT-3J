/**********************************************************
�}�U�[�{�[�h��8�r�b�g�X�C�b�`�ɂ����LED��ON-OFF���s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	initLed();
	P2.DDR=0;
	P2.PCR.BYTE=0xff;
	while(1) {
		if (P2.DR.BIT.B0==0) { /*8bitSW��0��ON�̎�*/
			turnOnLed(0);
			turnOnLed(1);
		} else if (P2.DR.BIT.B1==0) { /*8bitSW��1��ON�̎�*/
			turnOnLed(0);
			turnOffLed(1);
		} else if (P2.DR.BIT.B2==0) { /*8bitSW��2��ON�̎�*/
			turnOffLed(0);
			turnOnLed(1);
		} else {
			turnOffLed(0);
			turnOffLed(1);
		}
	}
}