/*2�i���ɕϊ����C1�̌��𐔂���*/

#include <3048fone.h>
#include "h8_3048fone.h"

int countOnes(short int value){
	short int mask;
	int count;
	while(value!=0){
		if(value&1)count++;
		value=((unsigned short int)value)>>1;
	}
	return count;
}

main()
{
	short int x,y;
	initSCI1(); /*�V���A���ʐM���j�b�g�@SCI-ch1�̏�����*/
	SCI1_printf("10�i����2�i���ɕϊ����C1�̌��𐔂��܂�\n"); /*printf�Ɠ��l*/
	while(1) {/*����͖������[�v*/
		x=SCI1_getInt("���l����́�");
		SCI1_printf("��i����%d��%b�ł��D\n",x,x);
		y=countOnes(x);
		SCI1_printf("1�̐���%d�ł����D\n",y);
	}
}
/*���s����

10�i����2�i���ɕϊ����C1�̌��𐔂��܂�
���l����́�3
��i����3��11�ł��D
1�̐���2�ł����D
���l����́�23
��i����23��10111�ł��D
1�̐���4�ł����D
���l����́�127
��i����127��1111111�ł��D
1�̐���7�ł����D
���l����́�1546
��i����1546��11000001010�ł��D
1�̐���4�ł����D
���l����́�-100
��i����-100��1111111110011100�ł��D
1�̐���12�ł����D
���l����́�-12

*/
