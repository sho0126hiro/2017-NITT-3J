#include <stdio.h>
/**ŠÖ”éŒ¾********************************************************************/
void expand(char data[512],char pattern[64][64]);
void noise(char p[64][64]);
int label(char p[64][64],int j,int i,int x);
void Display(char d[64][64]);
/**main************************************************************************/
int main(){
	int i,j,x,y;
	char data[512];
	char pattern[64][64]={0};
	unsigned char b=128;
	FILE *fp;
	
	fp=fopen("21.img","rb");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	
	fread(data,512,1,fp);
	fclose(fp);
	expand(data,pattern);
	pattern[0][0]=1;
	pattern[63][5]=1;
	Display(pattern);
	noise(pattern);
	printf("\n\n");
	Display(pattern);
	return 0;
}
//“ñŸŒ³”z—ñ‚ÉŠi”[‚·‚éŠÖ”*****************************************************/
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
//ƒmƒCƒYˆ—*******************************************************************/
void noise(char p[64][64]){
	int i,j,x=2,T=18,c=0;
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			if(p[j][i]==1){
				int a=label(p,j,i,x);
				if(a==1){
					printf("error");
					return;
				}
				x++;
			}
		}
	}

	//œ‹
	while(x!=0){
		c=0;
		for(i=0;i<64;i++)for(j=0;j<64;j++)if(p[i][j]==x)c++;
		if(c<T){
			for(i=0;i<64;i++)for(j=0;j<64;j++)if(p[i][j]==x)p[i][j]=0;
		}
		x--;
	}
	//–ß‚·
	for(i=0;i<64;i++)for(j=0;j<64;j++)if(p[i][j]!=0)p[i][j]=1;
}
int label(char p[64][64],int j,int i,int x){
	if(x==255)return 1;
	if(i<=0||i>=63||j<=0||j>=63){
		p[j][i]=x;
		return 0;
	}
	p[j][i]=x;
	if(p[j+1][i  ]==1)label(p,j+1,i  ,x);
	if(p[j-1][i  ]==1)label(p,j-1,i  ,x);
	if(p[j  ][i+1]==1)label(p,j  ,i+1,x);
	if(p[j  ][i-1]==1)label(p,j  ,i-1,x);
	return 0;
}
//•\¦ŠÖ”*******************************************************************/
void Display(char d[64][64]){
	int i,j;
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			printf("%d",d[j][i]);
		}
		printf("\n");
	}
}
/*****************************************************************************/