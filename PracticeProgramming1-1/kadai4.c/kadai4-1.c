#include <stdio.h>

int fib(int n){
	if(n<3)return 1;
	return fib(n-2)+fib(n-1);
}

int main(){
	int n;
	printf("フィボナッチ数列のn番目の値を求めます\n");
	printf("整数nを入力>>>");
	scanf("%d",&n);
	printf("%d\n",fib(n));
	return 0;
}
