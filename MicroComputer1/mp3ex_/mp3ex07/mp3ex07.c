#include <3048fone.h>
#include "h8_3048fone.h"

void wait_m4sec(int m4_sec)
/*10^-4sec�Ŏw������ԂȂɂ����Ȃ����ԉ҂��֐�*/
/*���Ƃ���wait_m4sec(15);���ĂԂ�1.5msec��ɂ��̊֐�����߂�*/
{
	int i,j;
	for (i=0;i<m4_sec;i++) {
		for (j=0;j<419;j++); /*419�̍������l���Ă݂悤*/
	}
}

main()
{
	int i=2,j;
	initLed();
	while(1) {
		turnOnLed(0); /*LED0��ON*/
		for(j=0;j<400;j++){
			/*�f���[�e�B�[��2^i%*/
			turnOnLed(1); /*LED1��ON*/
			wait_m4sec(i);
			turnOffLed(1); /*LED1��OFF*/
			wait_m4sec(100-i);
		}
		if(i==64)i=2;
		else i=i*2;
	}
}
