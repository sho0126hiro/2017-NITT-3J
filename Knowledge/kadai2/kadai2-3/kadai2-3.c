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
void expand(char data[512],char pattern[64][64]){
	int i,j,k;
	unsigned char b=128;
	
	for(k=0;k<64;k++){
		for(j=1;j<8;j++){
			b=128;
			for(i=0;i<8;i++){
				if((data[k*8+j]&b)==0){
					pattern[k][8*j+i]=0;
				}else{
					pattern[k][8*j+i]=1;
				}
				b=b>>1;
			}
		}
	}
}

void compress(char data[512],char pattern[64][64]){
	int i,j,k;
	unsigned char b=1;
	for(k=0;k<64;k++){
		for(j=0;j<64;j++){
			b=128;
			for(i=0;i<8;i++){
				if(pattern[k][j]==0){
					data[8k+j]=0;
				}else{
					data[j*k]=1;
				}
			}
			b=b<<1;
		}
	}	
}
//sakamotojun
/*void compress(char data[512],char pattern[64][64]){
	for(int i=0;i<512;i++){
		for(int j=7;j>=0;j--){
			if(data[i]&(1<<j)){
				pattern[i/8][(i%8+1)*8-j]=1;
			}else{
				pattern[i/8][(i%8+1)*8-j]=0;
			}
		}
	}
}*/

//•\¦ŠÖ”
void Display(char d[64][64]){
	int i,j;
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			printf("%d",d[j][i]);
		}
		printf("\n");
	}
}
int main(){
	int i,j;
	char data[512];
	char pattern[64][64]={0};
	unsigned char b=128;
	FILE *fp;
	
	fp=fopen("01.img","rb");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	fread(data,512,1,fp);
	fclose(fp);
	printimg( data ) ;
	expand( data, pattern ) ;
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			putchar(pattern[j][i] ==1?'@':'o');
		}
		putchar('\n');
	}
	/* data[]‚ğƒNƒŠƒA‚·‚é */
	compress( data, pattern ) ;
	printimg( data ) ;
	return 0;
}