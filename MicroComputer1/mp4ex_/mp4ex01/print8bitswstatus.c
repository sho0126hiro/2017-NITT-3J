/**********************************************************
�}�U�[�{�[�h��8�r�b�g�X�C�b�`���Ȃ����Ă���P2�̊e�r�b�g��
���ڌ��Ă݂悤�B
�܂��C�֐�get8BitSW()������l�����Ă݂悤�B
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	unsigned char sw1,sw2;
	initLed();
	initSCI1();
	init8BitSW();/*8bitSW�̏�����*/
	while(1) {
		sw1=P2.DR.BYTE;
		sw2=get8BitSW();
		SCI1_printf("P2.DR.BYTE=%08b get8BitSW()=%08b\n",sw1,sw2);
	}
}
