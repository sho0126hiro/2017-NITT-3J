#include <stdio.h>
#define N 100
#define ooo printf("%s %d\n",__FUNCTION__,__LINE__);
#define ppp printf("right=%d  left=%d\n",left,right);
/*関数宣言*********************************************************************/
void Display(int number[]);
void quick(int d[],int a,int b);
/*main*************************************************************************/
int main(){

	FILE *fp;
	int number[N];
	int i;
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
	int pivot=0,tmp,tmp2;
	int l=left,r=right;//保存
	if(left==right)return;
	pivot=d[left];
	while(left<right){
		while(d[left]<=pivot)left++;
		if(left!=right){
			d[right]=d[left];
			left++;
		}
		while(d[right]>=pivot)right--;
		if(left!=right){
			d[left]=d[right];
			right--;
		}
	}
	d[left]=pivot;
	pivot=left;
	left=l;
	right=r;
	if(left>pivot)quick(d,left,pivot-1);
	if(right>pivot)quick(d,pivot+1,right);
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

