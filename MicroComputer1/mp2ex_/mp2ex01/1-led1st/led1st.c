/*  �}�U�[�{�[�h���LED��1�b���Ƃ�ON-OFF���s��  */

#include <3048fone.h>
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
    /*P5�̉���4�r�b�g���o�͂ɐݒ�*/
    /* P5��DDR�̉���4�r�b�g��1��^����Ƃ��̐ݒ�ɂȂ�*/
    /*DDR�Ƃ�DataDirectionRegister(�f�[�^�����ݒ背�W�X�^)*/
    P5.DDR =  0x0f;     /*0xc0 = 11000000(��i��)*/
    while(1) {/*����͖������[�v*/
        /*LED0��ON�ɂ���  P5��DR�̑�0�r�b�g��1�ɂ���*/
        /*DR�Ƃ�DataRegister(�f�[�^���W�X�^)*/
        P5.DR.BIT.B0=1;
        /*LED1��OFF�ɂ���  P5��DR�̑�1�r�b�g��0�ɂ���*/
        P5.DR.BIT.B1=0;
        /*LED2��ON�ɂ���   P5��DR�̑�2�r�b�g��1�ɂ���*/
        P5.DR.BIT.B2=1;
        /*LED2��OFF�ɂ���  P5��DR�̑�3�r�b�g��0�ɂ���*/
        P5.DR.BIT.B3=0;
        waitmsec(1000);/*1000msec�̊ԂȂɂ����Ȃ�*/
        /*LED0��OFF�ɂ���  P5��DR�̑�0�r�b�g��0�ɂ���*/
        P5.DR.BIT.B0=0;
        /*LED1��ON�ɂ���   P5��DR�̑�1�r�b�g��1�ɂ���*/
        P5.DR.BIT.B1=1;
        /*LED2��OFF�ɂ���  P5��DR�̑�2�r�b�g��0�ɂ���*/
        P5.DR.BIT.B2=0;
        /*LED3��ON�ɂ���   P5��DR�̑�3�r�b�g��1�ɂ���*/
        P5.DR.BIT.B3=1;
        waitmsec(1000);
    }
} 

