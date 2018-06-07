#include <stdio.h>
#include <string.h>

int main(void){
	char ss[]="Abd";
	char *p1,*p2;
	p1=(char *)malloc(sizeof(char[4]));
	p2=(char *)malloc(sizeof(char[4]));
	strcpy(p1,ss);
	strcpy(p2,ss);
	//p1,p2Ç…ssÇÉRÉsÅ[
	printf("1:");
	printf("%s\n",*(p1+2));
	
	printf("2:");
	printf("%s\n",p1+1);
	
	printf("3:");
	printf("%c\n",*p1+1);

	*p2=*(p1+1)+1;
	*(p1+2)=*p2;
	printf("4:");
	printf("%s\n",p2);
	
	printf("5:");
	printf("%s\n",p1);
	
	return 0;
	
}

/*
1:d
2:bd
3:B
4:cbd
5:Abc
*/
