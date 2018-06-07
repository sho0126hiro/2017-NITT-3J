/* 2分探索木による探索 */

#include <stdio.h>
#include <stdlib.h> /*malloc*/
#include <string.h> /*strcmp*/

#define KEY_SIZE	8

struct tree{
	struct tree *left;
	int no;
	struct tree *right;
};

/* 数値の入力用関数 */
int get_num(void) {
	int  i;
	int  d = 0;
	int  c = 0;
	rewind(stdin);
	for( i = 0; i < 5 && c != '\n' ; i++ ){ /* 5ケタまで */
	 c = getchar();
	 if ( c == '\n' ) break;
	 d = d * 10 + c - '0';
	}
	rewind(stdin);
	return d;
}

/* ノードの追加 */
struct tree *add_node(int num) {
	 struct tree *p;
	 p = (struct tree *)malloc(sizeof(struct tree));
	 p->left = NULL;
	 p->no = num;
	 p->right = NULL;
	 return p;
}

/* ツリーの作成 */
struct tree *make_tree(struct tree *node, int num) {
	 if( node == NULL ){
		 node = add_node(num);
		 return node;
	 }
	 if ( num > node->no )
		 node->left = make_tree(node->left,num);
	 if ( num < node->no )
		 node->right = make_tree(node->right,num);
	  return node;
}

/* ツリーの表示 */
void print_tree(struct tree *node) {
	 int i;
	 static int depth = 0;
	  if( node->left != NULL ){
		 depth ++;
		 print_tree(node->left);
		 depth --;
	 }
	  for( i = 0; i < depth; i++ )
		 printf("\t");
	 printf("[%2d]\n",node->no);
	  if( node->right != NULL){
		 depth ++;
		 print_tree(node->right);
		 depth --;
	 }
}


/* ツリーの探索関数 search を実装 */
/*探索対象が見つかったら0、見つからなかったら-1を返す*/
int search(int target,struct tree *node){
	printf("[%d]->",node->no);
	if(node -> no == target)return 0;
	else if(node -> left == NULL && node ->right == NULL)return -1;
	if(node -> no < target && node -> left   != NULL)return search(target,node->left);
	if(node -> no > target && node -> right != NULL)return search(target,node->right);
	return 0;
}

int main(void) {
	struct tree *root;
	int i, num;	
	int target;	  /*探索キー*/
	char c[] = "";/*yes or no 入力用*/
	int check=0;
	root=0;
	for( i = 0; i < KEY_SIZE; i++ ){
		printf("%d> ",i+1);
		num = get_num();
		if( i == 0 ){
			root = make_tree(NULL,num);
		}
		else{
			make_tree(root,num);
		}
	}
	print_tree(root);
	
	/* キー入力により実行が停止されるまで、探索キーの
	 * 入力と探索、結果の表示を繰り返す
	 */
	printf("key>");
	target = get_num();
	check = search(target,root);
	if(check== -1)printf("NotFound.\n");
	else          printf("Found.\n");
	
	while(1){
		printf("Do you wanna continue(yes/no)?");
		gets(c);
		/*strcmp:一致すれば0、一致しなければ0以外を返す。*/
		if(! strcmp(c,"yes")){
			printf("key>");
			target = get_num();
			check = search(target,root);
			if(check== -1)printf("NotFound.\n");
			else          printf("Found.\n");
		} else {
			break;
		}
	}
	return 0;
}

