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
    
    printf("1\n");
    /*
      printf("*(p1):%c\n",*(p1));
      = printf("*(p1+0):%c\n",*(p1+0));
    */
    printf("*(p1)  :%c\n",*(p1));
    printf("*(p1+1):%c\n",*(p1+1));
    printf("*(p1+2):%c\n",*(p1+2));
    
    
    printf("2\n");
    
    printf("p1  :%s\n",p1);
    printf("p1+1:%s\n",p1+1);
    printf("p1+2:%s\n",p1+2);
    
    
    printf("3\n");
    printf("*p1  :%c\n",*p1);
    printf("*p1+1:%c\n",*p1+1);
    printf("*p1+2:%c\n",*p1+2);
    printf("\n");

    *p2=*(p1+1)+1;
    
    printf("*p2=*(p1+1)+1;\n");
    printf("*p2  :%c\n",*p2);
    printf("\n");
    
    *(p1+2)=*p2;
    
    printf("4:");
    printf("%s\n",p2);
    
    printf("5:");
    printf("%s\n",p1);
    
    return 0;
    
}

/*
1
    *(p1)  :A
    *(p1+1):b
    *(p1+2):d
2
    p1  :Abd
    p1+1:bd
    p1+2:d
3
    *p1  :A
    *p1+1:B
    *p1+2:C

        *p2=*(p1+1)+1;
        *p2  :c

4:  cbd
5:  Abc
*/
