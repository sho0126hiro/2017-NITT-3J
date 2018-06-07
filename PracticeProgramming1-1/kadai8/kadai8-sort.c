#include <stdio.h>
#define N 100

void Bubble(int number[]);
void Exchange(int number[],int i,int j);

int main(){
	FILE *fp,*fp2;
	int number[N],i;
	
	fp=fopen("sample3.txt","r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	fp2=fopen("sortsample3.txt","w");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	
	for(i=0;i<100;i++){
		fscanf(fp,"%d",&number[i]);
	}
	fclose(fp);
	Bubble(number);
	for(i=0;i<N;i++){
		fprintf(fp2,"%d\n",number[i]);
	}
	return 0;
}
void Bubble(int number[N]){
	int i,j;
	for(i=N;i>0;i--){
		for(j=0;j<i-1;j++){
			if(number[j]>number[j+1]){
				Exchange(number,j,j+1);
			}
		}
	}
}
void Exchange(int number[],int i,int j){
	int tmp;
	tmp=      number[i];
	number[i]=number[j];
	number[j]=tmp;
}
