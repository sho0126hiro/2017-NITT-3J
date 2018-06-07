/*課題3-3*/
/*PATN_LENGTHの値を限りなく小さくせよ*/
#include <stdio.h>
#include <string.h>/*strlen();使用のため*/

#define BF 1
#define KMP 1
#define BM 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 12

int next[PATN_LENGTH];

/* テキストとパターンの不一致が見つかったときにどれだけずらすかを示す表 */
int skip[PATN_LENGTH];

#define uchar unsigned char
#define max(a,b) ((a)>(b)?a:b) /* 二つの数a,bのうち大きい方を返すマクロ */

/* 文字列textから文字列patternを検索する(力まかせ法) */
int brute_force_search(char text[], char pattern[])
{
	int i = 0; /* 注目しているテキストの位置 */
	int j = 0; /* 注目しているパターンの位置 */
	int text_len, patn_len;
	int k;
	int check=0;
	text_len = strlen(text);    /* テキストの長さをセット */
	patn_len = strlen(pattern); /* パターンの長さをセット */
	while ( i < text_len && j < patn_len ) {
		if(check==0)for(k=0;k<i;k++)printf(" ");
		printf("%c",pattern[j]);
	/* テキストの最後尾に行き当たるか、パターンが見つかるまで繰り返す */
		if(text[i]==pattern[j]){
			/*テキストとパターンを１文字比較し、一致したら*/
			i++;/*テキストの位置を１文字進める*/
			j++;/*パターンの位置を１文字進める*/
			check=1;
		} else {
			/*一致しなかったら*/
			printf(" ...failure\n");
			i=i-j+1;/*テキストの位置を現在注目している先頭から１つ進める*/
			j=0;/*パターンの位置を先頭に戻す*/
			check=0;
		}
	}
	/*もし、検索に成功したら*/
	if(j==patn_len){
		/*パターンが見つかった位置を返す*/
		printf(" ...success\n");
		return i-j;
	}else {
		return -1;
	/*失敗したら-1を返す*/
	}
}

/* ずらし表を作成する */
void init_next(char pattern[])
{
	int j,k,m,patn_len;
	patn_len = strlen(pattern); /* パターンの長さをセット */
	for(j=0;j<patn_len;j++){
		if(j<1)next[j]=1;
		else {
			for(k=1;k<j;k++){
				for(m=k;m<j && pattern[m] == pattern[m-k];m++);
				if(m==j)break;	
			}
			next[j]=k;
		}
	}
	/*表示部*/
	for(j=0;j<patn_len;j++){
		printf("%c: next[%2d] = %2d\n",pattern[j],j,next[j]);
	}
}

/* 文字列textから文字列patternを検索する(KMP法) */
int kmp_search(char text[], char pattern[])
{
	int i = 0; /* 注目しているテキストの位置 */
	int j = 0; /* 注目しているパターンの位置 */
	int text_len, patn_len;
	int check=0,k;
	text_len = strlen(text);    /* テキストの長さをセット */
	patn_len = strlen(pattern); /* パターンの長さをセット */

	while(i < text_len && j < patn_len){
		if(check==0)for(k=0;k<i;k++)printf(" ");
		printf("%c",pattern[j]);
		/* テキストの最後尾に行き当たるか、パターンが見つかるまで繰り返す */
		if(text[i]==pattern[j]){
		/*テキストとパターンを１文字比較し、一致したら*/
			i++;/*テキストの位置を１文字進める*/
			j++;/*パターンの位置を１文字進める*/
			check=1;
		} else {
			/*一致しなかったら*/
			printf(" ...failure\n");
			j=j-next[j];/*nextを利用してパターンの位置を戻す（jからnext[j]を引く）*/
			if(j<0){
				/*もし、jが負になったら*/
				i++;/*テキストの位置を１つ進める*/
				j++;/*パターンの位置を１つ進める*/
			}
			check=0;
		}
	}
	if(j==patn_len){
		printf(" ...success\n");
		return i-j;
		/*もし、検索に成功したら*/
		/*パターンが見つかった位置を返す*/
	} else {
		return -1;
	/*失敗したら*/
	/*-1を返す*/
	}
}

/* BM法用のずらし表を作成する */
void init_skip(uchar pattern[])
{
	int i,patn_len;
	patn_len = strlen(pattern);
	for(i=0;i<256;     i++) skip[i]          = patn_len;
	for(i=0;i<patn_len;i++) skip[pattern[i]] = patn_len-i-1;
	/*表示部*/
	for(i=0;i<patn_len;i++){
		printf("%c: skip[%3d] = %2d\n",pattern[i],pattern[i],skip[pattern[i]]);
	}
}


/* 文字列textから文字列patternを検索する(BM法) */
int bm_search(uchar text[], uchar pattern[]) {

	int i; /* 注目しているテキストの位置 */
	int j; /* 注目しているパターンの位置 */
	int text_len, patn_len;
	int k;
	
	text_len = strlen(text);    /* テキストの長さをセット */
	patn_len = strlen(pattern); /* パターンの長さをセット */
	/*iにテキストの最初の注目位置をセット*/
	i=patn_len-1;
	
	while( i < text_len ) {
		/*jにパターンの最初の注目位置をセット*/
		j=patn_len-1;
		for(k=0;k<i;k++)printf(">");
		
		while( text[i]==pattern[j] ) {
			if(j!=patn_len-1)for(k=0;k<i;k++)printf(" ");
			printf("%c",pattern[j]);
			if(j==0){
				printf(" ...success\n");
				return i;
				/*すべての文字が一致したら*/
				/*パターンが見つかった位置を返す*/
			}
			i--;/*テキストの位置を１文字戻す*/
			j--;/*パターンの位置を１文字戻す*/
			printf("\n");
		}
		if(j!=patn_len-1)for(k=0;k<i;k++)printf(" ");
		printf("%c",pattern[j]);
		printf(" ...failure");
		/*テキストの注目点(i)を，不一致になった文字に応じた分量だけずらす*/
		i=i+max(patn_len-j,skip[text[i]]);
		printf("\n");
	}
	/*-1を返す*/
	return -1;
}

int main(void)
{
	uchar text[TEXT_LENGTH+1];
	uchar pattern[PATN_LENGTH+1];
	uchar text2[TEXT_LENGTH+1];
	uchar pattern2[PATN_LENGTH+1];
	int position;
	strcpy(text,"aabbabcabc");
	strcpy(pattern,"abcab");
	strcpy(text2,"pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko");
	strcpy(pattern2,"pyokopyokomu");
	int check[10]={0};
/*aabbabcabc*/

	printf("1.aabbabcabc\n");

#if BF
	printf("--- B F ---\n");
	printf("%s\n",text);
	position = brute_force_search(text, pattern);
	check[0]=position;
	printf("position=%d\n",position);
#endif

#if KMP
	printf("--- KMP ---\n");
	init_next(pattern);
	printf("%s\n",text);
	position = kmp_search(text, pattern);
	check[1]=position;
	printf("position=%d\n",position);
#endif


#if BM
	printf("--- B M ---\n");
	init_skip(pattern);
	printf("%s\n",text);
	position = bm_search(text, pattern);
	printf("position=%d\n",position);
	check[2]=position;
#endif

/*pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko*/

	printf("2.pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko\n");

#if BF
	printf("--- B F ---\n");
	printf("%s\n",text2);
	position = brute_force_search(text2, pattern2);
	printf("position=%d\n",position);
	check[3]=position;
#endif

#if KMP
	printf("--- KMP ---\n");
	init_next(pattern2);
	printf("%s\n",text2);
	position = kmp_search(text2, pattern2);
	printf("position=%d\n",position);
	check[4]=position;
#endif


#if BM
	printf("--- B M ---\n");
	init_skip(pattern2);
	printf("%s\n",text2);
	position = bm_search(text2, pattern2);
	printf("position=%d\n",position);
	check[5]=position;
#endif
	if(check[0]!=-1 && check[1]!=-1 && check[2]!=-1 && check[3]!=-1 && check[4]!=-1 && check[5]!=-1)printf("\n\nALL SUCSESS");
return 0;
}

