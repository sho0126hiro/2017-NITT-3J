/*bitperation 改良版版*/

/**********************************************************
ビット演算
SCI1へ出力，WINDOWSのHyperTerminalなどで受信できる。
ただし，設定は
38400baud, Async, 8bit , NoParity, stop1
**********************************************************/

#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	short int x,y,z,a;
	unsigned short int u;
	initSCI1(); /*シリアル通信ユニット　SCI-ch1の初期化*/
	SCI1_printf("Hello. How are you?\n"); /*printfと同様*/
	SCI1_printf("Let's make an bit operation\n");
	/*a=-1024;*/
	/*u=-1024;*/
	while (1) {
		x=SCI1_getInt("the first  number = ");
		y=SCI1_getInt("the second number = ");
		a=SCI1_getInt("a = ");
		u=SCI1_getInt("u = ");
		z=x&y;
		SCI1_printf("x=%b [%d] y=%b [%d] z=x&y=%b [%d]\n",x,x,y,y,z);
		z=x|y;
		SCI1_printf("x=%b [%d] y=%b [%d] z=x|y=%b [%d]\n",x,x,y,y,z,z);
		z=x^y;
		SCI1_printf("x=%b [%d] y=%b [%d] z=x^y=%b [%d]\n",x,x,y,y,z,z);
		z=x>>3;
		SCI1_printf("x=%b [%d] z=x>>3=%b [%d]\n",x,x,z,z);
		z=y<<3;
		SCI1_printf("y=%b [%d] z=y<<3=%b [%d]\n",y,y,z,z);
		
		SCI1_printf("\n以下課題用\n");
		z=a>>3;
		SCI1_printf("a=%b [%d] z=a>>3=%b [%d]\n",a,a,z,z);
		z=u>>3;
		SCI1_printf("a=%b [%d] z=a>>3=%b [%d]\n",u,u,z,z);
	}
}

/*実行結果**

Hello. How are you?
Let's make an bit operation
the first  number = 12
the second number = 65
a = -1024
u = -1024
x=1100 [12] y=1000001 [65] z=x&y=0 [0]
x=1100 [12] y=1000001 [65] z=x|y=1001101 [77]
x=1100 [12] y=1000001 [65] z=x^y=1001101 [77]
x=1100 [12] z=x>>3=1 [1]
y=1000001 [65] z=y<<3=1000001000 [520]

以下課題用
a=1111110000000000 [-1024] z=a>>3=1111111110000000 [-128]
a=1111110000000000 [-1024] z=a>>3=1111110000000 [8064]

*/
