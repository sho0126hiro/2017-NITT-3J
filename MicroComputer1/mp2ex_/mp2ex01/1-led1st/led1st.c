/*  マザーボード上のLEDの1秒ごとのON-OFFを行う  */

#include <3048fone.h>
void waitmsec(int msec)
/*mesc間なにもしない時間稼ぎ関数*/
{
    int i,j;
    for (i=0;i<msec;i++) {
        for (j=0;j<4190;j++);    /*4190は実測によって求めた値 25MHz駆動*/
    }
}

main()
{
    /*P5の下位4ビットを出力に設定*/
    /* P5のDDRの下位4ビットに1を与えるとこの設定になる*/
    /*DDRとはDataDirectionRegister(データ方向設定レジスタ)*/
    P5.DDR =  0x0f;     /*0xc0 = 11000000(二進数)*/
    while(1) {/*これは無限ループ*/
        /*LED0をONにする  P5のDRの第0ビットを1にする*/
        /*DRとはDataRegister(データレジスタ)*/
        P5.DR.BIT.B0=1;
        /*LED1をOFFにする  P5のDRの第1ビットを0にする*/
        P5.DR.BIT.B1=0;
        /*LED2をONにする   P5のDRの第2ビットを1にする*/
        P5.DR.BIT.B2=1;
        /*LED2をOFFにする  P5のDRの第3ビットを0にする*/
        P5.DR.BIT.B3=0;
        waitmsec(1000);/*1000msecの間なにもしない*/
        /*LED0をOFFにする  P5のDRの第0ビットを0にする*/
        P5.DR.BIT.B0=0;
        /*LED1をONにする   P5のDRの第1ビットを1にする*/
        P5.DR.BIT.B1=1;
        /*LED2をOFFにする  P5のDRの第2ビットを0にする*/
        P5.DR.BIT.B2=0;
        /*LED3をONにする   P5のDRの第3ビットを1にする*/
        P5.DR.BIT.B3=1;
        waitmsec(1000);
    }
} 

