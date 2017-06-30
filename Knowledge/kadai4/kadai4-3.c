#include <stdio.h>

#define DIM 256 //抽出する特徴量の次元
/**関数宣言********************************************************************/
void expand(char data[512],char pattern[64][64]);	//64*64の二次元配列に格納する
void noise(char p[64][64]);							//ノイズ除去1
int  label(char p[64][64],int j,int i,int x);		//ノイズ除去2
void smooth(char p[64][64]);						//スムージング1
void smoothDecision(char p[64][64]);				//スムージング2
void normalize(char p[64][64]);						//正規化1
int  min(int x,int y);								//正規化2
int  max(int x,int y);								//正規化3
void outline(char p[64][64]);						//輪郭抽出
void Display(char d[64][64]);						//表示
void extract( char p[64][64], int f[DIM] );			//特徴量抽出

/**main************************************************************************/
int main(){
	FILE *fp1, *fp2 ;
	char infn[0x80], outfn[0x80] ;
	char img[512] ;
	char p[64][64] ;
	int  f[DIM] ;
	int  num, i, j ;
	
	//データファイルごとの特徴量抽出
	
	for(i=0;i<46;i++){
		//画像ファイル・特徴ファイルの名前を設定する
		sprintf( infn, "%02d.img", i+1 );
		sprintf( outfn, "%02d.ftr", i+1 );
		//文字画像ファイルおよび特徴ファイルを開く
		fp1 = fopen( infn, "rb" ) ;
		fp2 = fopen( outfn, "w" ) ;
		//ファイル内に文字画像データがある限り下記の処理を繰り返す
		while(fread(img,512,1,fp1)==1){
			//前処理
			expand(img,p);
			noise(p);
			smooth(p);
			normalize(p);
			outline(p);
			//特徴抽出
			extract(p,f);
			//特徴出力
			for(j=0;j<DIM;j++){
				fprintf(fp2,"%d\n",f[j]);
			}
		}
		//ファイルクローズ
		fclose(fp1);
		fclose(fp2);
	}
	return 0;
}

//二次元配列に格納する*****************************************************/
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

//ノイズ除去1*******************************************************************/
void noise(char p[64][64]){
	int i,j,x=2,T=13,c=0;
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
	//Display(p);
	//除去
	while(x!=0){
		c=0;
		for(i=0;i<64;i++)for(j=0;j<64;j++)if(p[i][j]==x)c++;
		if(c<T){
			for(i=0;i<64;i++)for(j=0;j<64;j++)if(p[i][j]==x)p[i][j]=0;
		}
		x--;
	}
	//戻す
	for(i=0;i<64;i++)for(j=0;j<64;j++)if(p[i][j]!=0)p[i][j]=1;
}

//ノイズ除去2*******************************************************************/
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
	//printf("x0=%d y0=%d\nx1=%d y1=%d\n",x0,y0,x1,y1);
	int w=x1-x0+1;
	int h=y1-y0+1;
	//printf("w=%d h=%d",w,h);
	
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
//2数を比べて大きいほうを返す(正規化2)**************************************/
int max(int x,int y){
	if(y>x)return y;
	else return x;
}
//2数を比べて小さいほうを返す(正規化3)**************************************/
int min(int x,int y){
	if(y>x)return x;
	else return y;
}

//輪郭抽出**********************************************************/
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
//表示**********************************************************************/
void Display(char d[64][64]){
	int i,j;
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			printf("%d",d[j][i]);
		}
		printf("\n");
	}
}
/*特徴抽出***********************************************************************/
void extract( char p[64][64], int f[DIM] ){
	//DIM=256の時だけ動作する
	int l,k,j,i,c;
	for(l=0;l<16;l++){
		for(k=0;k<16;k++){
			c=0;
			for(j=0;j<4;j++){
				for(i=0;i<4;i++){
					if(p[4*l+j][4*k+i]==1){
						c++;
					}
				}
			}
			f[16*l+k]=c;
		}
	}
}
/*******************************************************************************/
