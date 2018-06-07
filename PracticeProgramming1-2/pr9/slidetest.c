#include <stdio.h>

int main(){
	int i,j=0;
	int q[10];
	for(i=0;i<10;i++)q[i]=-1;
	q[0]=0;
	q[1]=2;
	q[2]=4;
	q[3]=6;
	for(i=0;i<10;i++)printf("%d ",q[i]);
	printf("\n");
	printf("while\n");
	while(q[j]!=-1){
		q[j]=q[j+1];
		j++;
		for(i=0;i<10;i++)printf("[%2d]",q[i]);
		printf("\n");
	}
	printf("\n");
	q[j-1]=-1;
	printf("last\n");
	for(i=0;i<10;i++)printf("[%d]",q[i]);
	return 0;
}
