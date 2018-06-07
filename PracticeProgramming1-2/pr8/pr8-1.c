/* グラフ構造の深さ優先探索 */

#include<stdio.h>
#include <stdlib.h>
#define TRUE      1
#define FALSE     0
#define MAX_SIZE 11

typedef struct character{
	int  no;                        /* キー */
	char name;                      /* 名前 */
	struct character *next_addr;    /* 次のデータのアドレス */
}CELL;

/*二次元配列（ポインタ）*/
char *graph_data[] = {
	"CI",           /* A : C I */
	"DGH",          /* B : D G H */
	"ADG",          /* C : A D G */
	"BCHIJ",        /* D : B C H I J */
	"FHJ",          /* E : F H J */
	"EGK",          /* F : E G K */
	"BCF",          /* G : B C F */
	"BDEJ",         /* H : B D E J */
	"AD",           /* I : A D */
	"DEHK",         /* J : D E H K */
	"FJ"            /* K : F J */
};

CELL *adjacent[MAX_SIZE]; /* 隣接リスト */
int visited[MAX_SIZE];
int path[MAX_SIZE];

/* リスト構造で並んでいる様子を表示する */
void disp(void) {
	int i = 0;
	CELL *current_addr;
	printf("隣接リスト:\n");
	for( i = 0; i < MAX_SIZE; i++ ){
		if( adjacent[i] != NULL ){
			current_addr = adjacent[i];
			do{
				printf("-|%c|-",current_addr->name);
				current_addr = current_addr->next_addr;
			}while( current_addr != NULL );
		}
		printf("\n");
	}
}

/* データの追加 */
void add(int parent, int child) {
	/*adjacent[0]->child->child->NULL
	  adjacent[1]->child->NULL
	  （以下略）
	  上記の線形リストを作っている*/
	CELL *p;
	CELL *q;
	p = (CELL *)malloc(sizeof(CELL));
	p->no = child;
	p->name = 'A' + child;
	p->next_addr = NULL;
	q = adjacent[parent];
	while ( q->next_addr != NULL ) {
		q = q->next_addr;
	}
	q->next_addr = p;
}

/* グラフの初期化 */
void init_graph(void) {
	CELL *p;
	int i,j,l;
	for (i = 0; i < MAX_SIZE; i++){
		visited[i]=FALSE;
	}
	/*adjacent初期化*/
	for(i=0;i<MAX_SIZE;i++){
		p = (CELL *)malloc(sizeof(CELL));
		p->no=i;
		p->name='A'+i;
		p->next_addr=NULL;
		adjacent[i]=p;
	}
	//[TATE][YOKO]
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;graph_data[i][j] != '\0';j++){
			/*addを利用*/
			l=graph_data[i][j]-'A';
			add(i,l);
		}
	}
}
/* 経路の表示 */
void print_path(int num) {
	int i;
	for( i = 0; i <= num; i++ ){
		 printf("%c ", path[i] + 'A' );
	}
	printf("\n");
}

/* 経路の探索（深さ優先探索） */
void search(int num, int now, int end) {
	/*
		num : 探索手数
		now : 現在の頂点の位置
		end : ゴールの位置
	*/
	CELL *p;
	visited[now]=TRUE;/*訪れたことを記憶*/
	path[num]=now;/*現在位置をセット*/
	if(now==end){
		print_path(num);
	}else{
		p=adjacent[now];
		while(p != NULL){
			if(visited[p->no]==FALSE){
				search(num+1,p->no,end);
			}
			p=p->next_addr;
		}
	}
	visited[now]=FALSE;
	//printf("%d:adjacent[name]:%c[LAST]\n",__LINE__,now+'A');
}

/* メイン関数 */
int main(void) {
	init_graph();
	disp();
	search( 0, 0, 10 );		/* A(0) から K(10) の経路 */
	return 0;
}
