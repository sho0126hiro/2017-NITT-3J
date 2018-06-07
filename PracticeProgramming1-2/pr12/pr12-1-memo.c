/* ナップザック問題（動的計画法による解法） */

/*
==memo==
実行はgcc
a x(ナップザックのサイズ).exe
で実行

*/

#include<stdio.h>
#include<stdlib.h>

/* 配列size、valueはそれぞれ荷物の大きさと価値を表わしている
 * 同じ添え字同士が対応している(例：荷物0の大きさはsize[0]、価値はvalue[0]）。
 */

/* 荷物の大きさ */
	int size[] = {2, 3, 5, 7, 9, 15};
	
/* 荷物の価値 */
	int value[] = {2, 4, 7, 11, 14, 24};
	
/* 荷物の種類の数 */
	#define AS (sizeof(size)/sizeof(size[0]))
	
/* ナップザックの大きさの上限 */
	#define MAX_M   200

void DynamicProgramming(int N, int Nsize[], int Nvalue[]){
	int i,j;
		
	/* 現時点でナップザックに詰め込んだ荷物の価値の合計 */
	int total[MAX_M];
	
	/* 最後に選んだ荷物 */
	int choice[MAX_M];
	
	/* 荷物iを入れた時の価値の合計 */
	int repack_total;
	
	/* 配列をクリアしておく */
	for(i=0;i<=N;i++){
		total[i] = 0;
		choice[i] = -1;
	}
	/* 荷物 i = 0~AS までを考慮に入れる */
	for(i=0;i<AS;i++){
		/* 大きさj(=Nsize[i])のナップザックに対して、荷物を詰め込んでみる */
		//repack_total=0;
		for(j=0;j<=N;j++){/*j:ナップザックのサイズ*/
			if(Nsize[i] <= j){
				/* 	もし荷物iを入れたとすると、価値の合計はいくらになるかを計算して、
					変数repack_totalに格納 */				
				repack_total = total[j-Nsize[i]]+Nvalue[i];
				/*
				価値の合計（上の式の意味）は講義資料のPDFに詳細が書いてある
				（https://nittc.tokyo-ct.ac.jp/usr/kitakosi/LEE/PracProgI/documents/Pr12/DP.pdf）
				6ページ目
				「０ を取りだして１を入れる場合 ・・・ 大きさ x （４）－ ３の 時の価値（０）
				に荷物１を加えた時の価値（４）をプラスする
				→ 価値は４、最後に入れた荷物は１」
				*/
				if(repack_total > total[j]){
				/* 荷物iを入れた方が(入れないより)価値が大きくなるのなら、荷物iを入れる */
					total[j]=repack_total;
					/*repack_totalは荷物iを入れた時の合計の価値が入っているから、
					価値を更新する*/
					choice[j]=i;
				}
			}
		}
		/* 配列total、choiceの中身を表示する */
		printf("i = %d\n",i);
		printf("choice = ");
		for(j=0;j<=N;j++)
			printf("%2d ",choice[j]);
		printf("\n");
		
	}
	i=N;
	/* どの荷物をナップザックに入れたかを表示する */
	while(choice[i] != -1){
		printf("品物 %d （価値%d）を詰め込む\n", choice[i],Nvalue[choice[i]]);
		i = i - Nsize[choice[i]];
	}
	printf("価値の合計 = %d\n",total[N]);
}

int main(int argc, char *argv[]){

	/* ナップザックの大きさ */
	int m;
	
	/* 引数の数が誤っていないか、ナップザックの大きさが上限を超えていないか
	   判定（適切な引数の数、もしくは値が設定されていない場合、再度入力を求める）
	*/
	/* コマンド引数からナップザックの大きさを得る
		   argv[0]:File name(a)/argv[1]:引数（a y.exeのy)
	 */
	m = atoi(argv[1]);
	while(m>MAX_M || m==0){
		printf("引数が設定されていないか、上限を超えています。\n（ナップザックのサイズの上限は200)\n再度入力してください。＞");
		scanf("%d",&m);
	}
	printf("Size of knapsack is %d\n",m);
	
	DynamicProgramming(m,size,value);
	
	return 0;
}