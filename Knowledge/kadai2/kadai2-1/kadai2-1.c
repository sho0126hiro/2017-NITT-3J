#include <stdio.h>

void printimg(char data[512]){
	int i,j,k;
	unsigned char b=128;

	for(k=0;k<64;k++){
		for(j=1;j<8;j++){
			b=128;
			for(i=0;i<8;i++){
				if((data[k*8+j]&b)==0){
					printf(".");
				}else{
					printf("*");
				}
			b=b>>1;
			}
		}
		printf("\n");
	}
}	

int main(){
	char data[512];
	unsigned char b=128;
	FILE *fp;
	
	fp=fopen("01.img","rb");
	fread(data,512,1,fp);
	printimg(data);
	fclose(fp);
	return 0;
}

