/**********************************************************
�v�b�V���X�C�b�`�ɂ����LED��ON-OFF���s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	initLed();
	initPushSW();
	while(1) {
		if (checkPushSW(0)==1) { /*PushSW��0��ON�̎�*/
			turnOnLed(0);
			turnOffLed(1);
		} else if (checkPushSW(1)==1) { /*PushSW��1��ON�̎�*/
			turnOffLed(0);
			turnOnLed(1);
		} else {
			turnOffLed(0);
			turnOffLed(1);
		}
	}
}
