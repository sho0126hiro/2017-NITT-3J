#include <stdio.h>

int main(){
	int i,j,x;
	int number[15];
	for(i=0;i<10;i++){
		printf("���������=>");
		scanf("%d",&number[i]);
	}
	for(i=9;i>0;i--){
		for(j=0;j<i;j++){
			if(number[j]>number[j+1]){
				//���ёւ�
				x=number[j];
				number[j]=number[j+1];
				number[j+1]=x;
			}
		}
	}
	printf("========��������=======\n");
	for(i=0;i<10;i++){
		printf(" %d",number[i]);
	}
	return 0;
}

