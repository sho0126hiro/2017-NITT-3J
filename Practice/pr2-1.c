#include <stdio.h>
#include <string.h>/*strlen();使用のため*/

#define BF 1
#define KMP 0
#define TEXT_LENGTH 64
#define PATN_LENGTH 16
int next[PATN_LENGTH];

/* 文字列textから文字列patternを検索する(力まかせ法) */
int brute_force_search(char text[], char pattern[])
{
    int i = 0; /* 注目しているテキストの位置 */
    int j = 0; /* 注目しているパターンの位置 */
	int k = 0; /*パターンの先頭*/
    int text_len, patn_len;
	int check;

    text_len = strlen(text);    /* テキストの長さをセット */
    patn_len = strlen(pattern); /* パターンの長さをセット */
    while ( i < text_len && j < patn_len ) {
	/* テキストの最後尾に行き当たるか、パターンが見つかるまで繰り返す */
    	if(text[i]==pattern[j]){
			if(j==0)k=i;
		/*テキストとパターンを１文字比較し、一致したら*/
            i++;/*テキストの位置を１文字進める*/
            j++;/*パターンの位置を１文字進める*/
			check=1;
        } else {
			/*一致しなかったら*/
			if(j!=0){
          	  i=k+1;/*テキストの位置を現在注目している先頭から１つ進める*/
			}
			else i++;
            j=0;/*パターンの位置を先頭に戻す*/
			check=0;
    	}
	}
    /*もし、検索に成功したら*/
	if(check==1){
        /*パターンが見つかった位置を返す*/
		return k;
	}else {
		return -1;
   	/*失敗したら-1を返す*/
	}
}

/* ずらし表を作成する */
void init_next(char pattern[])
{
    /* 講義資料を参考に実装せよ */
}

/* 文字列textから文字列patternを検索する(KMP法) */
int kmp_search(char text[], char pattern[])
{
    /* 講義資料を参考に実装せよ */
}

int main(void)
{
    char text[TEXT_LENGTH+1];
	char text2[TEXT_LENGTH+1];
    char pattern[PATN_LENGTH+1];
	char pattern2[PATN_LENGTH+1];
    int position;
    strcpy(text,"xxxtartartayx");
    strcpy(pattern,"tartay");
	strcpy(text2,"pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko");
	strcpy(pattern2,"pyokopyokomu");

/*xxxtartartayx*/

	printf("1.xxxtartartayx\n");
#if BF
    printf("--- B F ---\n");
    printf("%s\n",text);
    position = brute_force_search(text, pattern);
    printf("position=%d\n",position);
#endif

#if KMP
    printf("--- KMP ---\n");
    init_next(pattern);
    printf("%s\n",text);
    position = kmp_search(text, pattern);
    printf("position=%d\n",position);
#endif

/*pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko*/

	printf("2.pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko\n");
#if BF
    printf("--- B F ---\n");
    printf("%s\n",text2);
    position = brute_force_search(text2, pattern2);
    printf("position=%d\n",position);
#endif

#if KMP
    printf("--- KMP ---\n");
    init_next(pattern2);
    printf("%s\n",text2);
    position = kmp_search(text2, pattern2);
    printf("position=%d\n",position);
#endif
    return 0;
}
