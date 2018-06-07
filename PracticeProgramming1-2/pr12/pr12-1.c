/* �i�b�v�U�b�N���i���I�v��@�ɂ���@�j */

/*
==memo==
���s��gcc
a x(�i�b�v�U�b�N�̃T�C�Y).exe
�Ŏ��s

*/

#include<stdio.h>
#include<stdlib.h>

/* �z��size�Avalue�͂��ꂼ��ו��̑傫���Ɖ��l��\�킵�Ă���
 * �����Y�������m���Ή����Ă���(��F�ו�0�̑傫����size[0]�A���l��value[0]�j�B
 */

/* �ו��̑傫�� */
	int size[] = {2, 3, 5, 7, 9, 15};
	
/* �ו��̉��l */
	int value[] = {2, 4, 7, 11, 14, 24};
	
/* �ו��̎�ނ̐� */
	#define AS (sizeof(size)/sizeof(size[0]))
	
/* �i�b�v�U�b�N�̑傫���̏�� */
	#define MAX_M   200

void DynamicProgramming(int N, int Nsize[], int Nvalue[]){
	int i,j;
		
	/* �����_�Ńi�b�v�U�b�N�ɋl�ߍ��񂾉ו��̉��l�̍��v */
	int total[MAX_M];
	
	/* �Ō�ɑI�񂾉ו� */
	int choice[MAX_M];
	
	/* �ו�i����ꂽ���̉��l�̍��v */
	int repack_total;
	
	/* �z����N���A���Ă��� */
	for(i=0;i<=N;i++){
		total[i] = 0;
		choice[i] = -1;
	}
	/* �ו� i = 0~AS �܂ł��l���ɓ���� */
	for(i=0;i<AS;i++){
		/* �傫��j(=Nsize[i])�̃i�b�v�U�b�N�ɑ΂��āA�ו����l�ߍ���ł݂� */
		//repack_total=0;
		for(j=0;j<=N;j++){/*j:�i�b�v�U�b�N�̃T�C�Y*/
			if(Nsize[i] <= j){
				/* 	�����ו�i����ꂽ�Ƃ���ƁA���l�̍��v�͂�����ɂȂ邩���v�Z���āA
					�ϐ�repack_total�Ɋi�[ */				
				repack_total = total[j-Nsize[i]]+Nvalue[i];
				if(repack_total > total[j]){
				/* �ו�i����ꂽ����(����Ȃ����)���l���傫���Ȃ�̂Ȃ�A�ו�i������ */
					total[j]=repack_total;
					choice[j]=i;
				}
			}
			//else choice[j]=choice[j-1];
		}
		/* �z��total�Achoice�̒��g��\������ */
		printf("i = %d\n",i);
		printf("choice = ");
		for(j=0;j<=N;j++)
			printf("%2d ",choice[j]);
		printf("\n");
		
	}
	i=N;
	/* �ǂ̉ו����i�b�v�U�b�N�ɓ��ꂽ����\������ */
	while(choice[i] != -1){
		printf("�i�� %d �i���l%d�j���l�ߍ���\n", choice[i],Nvalue[choice[i]]);
		i = i - Nsize[choice[i]];
	}
	printf("���l�̍��v = %d\n",total[N]);
}

int main(int argc, char *argv[]){

	/* �i�b�v�U�b�N�̑傫�� */
	int m;
	
	/* �����̐�������Ă��Ȃ����A�i�b�v�U�b�N�̑傫��������𒴂��Ă��Ȃ���
	   ����i�K�؂Ȉ����̐��A�������͒l���ݒ肳��Ă��Ȃ��ꍇ�A�ēx���͂����߂�j
	*/
	/* �R�}���h��������i�b�v�U�b�N�̑傫���𓾂�
		   argv[0]:File name(a)/argv[1]:�����ia y.exe��y)
	 */
	m = atoi(argv[1]);
	while(m>MAX_M || m==0){
		printf("�������ݒ肳��Ă��Ȃ����A����𒴂��Ă��܂��B\n�i�i�b�v�U�b�N�̃T�C�Y�̏����200)\n�ēx���͂��Ă��������B��");
		scanf("%d",&m);
	}
	printf("Size of knapsack is %d\n",m);
	
	DynamicProgramming(m,size,value);
	
	return 0;
}