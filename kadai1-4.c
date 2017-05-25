#include <stdio.h>
#define NUMBER 100 //要素数NUMBERは100

/*関数宣言*********************************************************************/
void Bubble(int number[]);
void Selection(int number[]);
void Insertion(int number[]);
void Reverse(int number[]);
void Display(int number[]);

/*main*************************************************************************/
int main(){

	FILE *fp;
	FILE *fp2;
	int number[NUMBER];
	char filename[200];
	char file[200];
	char extension[200];
	//ファイルの読み込み
	
	printf("読み込むファイル名を入力してください＞");
	scanf("%s",filename);
	sprintf(file,"%s.txt",filename);
	fp=fopen(file,"r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(int i=0;i<NUMBER;i++)fscanf(fp,"%d",&number[i]);
	fclose(fp);
	
	//読み込み終わり
	
	int x,y;
	
	printf("ソート方法を選択してください（数字を入力）\n1.バブルソート\n2．選択ソート\n3．挿入ソート\n>>>>>");
	scanf("%d",&x);
	printf("ソート順を選択してください（数字を入力）\n1.昇順\n2.降順\n>>>>>");
	scanf("%d",&y);
	printf("***************ソート前***************\n\n");
	Display(number);
	if(x==1){//バブルソート
		if(y==1){
			Bubble(number);
		}else if(y==2){//降順
			Bubble(number);
			Reverse(number);
		}
	}else if(x==2){//選択ソート
		if(y==1){
			Selection(number);
		}else if(y==2){//降順
			Selection(number);
			Reverse(number);
		}
	}else if(x==3){//挿入ソート
		if(y==1){
			Insertion(number);
		}else if(y==2){//降順
			Insertion(number);
			Reverse(number);
		}
	}else{
	//その他の数字が入力された場合
		printf("ERROR");
		return 0;
	}
	
	printf("\n\n***************ソート後***************\n\n");
	Display(number);
	
	//ファイルへの出力
	printf("\n書き出しファイルの拡張子を入力＞");
	scanf("%s",extension);
	sprintf(file,"%s.%s",filename,extension);
	fp2=fopen(file,"w");
	if(fp2==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(int i=0;i<NUMBER;i++)fprintf(fp2,"%d\n",number[i]);
	fclose(fp2);
	printf("\n書き出し完了");
	//出力終わり
	return 0;
}
/*バブルソート************************************************************/
void Bubble(int number[]){
	int x,i,j;
	for(i=NUMBER;i>0;i--){
		for(j=0;j<i;j++){
			if(number[j]>number[j+1]){
				x=number[j];
				number[j]=number[j+1];
				number[j+1]=x;
			}
		}
	}
}
/*選択ソート************************************************************/
void Selection(int number[]){
	int a,i,j,min,x;
	for(i=0;i<NUMBER;i++){
		min=number[i];
		a=i;
		for(j=i+1;j<100;j++){
			if(number[j]<min){
				min=number[j];
				a=j;
			}
		}
		x=number[a];
		number[a]=number[i];
		number[i]=x;
	}
}
/*挿入ソート************************************************************/
void Insertion(int number[]){
	int i,j,next;
	for(i=1;i<NUMBER;i++){
		next=number[i];
		for(j=i;j>=1 && number[j-1]>next;j--){
			number[j]=number[j-1];
		}
		number[j]=next;
	}
}
/*逆順を出力************************************************************/
void Reverse(int number[]){
	for(int i=0;i<NUMBER/2;i++){
		int x=number[i];
		number[i]=number[NUMBER-i-1];
		number[NUMBER-i-1]=x;
	}
}
/*表示*****************************************************************/
void Display(int number[]){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			printf("%3d",number[10*i+j]);
		}
		printf("\n");
	}
}


