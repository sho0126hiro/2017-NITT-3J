#include <stdio.h>
#include <string.h>/*strlen();�g�p�̂���*/

#define BF 1
#define KMP 0
#define TEXT_LENGTH 64
#define PATN_LENGTH 16
int next[PATN_LENGTH];

/* ������text���當����pattern����������(�͂܂����@) */
int brute_force_search(char text[], char pattern[])
{
    int i = 0; /* ���ڂ��Ă���e�L�X�g�̈ʒu */
    int j = 0; /* ���ڂ��Ă���p�^�[���̈ʒu */
	int k = 0; /*�p�^�[���̐擪*/
    int text_len, patn_len;
	int check;

    text_len = strlen(text);    /* �e�L�X�g�̒������Z�b�g */
    patn_len = strlen(pattern); /* �p�^�[���̒������Z�b�g */
    while ( i < text_len && j < patn_len ) {
	/* �e�L�X�g�̍Ō���ɍs�������邩�A�p�^�[����������܂ŌJ��Ԃ� */
    	if(text[i]==pattern[j]){
			if(j==0)k=i;
		/*�e�L�X�g�ƃp�^�[�����P������r���A��v������*/
            i++;/*�e�L�X�g�̈ʒu���P�����i�߂�*/
            j++;/*�p�^�[���̈ʒu���P�����i�߂�*/
			check=1;
        } else {
			/*��v���Ȃ�������*/
			if(j!=0){
          	  i=k+1;/*�e�L�X�g�̈ʒu�����ݒ��ڂ��Ă���擪����P�i�߂�*/
			}
			else i++;
            j=0;/*�p�^�[���̈ʒu��擪�ɖ߂�*/
			check=0;
    	}
	}
    /*�����A�����ɐ���������*/
	if(check==1){
        /*�p�^�[�������������ʒu��Ԃ�*/
		return k;
	}else {
		return -1;
   	/*���s������-1��Ԃ�*/
	}
}

/* ���炵�\���쐬���� */
void init_next(char pattern[])
{
    /* �u�`�������Q�l�Ɏ������� */
}

/* ������text���當����pattern����������(KMP�@) */
int kmp_search(char text[], char pattern[])
{
    /* �u�`�������Q�l�Ɏ������� */
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
