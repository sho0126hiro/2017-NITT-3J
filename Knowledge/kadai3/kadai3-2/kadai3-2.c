#include <stdio.h>

void expand(char data[512],char pattern[64][64]);
void outline(char p[64][64]);
void Display(char d[64][64]);
void smooth(char p[64][64]);
void smoothDecision(char p[64][64]);

//main*************************************************************************/
int main(){
	int i,j,x,y;
	char data[512];
	char pattern[64][64]={0};
	unsigned char b=128;
	FILE *fp;
	
	fp=fopen("01.img","rb");
	if (fp==NULL) {
		printf("can't open a file\n");
		exit(1);
	}
	fread(data,512,1,fp);
	fclose(fp);
	expand(data,pattern);
	Display(pattern);
	smooth(pattern);
	printf("2\n\n");
	Display(pattern);
	return 0;
}
//�X���[�W���O***************************************************************/
void smooth(char p[64][64]){
	smoothDecision(p);
	for(int j=1;j<63;j++){
		for(int i=1;i<63;i++){
			if(p[j][i]==2){
				p[j][i]=0;
			}
		}
	}
}

//�X���[�W���O2(����)********************************************************/
void smoothDecision(char p[64][64]){
	for(int j=1;j<63;j++){
		for(int i=1;i<63;i++){
		
			if(	p[j-1][i-1]    && p[j  ][i-1] && p[j+1][i-1] &&
				p[j-1][i  ]==0 && p[j  ][i  ] && p[j+1][i  ] &&
				p[j-1][i+1]    && p[j  ][i+1] && p[j+1][i+1]){
				p[j-1][i  ]=1;	
			}
			if(	p[j-1][i-1]==0 && p[j  ][i-1] && p[j+1][i-1] &&
				p[j-1][i  ]    && p[j  ][i  ] && p[j+1][i  ] &&
				p[j-1][i+1]==0 && p[j  ][i+1] && p[j+1][i+1]){
				p[j-1][i  ]=2;
			}
			//�E��]
			if(	p[j-1][i-1] && p[j][i-1]    && p[j+1][i-1] &&
				p[j-1][i  ] && p[j][i  ]    && p[j+1][i  ] &&
				p[j-1][i+1] && p[j][i+1]==0 && p[j+1][i+1]){
				p[j  ][i+1]=1;
			
			}
			if(	p[j-1][i-1]    && p[j][i-1] && p[j+1][i-1] &&
				p[j-1][i  ]    && p[j][i  ] && p[j+1][i  ] &&
				p[j-1][i+1]==0 && p[j][i+1] && p[j+1][i+1]==0){
				p[j][i+1]=2;
			}
			//������x�E��]
			if(	p[j-1][i-1] && p[j][i-1] && p[j+1][i-1]    &&
				p[j-1][i  ] && p[j][i  ] && p[j+1][i  ]==0 &&
				p[j-1][i+1] && p[j][i+1] && p[j+1][i+1]){
				p[j+1][i]=1;
			}
			if(	p[j-1][i-1] && p[j][i-1] && p[j+1][i-1]==0 &&
				p[j-1][i  ] && p[j][i  ] && p[j+1][i  ]    &&
				p[j-1][i+1] && p[j][i+1] && p[j+1][i+1]==0){
				p[j+1][i]=2;
			}
			//������x�E��]
			if(	p[j-1][i-1] && p[j][i-1]==0 && p[j+1][i-1] &&
				p[j-1][i  ] && p[j][i  ]    && p[j+1][i  ] &&
				p[j-1][i+1] && p[j][i+1]    && p[j+1][i+1]){
				p[j][i-1]=1;
			}
			if(	p[j-1][i-1]==0 && p[j][i-1] && p[j+1][i-1]==0 &&
				p[j-1][i  ]    && p[j][i  ] && p[j+1][i  ]    &&
				p[j-1][i+1]    && p[j][i+1] && p[j+1][i+1]){
				p[j][i-1]=2;
			}
		}
	
	}
	//����I���
}

/*
	p[j-1][i-1]==1 && p[j][i-1]==1 && p[j+1][i-1]==1 &&
	p[j-1][i]==1 && p[j][i]==1 && p[j+1][i]==1 &&
	p[j-1][i+1]==1 && p[j][i+1]==1 && p[j+1][i+1]==1	
*/

//�񎟌��z��Ɋi�[����֐�***************************************************/
void expand(char data[512],char pattern[64][64]){
	int i,j,k;
	unsigned char b=128;
	
	for(k=0;k<64;k++){
		for(j=1;j<8;j++){
			b=128;
			for(i=0;i<8;i++){
				if((data[k*8+j]&b)==0){
					pattern[k][8*j+i]=0;
				}else{
					pattern[k][8*j+i]=1;
				}
				b=b>>1;
			}
		}
	}
}

//�֊s���o�֐�**********************************************************/
void outline(char p[64][64]){
	int i,j;
	//������`�F�b�N(0�s�ځC63�s�ځC0��ځC63��ڂ͔��肵�Ȃ��j
	for(j=1;j<63;j++){
		for(i=1;i<63;i++){
			if(p[j-1][i]!=0 && p[j+1][i]!=0){//�Ώە����̏㉺����
				if(p[j][i-1]!=0 && p[j][i+1]!=0){//�Ώە����̍��E����
					p[j][i]=2;
				}
			}
		}
	}
	for(j=1;j<63;j++){
		for(i=1;i<63;i++){
			if(p[j][i]==2){
				p[j][i]=0;
			}
		}
	}
}
//�\���֐�********************************************************************//
void Display(char d[64][64]){
	int i,j;
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			printf("%d",d[j][i]);
		}
		printf("\n");
	}
}

