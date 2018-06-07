#include <stdio.h>

int main(){
	FILE *fp;
	int number[100];
	int i,j,x;
	//ファイルの読み込み
	fp=fopen("sample.txt","r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(i=0;i<100;i++){
		fscanf(fp,"%d",&number[i]);
	}
	fclose(fp);
	//読み込み終わり
	//ソート開始
	
	int N=100,k;//N:データ数
	int left=0,right=N-1;
	
	while(right>left){
		for(j=left;j<right;j++){
		//left=>right
			if(number[j]>number[j+1]){
				//並び替え
				x=number[j];
				number[j]=number[j+1];
				number[j+1]=x;
				k=j;
			}
		}
		right=k;
		for(j=right;j>left;j--){
		//right=>left
			if(number[j]<number[j-1]){
				//並び替え
				x=number[j];
				number[j]=number[j-1];
				number[j-1]=x;
				k=j;
			}
		}
		left=k;
	}

	//画面出力
	printf("========小さい順=======\n");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			printf("%3d",number[10*i+j]);
		}
		printf("\n");
	}
	return 0;
}

