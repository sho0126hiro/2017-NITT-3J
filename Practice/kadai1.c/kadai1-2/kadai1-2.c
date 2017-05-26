#include <stdio.h>

int main(){
	int i,j,x,min,a;
	int number[15];
	for(i=0;i<10;i++){
		printf("®”‚ð“ü—Í=>");
		scanf("%d",&number[i]);
	}
	for(i=0;i<10;i++){
		min=number[i];
		a=i;
		for(j=i+1;j<10;j++){
			if(number[j]<min){
				min=number[j];
				a=j;
			}
		}
		x=number[a];
		number[a]=number[i];
		number[i]=x;
	}
	printf("========¬‚³‚¢‡=======\n");
	for(i=0;i<10;i++){
		printf(" %d",number[i]);
	}
	return 0;
}

