#include <stdio.h>
#include <string.h>/*strlen();�g�p�̂���*/

#define BF 1
#define KMP 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 16
int next[PATN_LENGTH];

/* ������text���當����pattern����������(�͂܂����@) */
int brute_force_search(char text[], char pattern[])
{
	int i = 0; /* ���ڂ��Ă���e�L�X�g�̈ʒu */
	int j = 0; /* ���ڂ��Ă���p�^�[���̈ʒu */
	int text_len, patn_len;
	int k;
	int check=0;
	text_len = strlen(text);    /* �e�L�X�g�̒������Z�b�g */
	patn_len = strlen(pattern); /* �p�^�[���̒������Z�b�g */
	while ( i < text_len && j < patn_len ) {
		if(check==0)for(k=0;k<i;k++)printf(" ");
		printf("%c",pattern[j]);
	/* �e�L�X�g�̍Ō���ɍs�������邩�A�p�^�[����������܂ŌJ��Ԃ� */
		if(text[i]==pattern[j]){
			/*�e�L�X�g�ƃp�^�[�����P������r���A��v������*/
			i++;/*�e�L�X�g�̈ʒu���P�����i�߂�*/
			j++;/*�p�^�[���̈ʒu���P�����i�߂�*/
			check=1;
		} else {
			/*��v���Ȃ�������*/
			printf(" ...failure\n");
			i=i-j+1;/*�e�L�X�g�̈ʒu�����ݒ��ڂ��Ă���擪����P�i�߂�*/
			j=0;/*�p�^�[���̈ʒu��擪�ɖ߂�*/
			check=0;
		}
	}
	/*�����A�����ɐ���������*/
	if(j==patn_len){
		/*�p�^�[�������������ʒu��Ԃ�*/
		printf(" ...success\n");
		return i-j;
	}else {
		return -1;
	/*���s������-1��Ԃ�*/
	}
}

/* ���炵�\���쐬���� */
void init_next(char pattern[])
{
	int j,k,m,patn_len;
	patn_len = strlen(pattern); /* �p�^�[���̒������Z�b�g */
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
	/*�\����*/
	for(j=0;j<patn_len;j++){
		printf("%c:next[%2d] = %2d\n",pattern[j],j,next[j]);
	}
}

/* ������text���當����pattern����������(KMP�@) */
int kmp_search(char text[], char pattern[])
{
	int i = 0; /* ���ڂ��Ă���e�L�X�g�̈ʒu */
	int j = 0; /* ���ڂ��Ă���p�^�[���̈ʒu */
	int text_len, patn_len;
	int check=0,k;
	text_len = strlen(text);    /* �e�L�X�g�̒������Z�b�g */
	patn_len = strlen(pattern); /* �p�^�[���̒������Z�b�g */

	while(i < text_len && j < patn_len){
		if(check==0)for(k=0;k<i;k++)printf(" ");
		printf("%c",pattern[j]);
		/* �e�L�X�g�̍Ō���ɍs�������邩�A�p�^�[����������܂ŌJ��Ԃ� */
		if(text[i]==pattern[j]){
		/*�e�L�X�g�ƃp�^�[�����P������r���A��v������*/
			i++;/*�e�L�X�g�̈ʒu���P�����i�߂�*/
			j++;/*�p�^�[���̈ʒu���P�����i�߂�*/
			check=1;
		} else {
			/*��v���Ȃ�������*/
			printf(" ...failure\n");
			j=j-next[j];/*next�𗘗p���ăp�^�[���̈ʒu��߂��ij����next[j]�������j*/
			if(j<0){
				/*�����Aj�����ɂȂ�����*/
				i++;/*�e�L�X�g�̈ʒu���P�i�߂�*/
				j++;/*�p�^�[���̈ʒu���P�i�߂�*/
			}
			check=0;
		}
	}
	if(j==patn_len){
		printf(" ...success\n");
		return i-j;
		/*�����A�����ɐ���������*/
		/*�p�^�[�������������ʒu��Ԃ�*/
	} else {
		return -1;
	/*���s������*/
	/*-1��Ԃ�*/
	}
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
