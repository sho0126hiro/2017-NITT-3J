#include <stdio.h>
#define N1 1000000 //sample1
#define N2 10000000//sample2
/*関数宣言*********************************************************************/
void Display(int number[]);
void msort(int data[],int left,int right);
/*main*************************************************************************/
int main(){

	FILE *fp;
	int number1[N1]={0};
	//ファイルの読み込み
	fp=fopen("sample1.txt","r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(int i=0;i<N1;i++)fscanf(fp,"%d",&number1[i]);
	fclose(fp);
	//読み込み終わり
	//printf("ソート前\n\n\n\n");
	//Display(number1);	
	msort(number1,0,N1-1);
	printf("ソート後\n\n");
	Display(number1);
	return 0;
	
	/*
	FILE *fp;
	int number2[N2]={0};
	//ファイルの読み込み
	fp=fopen("sample2.txt","r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(int i=0;i<N2;i++)fscanf(fp,"%d",&number[i]);
	fclose(fp);
	//読み込み終わり
	printf("ソート前\n\n\n\n");
	Display(number2);
	msort(number2,0,N2-1);
	Display(number2);
	return 0;
	*/
}
/*マージソート***************************************************************/
void msort(int data[],int left,int right){
	int m,i,j,k;
	static int x[N1];
	if(left>=right)return;
	m=(left+right)/2;
	msort(data,left,m);
	msort(data,m+1,right);

	for(i=left;i<=m;i++)x[i]=data[i];
	j=right;
	for(i=m+1;i<=right;i++){
		x[i]=data[j];
		j--;
	}
	i=left;
	j=right;
	for(k=left;k<=right;k++){
		if(x[i]<=x[j]){
			data[k]=x[i];
			i++;
		}else{
			data[k]=x[j];
			j--;
		}
	}
}
/*
void msort(int data[],int left,int right){
	int m,i,j,k;
	static int x[N2];
	if(left>=right)return;
	m=(left+right)/2;
	msort(data,left,m);
	msort(data,m+1,right);

	for(i=left;i<=m;i++)x[i]=data[i];
	j=right;
	for(i=m+1;i<=right;i++){
		x[i]=data[j];
		j--;
	}
	i=left;
	j=right;
	for(k=left;k<=right;k++){
		if(x[i]<=x[j]){
			data[k]=x[i];
			i++;
		}else{
			data[k]=x[j];
			j--;
		}
	}
}
*/
/*表示*****************************************************************/
void Display(int number[]){
	for(int j=0;j<N1;j++){
			printf("[%8d]:%11d\n",j+1,number[j]);
	}
	
	/*
	for(int j=0;j<N2;j++){
			printf("[%8d]:%13d\n",j+1,number[j]);
	}
	*/
}