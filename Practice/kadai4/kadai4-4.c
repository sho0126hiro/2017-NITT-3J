#include <stdio.h>

int Binary(int n){
	if(n<=0)return 0;
	Binary(n/2);
	printf("%d",n%2);
	return n;
}

int main(){
	int n;
	printf("“ñi”‚ð‹‚ß‚Ü‚·\n");
	printf("®”n‚ð“ü—Í>>>");
	scanf("%d",&n);
	Binary(n);
	return 0;
}
