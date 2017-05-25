#include <stdio.h>
/**関数宣言********************************************************************/
void expand(char data[512],char pattern[64][64]);
void outline(char p[64][64]);
void Display(char d[64][64]);
void normalize(char p[64][64]);
int min(int x,int y);
int max(int x,int y);
/**main************************************************************************/
int main(){
	int i,j,x,y;
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
	expand(data,pattern);
	printf("Display 1\n\n\n");
	Display(pattern);
	normalize(pattern);
	printf("Display 2\n\n");
	Display(pattern);
	return 0;
}
//二次元配列に格納する関数*****************************************************/
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

//輪郭抽出関数*****************************************************************/
void outline(char p[64][64]){
	int i,j;
	//文字列チェック(0行目，63行目，0列目，63列目は判定しない）
	for(j=1;j<63;j++){
		for(i=1;i<63;i++){
			if(p[j-1][i]!=0 && p[j+1][i]!=0){//対象文字の上下が黒
				if(p[j][i-1]!=0 && p[j][i+1]!=0){//対象文字の左右が黒
					p[j][i]=2;
				}
			}
		}
	}
	for(j=1;j<63;j++){
		for(i=1;i<63;i++){
			if(p[j][i]==2){
				p[j][i]=0;
			}
		}
	}
}
//正規化***********************************************************************/
void normalize(char p[64][64]){
	int i,j,x0=64,y0=64,x1=0,y1=0;
	double W=64,H=64,x,y;
	char p2[64][64];
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			if(p[j][i]==1){
				x0=min(x0,i);
				y0=min(y0,j);
				x1=max(x1,i);
				y1=max(y1,j);
			}
		}
	}	
	printf("x0=%d y0=%d\nx1=%d y1=%d\n",x0,y0,x1,y1);
	int w=x1-x0+1;
	int h=y1-y0+1;
	printf("w=%d h=%d",w,h);
	
	/*	x0=12  y0= 5
		x1=50  y1=58
		w =39  h =54	*/
	
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			p2[j][i]=p[(int)(j*(h/H)+y0+0.5)][(int)(i*(w/W)+x0+0.5)];
		}
	}
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			p[j][i]=p2[j][i];
		}
	}
}
//2数を比べて大きいほうを返す(normalize)**************************************/
int max(int x,int y){
	if(y>x)return y;
	else return x;
}
//2数を比べて小さいほうを返す(normalize)**************************************/
int min(int x,int y){
	if(y>x)return x;
	else return y;
}
//表示関数*******************************************************************/
void Display(char d[64][64]){
	int i,j;
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			printf("%d",d[j][i]);
		}
		printf("\n");
	}
}
/*******************************************************************************/
