#include <stdio.h>

int fib(int n){
	if(n<3)return 1;
	return fib(n-2)+fib(n-1);
}

int main(){
	int n;
	printf("�t�B�{�i�b�`�����n�Ԗڂ̒l�����߂܂�\n");
	printf("����n�����>>>");
	scanf("%d",&n);
	printf("%d\n",fib(n));
	return 0;
}
