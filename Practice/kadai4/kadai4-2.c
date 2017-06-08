#include <stdio.h>


int Factorial(int n){
	if(n==1)return 1;
	return n*Factorial(n-1);
}
int main(){
	int n;
	printf("n‚ÌŠKæ‚ð‹‚ß‚Ü‚·\n");
	printf("®”n‚ð“ü—Í>>>");
	scanf("%d",&n);
	printf("%d!=%d\n",n,Factorial(n));
	return 0;
}
