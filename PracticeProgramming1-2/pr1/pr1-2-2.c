#include <stdio.h>
#include <time.h>/*clock();*/
/* dev-c++コンパイラでは，上記の"<"や">"と"stdio.h"との間にスペースを入れると
   コンパイル時に不具合が発生することがあるので，スペースは入れないように */

#define LINEAR 0  /* 1:線形探索，0:二分探索 */
#define NORMAL 0  /* 1:通常版，  0:番兵版   */
#define LOOP   0  /* 1:ループ版，0:再帰版   */

#define N  30000  /* 探索するレコード数 (注意：この値"だけ"を変えても、実際の検索レコード数は増えない） */

/* 線形探索 */
int l_search(int data[], int target)
{
	int i, count = 0;
#if NORMAL   /* 通常版 */
	for ( i = 0; i < N; i++ )
		if ( target == data[i] ) {
			return i;
		}
	return -1;
#else        /* 番兵版 */
	data[N-1]=target;
	/* ループに比較条件は不要（データ中に検索キーがあっても無くても最後に番兵は見つかるから） */
	while(1){
		if(data[count]==target) break;/* みつかったらループを抜ける */
		count++;
	}
	if(count==N-1)return -1;/* 番兵しかみつからなかったら-1を返す */
	return count;
	/* データがみつかったらbreakしたときの添え字の値を返す */
#endif
}

/* クイックソート */
void quick(int d[],int left,int right){
	/*関数内の変数名 data[]からd[]に変更しています*/
	if(left>=right)return;
	int l,r;
	int pivot,tmp;
	l=left;
	r=right;
	pivot=d[left];

	while(1){
		while(d[left]<=pivot && left<right)left++;
		while(d[right]>pivot && left<right)right--;
		if(left>=right)break;
		tmp      = d[left];
		d[left]  = d[right];
		d[right] = tmp;
	}
	left--;
	tmp=d[l];
	d[l]=d[left];
	d[left]=tmp;
	
	quick(d,l,left);
	quick(d,left+1,r);
	
}

/* 二分探索 */
int b_search(int data[], int low, int high, int target)
{
	int mid;
#if LOOP 
	/* ループバージョン */
	while(low<=high){
	/* low <= high の間はループ（low > highなら見つからなかった） */
		mid=(low+high)/2;/* mid に low と high の中間値をセット */
		if(data[mid]>target)high=mid-1;
		/* data[mid] より target が小さければ high を mid-1 に */
		else if(data[mid]<target)low=mid+1;
		/* data[mid] より target が大きければ low を mid+1 に */
		else return mid;
		/* data[mid] == target だったらmidを返す*/
	}
	return -1;
	/* 見つからなかったなら -1 を返す */
	
#else
	/* 再帰バージョン */
	if(low>high)return -1;
	/* low > high なら見つからなかったということで -1 を返す */
	mid=(low+high)/2;
	/* mid に low と high の中間値をセット */
	if(data[mid]>target)return b_search(data,low,mid-1,target);
	/* data[mid] より target が小さければ前半部分で再帰 */
	else if(data[mid]<target)return b_search(data,mid+1,high,target);
	/* data[mid] より target が大きければ後半部分で再帰 */
	else return mid;
	/* data[mid] == target だったら見つかったということで mid を返す */

#endif
}

/* メイン */
int main(void)
{
	int a[N], i, target, work[N], index;
	int j;
	double Pt[50];/*processing time*/
	double sum=0;
	clock_t start, end;
	for(j=0;j<10;j++){
		for( i = 0; i < N; i++ ) work[i] = rand() % N;
		start=clock(); /*開始時刻の取得*/
#if LINEAR
#else
		quick(work,0,N-1);
#endif
		for( target = N/2-500; target < N/2+500; target++ ) {  // 検索レコード数を変えるには、この辺りを修正する必要がある
#if LINEAR
			index = l_search(work,target);
#else
			index = b_search(work,0,N-1,target);
#endif
			end=clock();/*終了時刻*/
			
			/*printf("TARGET=%d: ", target);
			if ( index != -1 )	printf("○\n");
			  else					printf("×\n");*/
			  
		}
		Pt[j]=(double)(end-start)/CLOCKS_PER_SEC;
		//printf("[%02d]処理時間:%f秒\n",j+1,Pt[j]);
		printf("%f\n",Pt[j]);
		/*開始時刻と終了時刻の差：処理時間*/
		sum+=Pt[j];/*加算*/
	}
	printf("LINER:%d\nNORMAL:%d\nLOOP:%d\n",LINEAR,NORMAL,LOOP);
	printf("10回の平均処理時間：%lf秒\n",sum/10);
	return 0;
}
