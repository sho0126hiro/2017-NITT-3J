#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define ooo printf("%s %d\n",__FUNCTION__,__LINE__);
#define ppp printf("right=%d  left=%d\n",left,right);
/*関数宣言*********************************************************************/
void Display(int number[]);
void quick(int d[],int a,int b);
/*main*************************************************************************/
int main(){

	FILE *fp;
	int number[N]={0};
	int i;
	time_t t;
	srand((unsigned)time(&t));//rand初期化
	for(i=0;i<N;i++){
		number[i]=rand()%100;
	}
	printf("==========クイックソート==========\n");
	Display(number);
	printf("\n\n");
	quick(number,0,N);
	Display(number);
	return 0;
}
/*クイックソート***************************************************************/
void quick(int d[],int left,int right){
	int l=left,r=right;
	int pivot,tmp,tmp2;
	if(left==right)return;
	pivot=d[left];
	while(1){
		while(d[left]<pivot)left++;
		while(d[right]>pivot)right--;
		if(left>right)break;
		tmp  = d[left];
		d[left] = d[right];
		d[right] = tmp;
		right--;
		left++;
	}
	d[left] =pivot;
	pivot=left;
	if(l<pivot)quick(d,l,pivot-1);
	if(r>pivot)quick(d,pivot+1,r);
}
/*表示*************************************************************************/
void Display(int number[]){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			printf("%3d",number[10*i+j]);
		}
		printf("\n");
	}
}
/*****************************************************************************/

