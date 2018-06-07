#include <stdio.h>
#include <string.h>/*strlen();�g�p�̂���*/

#define BF 1
#define KMP 1
#define BM 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 256
int next[PATN_LENGTH];

/* �e�L�X�g�ƃp�^�[���̕s��v�����������Ƃ��ɂǂꂾ�����炷���������\ */
int skip[PATN_LENGTH];

#define uchar unsigned char
#define max(a,b) ((a)>(b)?a:b) /* ��̐�a,b�̂����傫������Ԃ��}�N�� */

/* ������text���當����pattern����������(�͂܂����@) */
int brute_force_search(char text[], char pattern[])
{
	int i = 0; /* ���ڂ��Ă���e�L�X�g�̈ʒu */
	int j = 0; /* ���ڂ��Ă���p�^�[���̈ʒu */
	int text_len, patn_len;
	
	text_len = strlen(text);    /* �e�L�X�g�̒������Z�b�g */
	patn_len = strlen(pattern); /* �p�^�[���̒������Z�b�g */
	while ( i < text_len && j < patn_len ) {
	/* �e�L�X�g�̍Ō���ɍs�������邩�A�p�^�[����������܂ŌJ��Ԃ� */
		if(text[i]==pattern[j]){
			/*�e�L�X�g�ƃp�^�[�����P������r���A��v������*/
			i++;/*�e�L�X�g�̈ʒu���P�����i�߂�*/
			j++;/*�p�^�[���̈ʒu���P�����i�߂�*/
		} else {
			/*��v���Ȃ�������*/
			i=i-j+1;/*�e�L�X�g�̈ʒu�����ݒ��ڂ��Ă���擪����P�i�߂�*/
			j=0;/*�p�^�[���̈ʒu��擪�ɖ߂�*/
		}
	}
	/*�����A�����ɐ���������*/
	if(j==patn_len){
		/*�p�^�[�������������ʒu��Ԃ�*/
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
}

/* ������text���當����pattern����������(KMP�@) */
int kmp_search(char text[], char pattern[])
{
	int i = 0; /* ���ڂ��Ă���e�L�X�g�̈ʒu */
	int j = 0; /* ���ڂ��Ă���p�^�[���̈ʒu */
	int text_len, patn_len;
	int check;

	text_len = strlen(text);    /* �e�L�X�g�̒������Z�b�g */
	patn_len = strlen(pattern); /* �p�^�[���̒������Z�b�g */

	while(i < text_len && j < patn_len){
		/* �e�L�X�g�̍Ō���ɍs�������邩�A�p�^�[����������܂ŌJ��Ԃ� */
		if(text[i]==pattern[j]){
		/*�e�L�X�g�ƃp�^�[�����P������r���A��v������*/
			i++;/*�e�L�X�g�̈ʒu���P�����i�߂�*/
			j++;/*�p�^�[���̈ʒu���P�����i�߂�*/
		} else {
			/*��v���Ȃ�������*/
			j=j-next[j];/*next�𗘗p���ăp�^�[���̈ʒu��߂��ij����next[j]�������j*/
			if(j<0){
				/*�����Aj�����ɂȂ�����*/
				i++;/*�e�L�X�g�̈ʒu���P�i�߂�*/
				j++;/*�p�^�[���̈ʒu���P�i�߂�*/
			}
		}
	}
	if(j==patn_len)return i-j;
	/*�����A�����ɐ���������*/
	/*�p�^�[�������������ʒu��Ԃ�*/
	else return -1;
	/*���s������*/
	/*-1��Ԃ�*/
}

/* BM�@�p�̂��炵�\���쐬���� */
void init_skip(uchar pattern[])
{
	int i,patn_len;
	patn_len = strlen(pattern);
	for(i=0;i<256;     i++) skip[i]          = patn_len;
	for(i=0;i<patn_len;i++) skip[pattern[i]] = patn_len-i-1;
}


/* ������text���當����pattern����������(BM�@) */
int bm_search(uchar text[], uchar pattern[]) {

	int i; /* ���ڂ��Ă���e�L�X�g�̈ʒu */
	int j; /* ���ڂ��Ă���p�^�[���̈ʒu */
	int text_len, patn_len;

	text_len = strlen(text);    /* �e�L�X�g�̒������Z�b�g */
	patn_len = strlen(pattern); /* �p�^�[���̒������Z�b�g */
	/*i�Ƀe�L�X�g�̍ŏ��̒��ڈʒu���Z�b�g*/
	i=patn_len-1;

	while( i < text_len ) {
	/*j�Ƀp�^�[���̍ŏ��̒��ڈʒu���Z�b�g*/
		j=patn_len-1;
		while( text[i]==pattern[j] ) {
			if(j==0){
				return i;
				/*���ׂĂ̕�������v������*/
				/*�p�^�[�������������ʒu��Ԃ�*/
			}
			i--;/*�e�L�X�g�̈ʒu���P�����߂�*/
			j--;/*�p�^�[���̈ʒu���P�����߂�*/
		}
	/*�e�L�X�g�̒��ړ_(i)���C�s��v�ɂȂ��������ɉ��������ʂ������炷*/
		i=i+max(patn_len-j,skip[text[i]]);
	}
	/*-1��Ԃ�*/
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
	
/*aabbabcabc*/

	printf("1.aabbabcabc\n");

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


#if BM
	printf("--- B M ---\n");
	init_skip(pattern);
	printf("%s\n",text);
	position = bm_search(text, pattern);
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


#if BM
	printf("--- B M ---\n");
	init_skip(pattern2);
	printf("%s\n",text2);
	position = bm_search(text2, pattern2);
	printf("position=%d\n",position);
#endif

return 0;
}
