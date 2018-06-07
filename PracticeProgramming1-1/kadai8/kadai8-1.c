#include <stdio.h>
#define N 10000000
#define debug printf("%d %s \n",__LINE__,__func__); 

int main(){
	FILE *fp;
	int i,n1;
	long number[N];
	fp=fopen("sorted.dat","r");
	if (fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(i=0;i<N;i++){
		fscanf(fp,"%d",&number[i]);
	}
	fclose(fp);
	
	printf("�T�����鐔������͂��Ă���������");
	scanf("%d",&n1);
	
	int left=0,right=N,m;
	
	while(left<=right){
		m=(left+right)/2;
		if(number[m]==n1){
			printf("%d�Ԗڂł�",m);
			return 0;
		}else if(number[m]<n1){
			left = m+1;	//M+1������̐擪�ɂ���
		}else {
			right = m-1;//M-1������̍Ō���ɂ���
		}
	}
	printf("�Y���Ȃ�");
	return 0;
}
