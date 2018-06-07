#include <stdio.h>
#define BUF_SIZE 32
#include <string.h>/*strlen();使用のため*/
int checksp(int c)
{
	if(c==0x20)return 1;	/*space*/
	else if(c==0x09)return 1;	/*Tab*/
	else if(c==0x0A)return 1;	/*改行*/
	else if(c==0x2C)return 2;	/*カンマ*/
	else if(c==0x2E)return 1;	/*ピリオド*/
	else return 0;		/*普通の文字*/
}

void compress(char *s)
{
	char *p=s;
	/* 行頭の空白を消去 */
	while( checksp(*p) ){
		p++;
	}
	/* 新しい文字列を作成していく */

	while(*p!='\0'){			
		/*ピリオドから先*/
		if(*p==0x2E){
			while(*p!='\0'){
				p++;
			}
			*s='.';
			s++;
			break;
		}
		if(checksp(*p)==1){
			if(checksp(*(p+1))==0){
				*s=*p;
				s++;
			}
		}else{
			*s=*p;
			s++;
		}
		p++;
		//s++;
	}
	*s = '\0';
}


int main(void)
{
	char s[] = "     Nice to \n meet \t you    ,  Jack !\n     I'm      Mike \n\t\t .    ";
	printf("Before = \"%s\"\n",s);
	compress(s);

	printf("After  = \"%s\"\n",s);

	return 0;
}


