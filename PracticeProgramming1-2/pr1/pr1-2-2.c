#include <stdio.h>
#include <time.h>/*clock();*/
/* dev-c++�R���p�C���ł́C��L��"<"��">"��"stdio.h"�Ƃ̊ԂɃX�y�[�X�������
   �R���p�C�����ɕs����������邱�Ƃ�����̂ŁC�X�y�[�X�͓���Ȃ��悤�� */

#define LINEAR 0  /* 1:���`�T���C0:�񕪒T�� */
#define NORMAL 0  /* 1:�ʏ�ŁC  0:�ԕ���   */
#define LOOP   0  /* 1:���[�v�ŁC0:�ċA��   */

#define N  30000  /* �T�����郌�R�[�h�� (���ӁF���̒l"����"��ς��Ă��A���ۂ̌������R�[�h���͑����Ȃ��j */

/* ���`�T�� */
int l_search(int data[], int target)
{
	int i, count = 0;
#if NORMAL   /* �ʏ�� */
	for ( i = 0; i < N; i++ )
		if ( target == data[i] ) {
			return i;
		}
	return -1;
#else        /* �ԕ��� */
	data[N-1]=target;
	/* ���[�v�ɔ�r�����͕s�v�i�f�[�^���Ɍ����L�[�������Ă������Ă��Ō�ɔԕ��͌����邩��j */
	while(1){
		if(data[count]==target) break;/* �݂������烋�[�v�𔲂��� */
		count++;
	}
	if(count==N-1)return -1;/* �ԕ������݂���Ȃ�������-1��Ԃ� */
	return count;
	/* �f�[�^���݂�������break�����Ƃ��̓Y�����̒l��Ԃ� */
#endif
}

/* �N�C�b�N�\�[�g */
void quick(int d[],int left,int right){
	/*�֐����̕ϐ��� data[]����d[]�ɕύX���Ă��܂�*/
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

/* �񕪒T�� */
int b_search(int data[], int low, int high, int target)
{
	int mid;
#if LOOP 
	/* ���[�v�o�[�W���� */
	while(low<=high){
	/* low <= high �̊Ԃ̓��[�v�ilow > high�Ȃ猩����Ȃ������j */
		mid=(low+high)/2;/* mid �� low �� high �̒��Ԓl���Z�b�g */
		if(data[mid]>target)high=mid-1;
		/* data[mid] ��� target ����������� high �� mid-1 �� */
		else if(data[mid]<target)low=mid+1;
		/* data[mid] ��� target ���傫����� low �� mid+1 �� */
		else return mid;
		/* data[mid] == target ��������mid��Ԃ�*/
	}
	return -1;
	/* ������Ȃ������Ȃ� -1 ��Ԃ� */
	
#else
	/* �ċA�o�[�W���� */
	if(low>high)return -1;
	/* low > high �Ȃ猩����Ȃ������Ƃ������Ƃ� -1 ��Ԃ� */
	mid=(low+high)/2;
	/* mid �� low �� high �̒��Ԓl���Z�b�g */
	if(data[mid]>target)return b_search(data,low,mid-1,target);
	/* data[mid] ��� target ����������ΑO�������ōċA */
	else if(data[mid]<target)return b_search(data,mid+1,high,target);
	/* data[mid] ��� target ���傫����Ό㔼�����ōċA */
	else return mid;
	/* data[mid] == target �������猩�������Ƃ������Ƃ� mid ��Ԃ� */

#endif
}

/* ���C�� */
int main(void)
{
	int a[N], i, target, work[N], index;
	int j;
	double Pt[50];/*processing time*/
	double sum=0;
	clock_t start, end;
	for(j=0;j<10;j++){
		for( i = 0; i < N; i++ ) work[i] = rand() % N;
		start=clock(); /*�J�n�����̎擾*/
#if LINEAR
#else
		quick(work,0,N-1);
#endif
		for( target = N/2-500; target < N/2+500; target++ ) {  // �������R�[�h����ς���ɂ́A���̕ӂ���C������K�v������
#if LINEAR
			index = l_search(work,target);
#else
			index = b_search(work,0,N-1,target);
#endif
			end=clock();/*�I������*/
			
			/*printf("TARGET=%d: ", target);
			if ( index != -1 )	printf("��\n");
			  else					printf("�~\n");*/
			  
		}
		Pt[j]=(double)(end-start)/CLOCKS_PER_SEC;
		//printf("[%02d]��������:%f�b\n",j+1,Pt[j]);
		printf("%f\n",Pt[j]);
		/*�J�n�����ƏI�������̍��F��������*/
		sum+=Pt[j];/*���Z*/
	}
	printf("LINER:%d\nNORMAL:%d\nLOOP:%d\n",LINEAR,NORMAL,LOOP);
	printf("10��̕��Ϗ������ԁF%lf�b\n",sum/10);
	return 0;
}
