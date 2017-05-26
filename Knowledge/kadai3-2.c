#include <stdio.h>

void expand(char data[512],char pattern[64][64]);
void outline(char p[64][64]);
void Display(char d[64][64]);
void smooth(char p[64][64]);
void smoothDecision(char p[64][64]);

//main*************************************************************************/
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
	Display(pattern);
	smooth(pattern);
	printf("2\n\n");
	Display(pattern);
	return 0;
}
//スムージング***************************************************************/
void smooth(char p[64][64]){
	smoothDecision(p);
	for(int j=1;j<63;j++){
		for(int i=1;i<63;i++){
			if(p[j][i]==2){
				p[j][i]=0;
			}
		}
	}
}

//スムージング2(判定)********************************************************/
void smoothDecision(char p[64][64]){
	for(int j=1;j<63;j++){
		for(int i=1;i<63;i++){
		
			if(	p[j-1][i-1]    && p[j  ][i-1] && p[j+1][i-1] &&
				p[j-1][i  ]==0 && p[j  ][i  ] && p[j+1][i  ] &&
				p[j-1][i+1]    && p[j  ][i+1] && p[j+1][i+1]){
				p[j-1][i  ]=1;	
			}
			if(	p[j-1][i-1]==0 && p[j  ][i-1] && p[j+1][i-1] &&
				p[j-1][i  ]    && p[j  ][i  ] && p[j+1][i  ] &&
				p[j-1][i+1]==0 && p[j  ][i+1] && p[j+1][i+1]){
				p[j-1][i  ]=2;
			}
			//右回転
			if(	p[j-1][i-1] && p[j][i-1]    && p[j+1][i-1] &&
				p[j-1][i  ] && p[j][i  ]    && p[j+1][i  ] &&
				p[j-1][i+1] && p[j][i+1]==0 && p[j+1][i+1]){
				p[j  ][i+1]=1;
			
			}
			if(	p[j-1][i-1]    && p[j][i-1] && p[j+1][i-1] &&
				p[j-1][i  ]    && p[j][i  ] && p[j+1][i  ] &&
				p[j-1][i+1]==0 && p[j][i+1] && p[j+1][i+1]==0){
				p[j][i+1]=2;
			}
			//もう一度右回転
			if(	p[j-1][i-1] && p[j][i-1] && p[j+1][i-1]    &&
				p[j-1][i  ] && p[j][i  ] && p[j+1][i  ]==0 &&
				p[j-1][i+1] && p[j][i+1] && p[j+1][i+1]){
				p[j+1][i]=1;
			}
			if(	p[j-1][i-1] && p[j][i-1] && p[j+1][i-1]==0 &&
				p[j-1][i  ] && p[j][i  ] && p[j+1][i  ]    &&
				p[j-1][i+1] && p[j][i+1] && p[j+1][i+1]==0){
				p[j+1][i]=2;
			}
			//もう一度右回転
			if(	p[j-1][i-1] && p[j][i-1]==0 && p[j+1][i-1] &&
				p[j-1][i  ] && p[j][i  ]    && p[j+1][i  ] &&
				p[j-1][i+1] && p[j][i+1]    && p[j+1][i+1]){
				p[j][i-1]=1;
			}
			if(	p[j-1][i-1]==0 && p[j][i-1] && p[j+1][i-1]==0 &&
				p[j-1][i  ]    && p[j][i  ] && p[j+1][i  ]    &&
				p[j-1][i+1]    && p[j][i+1] && p[j+1][i+1]){
				p[j][i-1]=2;
			}
		}
	
	}
	//判定終わり
}

/*
	p[j-1][i-1]==1 && p[j][i-1]==1 && p[j+1][i-1]==1 &&
	p[j-1][i]==1 && p[j][i]==1 && p[j+1][i]==1 &&
	p[j-1][i+1]==1 && p[j][i+1]==1 && p[j+1][i+1]==1	
*/

//二次元配列に格納する関数***************************************************/
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

//輪郭抽出関数**********************************************************/
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
//表示関数********************************************************************//
void Display(char d[64][64]){
	int i,j;
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			printf("%d",d[j][i]);
		}
		printf("\n");
	}
}

