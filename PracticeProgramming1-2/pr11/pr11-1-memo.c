#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_SIZE 13
#define TRUE     1
#define FALSE    0
#define IMAX     10000 /* 想定し得る最大コストよりも大きい値を設定 */

#define min(a,b) ((a)<(b) ? (a):(b))

 /* データ（隣接行列） */
int adjacent[MAX_SIZE][MAX_SIZE] = {
        {   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  0: 東京
        {  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  1: 埼玉
        {IMAX,  90,   0,IMAX,IMAX, 110, 330,240,IMAX,IMAX,IMAX,IMAX,IMAX},      //  2: 群馬
        {  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  3: 千葉
        {IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  4: 茨城
        {IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  5: 栃木
        {IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},     //  6: 福島
        {IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},     //  7: 新潟
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},     //  8: 山形
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},     //  9: 宮城
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},     // 10: 秋田
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},     // 11: 岩手
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}      // 12: 青森
};

char *graph_data[] = {  // 上記隣接行列の0~12番目の各要素に対応
        "Tokyo",
        "Saitama",
        "Gunma",
        "Chiba",
        "Ibaraki",
        "Tochigi",
        "Fukushima",
        "Niigata",
        "Yamagata",
        "Miyagi",
        "Akita",
        "Iwate",
        "Aomori"
};


int d[MAX_SIZE][MAX_SIZE];           /* 頂点間の最小コスト */
int pre_vertex[MAX_SIZE][MAX_SIZE];  /* 最短経路 */

/* dとpre_vertexを初期化 */
void init(void)
{
	//d[i][j]=adjacent[i][j]
	int i,j;
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			d[i][j]=adjacent[i][j];//adjacent初期化
			pre_vertex[i][j] = i;//pre_vertex初期化
		}
	}
}

/* すべての頂点間の最短経路を探索（フロイド法） */
void search(void)
{
	int i,j,k;
  for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			for(k=0;k<MAX_SIZE;k++){
				if(d[i][j]!=(min(d[i][j],d[i][k]+d[k][j]))){//更新する
					d[i][j]=d[i][k]+d[k][j];
					pre_vertex[i][j]=pre_vertex[k][j];
				}
			}
		}
	}
  /*memo
  for(i=0;i<MAX_SIZE;i++){
    for(j=0;j<MAX_SIZE;j++){
      上の二行で、すべての隣接行列を操作（指定）している。
      
      for(k=0;k<MAX_SIZE;k++){
      これは、他の経由していったほうが早いかを調べるためにkを使っている。
      kを0-maxsizeで繰り返すことで、全ての頂点に対して、経由したほうが早いかを調べている

        if文
        i-j　  このルートか、
        i-k-j　このルートのどっちが短いかを調べたい。

        ちなみに、min(a,b)は、aとbで比べて小さいほうを返す（上でdefineしてる）
        10行目
        #define min(a,b) ((a)<(b) ? (a):(b))
        これは、関数
        int min(int a,int b){
          if(a>b)return b;  //aとbで比べてbが小さいからbを返す
          else return a;    //aとbで比べてaが小さいからaを返す
        }
        と同じ意味
        
        min(d[i][j],d[i][k]+d[k][j]))
        これは、d[i][j]と、d[i][k]+d[k][j]を比べてどっちが小さいかを調べて、
        小さいほうを表している。
        

        if(d[i][j]!=(min(d[i][j],d[i][k]+d[k][j]))){//更新する
          ：kを経由したほうが早い時に、if(true)になる

        ifの中身:
          d[i][j]=d[i][k]+d[k][j];
          kを経由したほうが早いなら、kを経由したルートに更新しよう
          pre_vertex[i][j]=pre_vertex[k][j];
          これは、先生の講義資料の中に
          「そして、d[i][j]を更新する際、 pre_vertex[i][j]にはpre_vertex[k][j]を代入します。」
          ってかかれてあった。
          （https://nittc.tokyo-ct.ac.jp/usr/kitakosi/LEE/PracProgI/akiyojissen1/kougi27.html）
    
    これでおしまい
    search関数を動かした後の、d[i][j]とpre_vertex[i][j]の状態は下に貼っておきます
    なにか参考になるかも
  */
}

/* 経路を表示（逆順） */
void print_path(int p, int q)
{
    int x = q;
    printf("-|%s|-",graph_data[x]);
    do{
        x = pre_vertex[p][x];
        printf("-|%s|-",graph_data[x]);
    }while(x != p);
}

int main(void)
{
	//int h,begin,end,flag;
	//int i,j;
	char start[10],destination[10];
    /* 初期化 */
	init();
    /* 探索 */
	search();

	print_path(5, 0);   // 実行の一例 tochigi-tokyo
    return 0;
}
/*
pre_vertex[i][j]
    0    0    1    0    1    1    5    2    6    6    8    9   11
    1    1    1    1    1    1    5    2    6    6    8    9   11
    1    2    2    1    5    2    5    2    6    6    8    9   11
    3    3    1    3    3    1    5    2    6    6    8    9   11
    1    4    5    4    4    4    4    2    6    6    8    9   11
    1    5    5    1    5    5    5    2    6    6    8    9   11
    1    5    5    1    6    6    6    2    6    6    8    9   11
    1    2    7    1    5    2    5    7    6    6    8    9   11
    1    5    5    1    6    6    8    2    8    8    8    9   11
    1    5    5    1    6    6    9    2    9    9    8    9   11
    1    5    5    1    6    6    8    2   10    8   10   10   10
    1    5    5    1    6    6    9    2    9   11   11   11   11
    1    5    5    1    6    6    9    2    9   11   12   12   12
d[i][j]
    0   30  120   40  170  110  280  360  360  370  550  550  740
   30    0   90   60  140   80  250  330  330  340  520  520  710
  120   90    0  150  210  110  280  240  360  370  550  550  740
   40   60  150    0  130  140  310  390  390  400  580  580  770
  170  140  210  130    0  100  260  450  340  350  530  530  720
  110   80  110  140  100    0  170  350  250  260  440  440  630
  280  250  280  310  260  170    0  520   80   90  270  270  460
  360  330  240  390  450  350  520    0  600  610  790  790  980
  360  330  360  390  340  250   80  600    0   60  190  240  430
  370  340  370  400  350  260   90  610   60    0  250  180  370
  550  520  550  580  530  440  270  790  190  250    0  110  300
  550  520  550  580  530  440  270  790  240  180  110    0  190
  740  710  740  770  720  630  460  980  430  370  300  190    0
*/