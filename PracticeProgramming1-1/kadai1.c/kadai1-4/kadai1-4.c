#include <stdio.h>
#define NUMBER 100 //�v�f��NUMBER��100

/*�֐��錾*********************************************************************/
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
	//�t�@�C���̓ǂݍ���
	
	printf("�ǂݍ��ރt�@�C��������͂��Ă���������");
	scanf("%s",filename);
	sprintf(file,"%s.txt",filename);
	fp=fopen(file,"r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(int i=0;i<NUMBER;i++)fscanf(fp,"%d",&number[i]);
	fclose(fp);
	
	//�ǂݍ��ݏI���
	
	int x,y;
	
	printf("�\�[�g���@��I�����Ă��������i��������́j\n1.�o�u���\�[�g\n2�D�I���\�[�g\n3�D�}���\�[�g\n>>>>>");
	scanf("%d",&x);
	printf("�\�[�g����I�����Ă��������i��������́j\n1.����\n2.�~��\n>>>>>");
	scanf("%d",&y);
	printf("***************�\�[�g�O***************\n\n");
	Display(number);
	if(x==1){//�o�u���\�[�g
		if(y==1){
			Bubble(number);
		}else if(y==2){//�~��
			Bubble(number);
			Reverse(number);
		}
	}else if(x==2){//�I���\�[�g
		if(y==1){
			Selection(number);
		}else if(y==2){//�~��
			Selection(number);
			Reverse(number);
		}
	}else if(x==3){//�}���\�[�g
		if(y==1){
			Insertion(number);
		}else if(y==2){//�~��
			Insertion(number);
			Reverse(number);
		}
	}else{
	//���̑��̐��������͂��ꂽ�ꍇ
		printf("ERROR");
		return 0;
	}
	
	printf("\n\n***************�\�[�g��***************\n\n");
	Display(number);
	
	//�t�@�C���ւ̏o��
	printf("\n�����o���t�@�C���̊g���q����́�");
	scanf("%s",extension);
	sprintf(file,"%s.%s",filename,extension);
	fp2=fopen(file,"w");
	if(fp2==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(int i=0;i<NUMBER;i++)fprintf(fp2,"%d\n",number[i]);
	fclose(fp2);
	printf("\n�����o������");
	//�o�͏I���
	return 0;
}
/*�o�u���\�[�g************************************************************/
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
/*�I���\�[�g************************************************************/
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
/*�}���\�[�g************************************************************/
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
/*�t�����o��************************************************************/
void Reverse(int number[]){
	for(int i=0;i<NUMBER/2;i++){
		int x=number[i];
		number[i]=number[NUMBER-i-1];
		number[NUMBER-i-1]=x;
	}
}
/*�\��*****************************************************************/
void Display(int number[]){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			printf("%3d",number[10*i+j]);
		}
		printf("\n");
	}
}


