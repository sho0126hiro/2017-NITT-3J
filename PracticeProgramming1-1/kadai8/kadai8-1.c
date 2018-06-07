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
	
	printf("’Tõ‚·‚é”Žš‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢„");
	scanf("%d",&n1);
	
	int left=0,right=N,m;
	
	while(left<=right){
		m=(left+right)/2;
		if(number[m]==n1){
			printf("%d”Ô–Ú‚Å‚·",m);
			return 0;
		}else if(number[m]<n1){
			left = m+1;	//M+1‚ðŽŸ‰ñ‚Ìæ“ª‚É‚·‚é
		}else {
			right = m-1;//M-1‚ðŽŸ‰ñ‚ÌÅŒã”ö‚É‚·‚é
		}
	}
	printf("ŠY“–‚È‚µ");
	return 0;
}
