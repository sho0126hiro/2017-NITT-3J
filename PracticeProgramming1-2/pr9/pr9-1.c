/* グラフ構造の幅優先探索 */

#include<stdio.h>

#define TRUE            1
#define FALSE           0
#define MAX_SIZE        11

int adjacent[MAX_SIZE][MAX_SIZE]; /* 隣接行列 */
int visited[MAX_SIZE];
int open_list[MAX_SIZE]; /* キュー */
int count;/**/
	
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

/*隣接行列の表示*/
void disp(){
	int i,j;
	printf("隣接行列：\n");
	for(j=0;j<MAX_SIZE;j++){
		for(i=0;i<MAX_SIZE;i++){
			printf("%d ",adjacent[j][i]);
		}
		printf("\n");
	}
}

/* グラフの初期化 */
void init_graph(void)
{
	int i,j;
	/*visit初期化*/
	for(j=0;j<MAX_SIZE;j++){
		visited[j]=FALSE;
	}
	/*adjacent初期化*/
	for(j=0;j<MAX_SIZE;j++){
		for(i=0;i<MAX_SIZE;i++){
			adjacent[j][i]=0;
		}
	}
	//[TATE][YOKO]
	for(j=0;j<MAX_SIZE;j++){
		for(i=0;graph_data[j][i] != '\0' ;i++){
			adjacent[j][graph_data[j][i]-'A']=1;
		}
	}
	disp();
}


/* キューの初期化 */
void init_queue(int *q)
{
	int i;
	for( i = 0; i < MAX_SIZE; i++ ){
		q[i] = -1;
	}
}

/* キューの表示 */
void print_queue(int *q)
{
	int i;
	printf("{");
	for( i = 0; i < MAX_SIZE; i++ )
		if( q[i] != -1 )
			printf("%c",q[i]+'A');
	printf("}\n");
}

/* キューの中にデータdが存在しているかどうかをチェック */
int check_queue(int *q,int d)
{
	int i;
	for( i = 0; i < MAX_SIZE;i++ )
		if( q[i] == d ) return TRUE;
	return FALSE;
}

/* キューにデータを入れる */
void enqueue(int *q, int d)
{	
	int count=0;
	while(q[count]!=-1)count++;
	q[count]=d;
}

/* キューからデータを取り出す */
int dequeue(int *q)
{
	int x,i=0;
	
	if(q[0]==-1)return -1;//いらない？
	else x=q[0];
	/*slide*/
	while(q[i]!=-1){
		q[i]=q[i+1];
		i++;
	}
	q[i-1]=-1;
	return x;
}

/* 経路の探索（幅優先探索） */
/*searching.. の場所とprint_queueの場所*/
void search(int now, int end)
{
	int i;
	init_queue(open_list);/*キューの初期化*/
	enqueue(open_list,now);/*最初のデータ(now)をキューに入れる*/
	visited[now]=TRUE;/*訪れたことを記憶*/
	printf("searching ... %c\n",(now +'A'));
	printf("open_list =");
	print_queue(open_list);
	/*キューにデータがなくなるまで繰り返す*/
	while(open_list[0]!=-1){
		now=dequeue(open_list);/*キューからデータを取り出してnowにセット*/
		visited[now]=TRUE;/*visited[now]にTRUEをセットし訪れたことを記憶*/
		if(now==end){/*現在位置がゴールであれば*/
			printf("Found.\n");
		}else{/*現在地がゴールでない時*/	
			for(i=0;i<MAX_SIZE;i++){/*全ての頂点を検索*/
				if(adjacent[now][i]==1 && visited[i]!=TRUE){/*隣接している時でかつ、まだ訪れていない時*/
					if(check_queue(open_list,i)!=TRUE){/*キューの中に存在しない頂点を選ぶ*/
						enqueue(open_list,i);
						printf("searching ... %c\n",(i +'A'));
						printf("open_list =");
						print_queue(open_list);
					}
				}
			}
		}
	}	
}

/* メイン関数 */
int main(void)
{
	init_graph();
	search(0, 10 );         /* A から K の経路 */
	return 0;
}
