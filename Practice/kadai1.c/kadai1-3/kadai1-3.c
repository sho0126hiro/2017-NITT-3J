#include <stdio.h>

int main(){
	FILE *fp;
	int number[100];
	int i,j;
	//�t�@�C���̓ǂݍ���
	fp=fopen("sample.txt","r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	
	for(i=0;i<100;i++){
		fscanf(fp,"%d",&number[i]);
	}
	fclose(fp);
	//�ǂݍ��ݏI���
	
	//�\�[�g�J�n
	
	int next;
	
	for(i=1;i<100;i++){
		next=number[i];
		for(j=i;j>=1 && number[j-1]>next;j--){
			number[j]=number[j-1];
		}
		number[j]=next;
	}
	
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			printf("%3d",number[10*i+j]);
		}
		printf("\n");
	}
	
	return 0;
}
	
