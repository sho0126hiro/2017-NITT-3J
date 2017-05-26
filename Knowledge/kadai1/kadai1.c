#include <stdio.h>

int main(){
	int i,j,k,l;
	char d[512];
	unsigned char b=128;
	FILE *fp;
	
	fp=fopen("01.img","rb");
	
	for(l=0;l<20;l++){
		fread(d,512,1,fp);
		for(k=0;k<64;k++){
			for(j=0;j<8;j++){
				b=128;
				for(i=0;i<8;i++){
					if((d[k*8+j]&b)==0){
						printf(".");
					}else{
						printf("*");
					}
				b=b>>1;
				}
			}
			printf("\n");
		}
		getchar();
		printf("\n\n");
	}
	return 0;
}

