#include <stdio.h>

int Summation(int n){
	if(n==1)return 1;
	return n+Summation(n-1);
}
int main(){
	int n;
	printf("n�܂ł̑��a�����߂܂�\n");
	printf("����n�����>>>");
	scanf("%d",&n);
	printf("%d\n",Summation(n));
	return 0;
}
