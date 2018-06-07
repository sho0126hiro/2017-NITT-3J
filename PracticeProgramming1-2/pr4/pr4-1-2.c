#include <stdio.h>
#define BUF_SIZE 32
#include <string.h>/*strlen();�g�p�̂���*/
int checksp(int c)
{
	if(c==0x20)return 1;	/*space*/
	else if(c==0x09)return 1;	/*Tab*/
	else if(c==0x0A)return 1;	/*���s*/
	else if(c==0x2C)return 2;	/*�J���}*/
	else if(c==0x2E)return 1;	/*�s���I�h*/
	else return 0;		/*���ʂ̕���*/
}

void compress(char *s)
{
	char *p=s;
	/* �s���̋󔒂����� */
	while( checksp(*p) ){
		p++;
	}
	/* �V������������쐬���Ă��� */

	while(*p!='\0'){			
		/*�s���I�h�����*/
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


