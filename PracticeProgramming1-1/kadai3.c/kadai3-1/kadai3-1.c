#include <stdio.h>
#define NUMBER 100//要素数
void Display(int []);

int main(){
	FILE *fp;
	int number[NUMBER];
	int i,j=0;
	//ファイルの読み込み
	fp=fopen("sample.txt","r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	
	for(i=0;i<NUMBER;i++){
		fscanf(fp,"%d",&number[i]);
	}
	fclose(fp);
	//読み込み終わり
	printf("	ソート前		\n");
	Display(number);
	int h,x;
	
	//最初の間隔h
	h=1;
	while(h<NUMBER){
		h=3*h+1;
		if(h>NUMBER){
			h=h/3;
			break;
		}
		//printf("H=%d\n",h);
	}
	//printf("H=%d\n",h);
	//シェルソート
	while(h>0){
		for(i=0;i<NUMBER;i++){
			j=i;
			x=number[i];
			while((j>=h) && (number[j-h]>x)){
				number[j]=number[j-h];
				j=j-h;
			}
			number[j]=x;
		}
		if(h/3!=0)h=h/3;
		else if(h==1)h=0;
		else h=1;
	}
	printf("	ソート後	\n");
	Display(number);
	return 0;
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
