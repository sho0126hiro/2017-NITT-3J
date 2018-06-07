/* �n�b�V���@�ɂ��f�[�^�Ǘ��i�`�F�C���@�Łj */

#include <stdio.h>
#include <stdlib.h>
#define ERROR    -1
#define HASH_SIZE  9
typedef struct character {
	int no;                         /* �L�[ */
	char name[16];                  /* ���O */
	struct character *next_addr;    /* ���̃f�[�^�̃A�h���X */
} CHARACTER;
CHARACTER *HashTable[HASH_SIZE];

/* ���l�̓��͗p�֐� */
int get_num(void)
{
	int  i;
	int  d = 0;
	int  c = 0;
	rewind(stdin);
	for( i = 0; i < 5 && c != '\n' ; i++ ) {
		/* 5�P�^�܂� */
		c = getchar();
		if ( c == '\n' ) break;
		d = d * 10 + c - '0';
	}
	rewind(stdin);
	return d;
}

/* �n�b�V���\���烊�X�g�\���ŕ���ł���l�q��\������ */
void disp(void)
{
	int i = 0;
	struct character *current_addr;
	for( i = 0; i < HASH_SIZE; i++ ) {
		printf("-|%d|",i);
		printf("%2d|-",HashTable[i]);
		if( HashTable[i] != NULL) {
			/* ���X�g�\���ŘA�����Ă���f�[�^��\�� */
			current_addr=HashTable[i];
			while(1){
				printf("-|%d|",i);
				printf("%d:%d:%s:%d|-",current_addr,current_addr->no,current_addr->name,current_addr->next_addr);
				current_addr=current_addr->next_addr;
				if(current_addr==NULL)break;
			}
		}
		printf("\n");
	}
}

/* �n�b�V���l�̌v�Z */
int hash(int h)
{
	return h % HASH_SIZE;
}

/* �f�[�^�̒ǉ� */
void add(void)
{
	struct character *p;
	struct character *q;
	int i, j;
	int h;
	/* �ǉ��f�[�^�̂��߂̃��������m�� */
	p=(struct character *)malloc(sizeof(*p));
	q=(struct charactar *)malloc(sizeof(*q));
	printf("NO��");
	p->no = get_num();
	printf("���O��");
	fgets(p->name,16,stdin);
	for( j=0; p->name[j] != '\n' && j != 15; j++ );
	p->name[j] = '\0';
	/* �����s�R�[�h���폜���邽�߂̏��� */
	p->next_addr = NULL;
	h = hash( p->no );

	if( HashTable[h] == NULL ) {
		/* HashTable[h]�ɂ܂��f�[�^�����݂��ĂȂ������Ƃ��̏��� */
		HashTable[h]=p;
	} else {
		/* HashTable[h]�Ɋ��Ƀf�[�^�����݂��Ă����Ƃ��̏��� */
		q=HashTable[h];
		while(q->next_addr!=NULL){
			q=q->next_addr;
		}
		q->next_addr=p;
	}
	disp();
}

/* �f�[�^�̍폜 */
int del(void)
{
	int i, h;
	struct character *current_addr,*head,*target;
	int point;
	disp();
	printf("NO��");
	point = get_num();
	h = hash(point);
	/* �L�[������������Y���f�[�^���폜����disp()���Ă�
	* �L�[��������Ȃ�������"NOT FOUND."��\������ERROR��Ԃ�
	*/
	if(HashTable[h]==NULL){
		printf("NOT FOUND\n");
		return ERROR;
	}
	head=HashTable[h];
	current_addr=HashTable[h];
	target=HashTable[h];
	while(current_addr->no!=point){
		/*  */
		if(current_addr==NULL){
			printf("NOT FOUND\n");
			return ERROR;
		}
		current_addr=current_addr->next_addr;
	}
	/*found,current_addr->key*/
	printf("a");
	current_addr=head;
	if(head->no==point){
		//head=head->next_addr;
		HashTable[h]=head->next_addr;
		disp();
		return;
	}
	while(1){
		if(current_addr->next_addr->no==point){
			/*?i??*/
			current_addr->next_addr=current_addr->next_addr->next_addr;
			break;
		}
		current_addr=current_addr->next_addr;
	}
	disp();
}

/* �f�[�^�̒T�� */
int search(void)
{
	int i, h;
	struct character *current_addr,*head,*target;
	int point,check=0;
	printf("NO��");
	point = get_num();
	h = hash(point);
	/* �L�[������������Y���f�[�^(�L�[&�Ή����閼�O)��\������disp()
	* ���Ă�
	* �L�[��������Ȃ�������"NOT FOUND."��\������ERROR��Ԃ�
	*/
	current_addr=HashTable[h];
	while(current_addr!=NULL){
		if(current_addr->no == point){
			printf("�T���L�[%d�ɑΉ�����f�[�^��%s�ł��B\n",point,current_addr->name);
			printf("-|%d|%d:%d:%s:%d|-\n",h,current_addr,current_addr->no,current_addr->name,current_addr->next_addr);
			printf("****************************************************\n\n");
			disp();
			check=1;
			break;
		}
		current_addr=current_addr->next_addr;
	}
	if(!check)printf("NOT FOUND\n");
}


/* ���j���[ */
int menu(void)
{
	int c;
	while( 1 ) {
		printf("1.�\\��\n");      // �ۑ�5�Ɠ��l�̗��R�ŁC"�\"��"��"�̊Ԃ�"\"��}��
		printf("2.�ǉ�\n");
		printf("3.�폜\n");
		printf("4.�T��\n");
		printf("5.�I��\n");
		c = get_num();
		if( c >= 1 && c <= 5 )  break;
		else printf("1?5�܂ł̐�������͂��Ă�������\n");
	}
	switch( c ) {
		case 1:
			disp();
			break;
		case 2:
			add();
			break;
		case 3:
			del();
			break;
		case 4:
			search();
			break;
		case 5:
			return 1;
	}
	return 0;
}

int main(void)
{
	int i, end = 0;
	/* �n�b�V���\�������� */
	for( i = 0; i < HASH_SIZE; i++ )
		HashTable[i] = NULL;
	while( !end ) {
		end = menu();
	}
	return 0;
}