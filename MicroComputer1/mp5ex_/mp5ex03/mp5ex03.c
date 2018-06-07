#include <3048fone.h>
#include "h8_3048fone.h"

void pushreleaseSW1(void)
/*�v�b�V���X�C�b�`���������܂ő҂��āC*/
/*���̌㗣�����܂ő҂֐�			*/
{
	while (checkPushSW(0)==0);
	while (checkPushSW(0)==1);
}

void pushreleaseSW2(void)
/*�v�b�V���X�C�b�`���������܂ő҂��āC*/
/*���̌㊮�S�ɗ������܂ő҂֐�		*/
{
	int status=1;
	const int Nantichatter=5000;
	int statuscnt=0;
	while (checkPushSW(0)==0);
	while (status==1) {
		if (checkPushSW(0)==1) {
			statuscnt=0;
		} else {
			statuscnt++;
			if (Nantichatter<statuscnt) {
				status=0;
			}
		}
	}
}

main()
{
	initLed();
	initPushSW();
	while(1) {
		turnOnLed(0);
		pushreleaseSW2();
		/*pushreleaseSW1();*/
		turnOffLed(0);
		pushreleaseSW2();
		/*pushreleaseSW1();*/
	}
}

