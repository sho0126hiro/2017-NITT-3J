void waitmsec(int msec)
/*msec�ԂȂɂ����Ȃ����ԉ҂��֐�*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++); /*4190�͎����ɂ���ċ��߂��l 25MHz�쓮*/
	}
}

main()
{
	/* P5�̉���2�r�b�g���o�͂ɐݒ� */
	/* P5�̓��o�͐ݒ蕔�̉���2�r�b�g��1��^����Ƃ��̐ݒ�ɂȂ�*/
	*(unsigned char *)0xfffc8 = 0x3; /*0x3 �� 00000011(��i�@�\�L)*/

	while(1) {/*����͖������[�v*/
		/*P5�̉��ʂQ�r�b�g��01(��i�@�\�L)���o�͂���*/
		*(unsigned char *)0xfffca = 0x01; /*0x01 �� 00000001(��i�@�\�L)*/

		waitmsec(1000);/*1000msec�̊ԂȂɂ����Ȃ�*/

		/*P5�̉��ʂQ�r�b�g��10(��i�@�\�L)���o�͂���*/
		*(unsigned char *)0xfffca = 0x02; /*0x02 �� 00000010(��i�@�\�L)*/

		waitmsec(1000);
	}
} 
