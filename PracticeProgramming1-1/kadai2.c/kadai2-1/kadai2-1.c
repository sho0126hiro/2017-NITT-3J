#include <stdio.h>

int main(){
	FILE *fp;
	int number[100];
	int i,j,x;
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
	
	int N=100,k;//N:�f�[�^��
	int left=0,right=N-1;
	
	while(right>left){
		for(j=left;j<right;j++){
		//left=>right
			if(number[j]>number[j+1]){
				//���ёւ�
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
				//���ёւ�
				x=number[j];
				number[j]=number[j-1];
				number[j-1]=x;
				k=j;
			}
		}
		left=k;
	}

	//��ʏo��
	printf("========��������=======\n");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			printf("%3d",number[10*i+j]);
		}
		printf("\n");
	}
	return 0;
}

