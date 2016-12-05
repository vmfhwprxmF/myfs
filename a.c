#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

char bootblock[2];  //  부트블럭은 16비트 고정
typedef struct data
{
	int direct;		//직접
	struct data *indirect;  //간접 자기참조구조체
}data;

typedef struct 
{
	unsigned char bit_inode[64];		// i-node 사용여부 (512)
	unsigned char bit_data[128];	// data block 사용여부 (1024)
}super;
super supers;

typedef struct 
{
	_Bool file; 					// 0-file, 1-dir 
	int when[6];					// 시간저장
	int size;     					// 파일크기
	//data num;						// 데이터 블럭 번호
/*
	struct i_node *direct;
	int *s_indirect;				//자기참조구조체 구현 필요함
	int *d-indirect;
 */
}INODE;
INODE i_node[512];

typedef struct
{
	char data[128];				// 128바이트
}DATA_BLOCK; 
DATA_BLOCK data_block[1024];

typedef struct
{
	char *l_link;	// 왼쪽 파일 링크
	char name[4];		// 본 파일 이름
	char *r_link;		// 오른쪽 파일 링크
}binary_tree;

char check_bit(int num)					//비트사용함수(삽입,제거)
{
	int i;
	unsigned int n=128;
	int mask = 1 << (8-num);
	return mask;
}

int find_ibit(unsigned char *num)		//비트 0인 가장 가까운 inode 찾는 함수
{
	int i;
	for(i=0;i<64;i++)
	{
		if(num[i]<128)
		{
			return i*8+1;
			break;
		}
		else if(num[i]-128<64)
		{
			return i*8+2;
			break;
		}
		else if(num[i]-(128+64)<32)
		{	
			return i*8+3;
			break;
		}
		else if(num[i]-(128+64+32)<16)
		{	
			return i*8+4;
			break;
		}
		else if(num[i]-(128+64+32+16)<8)
		{	
			return i*8+5;
			break;
		}
		else if(num[i]-(128+64+32+16+8)<4)
		{
			return i*8+6;
			break;
		}
		else if(num[i]-(128+64+32+16+8+4)<2)
		{
			return i*8+7;
			break;
		}
		else if(num[i]-(128+64+32+16+8+4+2)<1)
		{
			return i*8+8;
			break;
		}
	}
}
int find_dbit(unsigned char *num)		//비트 0인 가장 가까운 inode 찾는 함수
{
	int i;
	for(i=0;i<128;i++)
	{
		if(num[i]<128)
		{
			return i*8+1;
			break;
		}
		else if(num[i]-128<64)
		{
			return i*8+2;
			break;
		}
		else if(num[i]-(128+64)<32)
		{	
			return i*8+3;
			break;
		}
		else if(num[i]-(128+64+32)<16)
		{	
			return i*8+4;
			break;
		}
		else if(num[i]-(128+64+32+16)<8)
		{	
			return i*8+5;
			break;
		}
		else if(num[i]-(128+64+32+16+8)<4)
		{
			return i*8+6;
			break;
		}
		else if(num[i]-(128+64+32+16+8+4)<2)
		{
			return i*8+7;
			break;
		}
		else if(num[i]-(128+64+32+16+8+4+2)<1)
		{
			return i*8+8;
			break;
		}
	}
}

int find_zero(unsigned char a)					//빈 비트열 찾기
{
	int i;
	int count=0;
	char c;
	int n = sizeof(int)*2;
	int mask = 1<<(n-1);
	for(i=1;i<=n;++i)
	{
		if(a&mask)
			count++;
		a <<=1;
	}
	return 8-count;
}
void print_bit(unsigned char a)						//비트열출력
{
	int i;
	int n = sizeof(int)*2;
	int mask = 1 << (n-1);
	for(i=1;i<=n;++i)
	{
		putchar(((a&mask)==0)?'0':'1');
		a <<=1;
		if(i%4==0)
			printf(" ");
	}
}

void get_time(char z)     //파일, 디렉터리의 inode 시간 정보 생성
{
	struct tm *t;
	time_t ct;
	ct = time(NULL);
	t = localtime(&ct);			
	i_node[z].when[0]=t->tm_year+1900;			//시간저장
	i_node[z].when[1]=t->tm_mon+1;
	i_node[z].when[2]=t->tm_mday;
	i_node[z].when[3]=t->tm_hour;
	i_node[z].when[4]=t->tm_min;
	i_node[z].when[5]=t->tm_sec;
}
void get_finode(char z)		//파일 inode정보생성
{
	i_node[z].file=0;
	get_time(z);
}

void get_dinode(char z)		//디렉터리 inode정보 생성
{
	i_node[z].file=1;
	get_time(z);
}
/*
	inode삭제

i_node free_inode(char z)
{
	i_node[z].file = "NULL";
}
	data삭제

*/

int main()
{
	FILE *ifp;	//myfs파일 포인터
	char com[5][10];
	
	char dir[10]={"/  "};
	int i, comcount, fr, ee;
	char c;
	while(1)
	{
		printf("$ ");
		scanf("%s", com[0]);
		if(strcmp("mymkfs", com[0])==0)
		{
			if((ifp=fopen("myfs", "r"))!=NULL)		//myfs 파일 유무 검사
				printf("errpr : myfs exists.\n"); //파일 있을때 오류처리
			else
				system("touch myfs");	//파일 만들기
		}
		if(strcmp("myfs_shell", com[0])==0)
		{
			if((ifp=fopen("myfs", "r"))==NULL)		//myfs 파일 유무 검사
				printf("error : myfs not exists.\n");
		}
		if((ifp=fopen("myfs", "r"))!=NULL)		//myfs 파일 유무 검사
		{
		/*ifp=fopen("myfs", "rb");			//이진파일(저장내용) 불러오기
		
		 {
		   	* 파일 불러오는 과정 *
		 }

		 */

			if(strcmp("myfs_shell", com[0])==0)
			{
				while(1)
				{
					printf("[%s]$ ", dir);	//현재 위치 출력
					comcount=0;
					for(i=0;i<4;i++)
					{
						scanf("%s", com[i]);       //명령어 입력
						c=getchar();
						if(c=='\n')
							break;
						comcount++;
					}
					if(strcmp("myls", com[0])==0)
					{
						//이진트리
					}

					if(strcmp("mycat", com[0])==0)
					{
						if(strcmp(">", com[3])==0)					//파일연결
						{
								//com[1], com[2]파일 데이터블럭 불러옴
								//com[4]파일 데이터블럭에 삽입
						}
						else
						{
							//파일 데이터블럭 불러와서 printf
						}
					}

					if(strcmp("myshowfile", com[0])==0)
					{
						//com[3]파일 데이터블럭을 com[1]-1부터 com[2]-1까지 출력
					}

					if(strcmp("mypwd", com[0])==0)
						;

					if(strcmp("mycd", com[0])==0)
					{
					/*if(strcmp(com[1],"NULL")==0)
							strcpy(dir, "/  ");
						else
					*/		strcpy(dir, com[1]); 
					}

					if(strcmp("mycp", com[0])==0)
					{
						//com[1]파일 데이터 블럭 내용을 com[2]파일의 데이터 블럭에 복사
					}

					if(strcmp("mycpto", com[0])==0)
					{
						FILE *afp;
						char c[30];
						sprintf(c, "touch %s", com[2]);			//프롬프트에 파일생성 명령어 만들기
						system(c);								//파일 생성
						//내용 쓰기?
					}
	
					if(strcmp("mycpfrom", com[0])==0)
					{	
						FILE *bfp;
						//com[2] mytouch로 생성 후 com[1]파일 파일포인터로 열어서 정보 읽은 후 데이터블럭에 정보넣기
					}

					if(strcmp("mymkdir", com[0])==0)
					{
						int q;
						q=find_dbit(supers.bit_inode);			//inode 빈 번호 찾기
				  		if(q%8!=0)
							supers.bit_inode[q/8]+=check_bit(q%8);
					 	else
						   	supers.bit_inode[q/8-1]+=check_bit(8);
						get_dinode(q-1);
									//이진트리연결 등....
					}

					if(strcmp("myrmdir", com[0])==0)
					{
							//inode번호 받아서 지우고(함수사용) 이진트리수정 등등...
					}

					if(strcmp("myrm", com[0])==0)
					{
							//rmdir 동일
					}

					if(strcmp("mymv", com[0])==0)
					{
						//com[1]이 파일, com[2]가 디렉터리 = 디렉터리 안으로 파일 이동
						//둘다 파일=  com[2]로 이름변경
					}

					if(strcmp("mytouch", com[0])==0)
					{
						int q;
						q=find_ibit(supers.bit_inode);			//inode 빈 번호 찾기
				  		if(q%8!=0)
							supers.bit_inode[q/8]+=check_bit(q%8);
					 	else
						   	supers.bit_inode[q/8-1]+=check_bit(8);
						get_finode(q-1);					//파일의 inode 생성
						//이미 있는 파일인 경우 시간변경
					}

					if(strcmp("myshowinode", com[0])==0)
					{
						int l;
					//	l=com[1]-1;
						if(i_node[l].file==0)
							printf("file type : regular file\n");
						else if(i_node[l].file==1)
							printf("file type : directory\n");

							printf("file size : %d byte\n", i_node[l].size);
				printf("modified time : %d/%d/%d %d:%d:%d\n", i_node[l].when[0], i_node[l].when[1], i_node[l].when[2], i_node[l].when[3], i_node[l].when[4], i_node[l].when[5]);
							printf("data block list ; \n");
							//데이터 블록 채울것
					}

					if(strcmp("myshowdatablock", com[0])==0)
					{
						int l;
						//  l=com[1]-1;            >> char형 3자리 숫자 int 형으로 바꾸는 법!
						printf("%s", data_block[l]);
					}

					if(strcmp("mystate", com[0])==0)
					{
						int num_inode=0, num_data=0;
						int j;
						for(j=0;j<64;j+=2)
						{
							num_inode += find_zero(supers.bit_inode[j]);
							num_inode += find_zero(supers.bit_inode[j+1]);
						}
						for(j=0;j<128;j+=2)
						{
							num_data += find_zero(supers.bit_data[j]);
							num_data += find_zero(supers.bit_data[j+1]);
						}
						printf("free inode : %d\n", num_inode);		//inode 남은갯수
						printf("free data block : %d\n", num_data);	//data block 남은갯수
					}
					if(strcmp("mytree", com[0])==0)
					{
						//트리출력
					}

					/* command */
					if(strcmp("byebye", com[0])==0)
						break;
					else
					{
						char command[50];
						if(comcount==0)
							sprintf(command, "%s", com[0]);
						else if(comcount==1)
							sprintf(command, "%s %s", com[0], com[1]);
						else if(comcount==2)
							sprintf(command, "%s %s %s", com[0], com[1], com[2]);
						else if(comcount==3)
							sprintf(command, "%s %s %s %s", com[0], com[1], com[2], com[3]);
						system(command);

					}
					for(fr=0;fr<5;fr++)
					{
						for(ee=0;ee<10;ee++)
							com[fr][ee]=0;
					}
				}			
			}		
		}
	}
}
