#include <stdio.h>
#define N1 1000000//sample1
#define N2 10000000//sample2
/*関数宣言*********************************************************************/
void Display(int number[]);
void quick(int d[],int left,int right);
/*main*************************************************************************/
int main(){

	FILE *fp;
	int number1[N1]={0};
	//int number2[N2];
	
	//ファイルの読み込み
	fp=fopen("sample1.txt","r");
	//fp=fopen("sample2.txt","r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(int i=0;i<N1;i++)fscanf(fp,"%d",&number1[i]);
	//for(int i=0;i<N2;i++)fscanf(fp,"%d",&number[i]);
	fclose(fp);
	//読み込み終わり
	//printf("ソート前\n\n\n\n");
	//Display(number1);
	quick(number1,0,N1-1);
	//quick(number2,0,N2-1);
	printf("ソート後\n\n");
	Display(number1);
	//Display(number2);
	return 0;
}
/*クイックソート***************************************************************/
void quick(int d[],int left,int right){
	if(left>=right)return;
	int l,r;
	int pivot,tmp;
	l=left;
	r=right;
	pivot=d[left];
	
	while(1){
		while(d[left]<=pivot && left<right)left++;
		while(d[right]>pivot && left<right)right--;
		if(left>=right)break;
		tmp      = d[left];
		d[left]  = d[right];
		d[right] = tmp;
	}
	
	/*for(int i=0;i<N1;i++){
		//printf("%d:[%d]:%d  left=%d,right=%d,pivot=%d\n",__LINE__,i,d[i],left,right,pivot);
	}*/
	//printf("\n");
	left--;
	tmp=d[l];
	d[l]=d[left];
	d[left]=tmp;
	
	quick(d,l,left);
	quick(d,left+1,r);
}	
/*表示*****************************************************************/
void Display(int number[]){
	for(int j=0;j<N1;j++){
			printf("[%8d]:%11d\n",j+1,number[j]);
	}
}