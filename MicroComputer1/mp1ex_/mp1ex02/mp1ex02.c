/*2進数に変換し，1の個数を数える*/

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
	initSCI1(); /*シリアル通信ユニット　SCI-ch1の初期化*/
	SCI1_printf("10進数を2進数に変換し，1の個数を数えます\n"); /*printfと同様*/
	while(1) {/*これは無限ループ*/
		x=SCI1_getInt("数値を入力＞");
		SCI1_printf("二進数で%dは%bです．\n",x,x);
		y=countOnes(x);
		SCI1_printf("1の数は%d個でした．\n",y);
	}
}
/*実行結果

10進数を2進数に変換し，1の個数を数えます
数値を入力＞3
二進数で3は11です．
1の数は2個でした．
数値を入力＞23
二進数で23は10111です．
1の数は4個でした．
数値を入力＞127
二進数で127は1111111です．
1の数は7個でした．
数値を入力＞1546
二進数で1546は11000001010です．
1の数は4個でした．
数値を入力＞-100
二進数で-100は1111111110011100です．
1の数は12個でした．
数値を入力＞-12

*/
