#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

char bootblock[2];  //  부트블럭은 16비트 고정
/*typedef struct
{
	int direct;		//직접
	struct data *indirect;  //간접 자기참조구조체
}data;
*/
typedef struct 
{
	int c_i_bi[16];		// i-node 사용여부 (512)
	int c_d_bit[32];	// data block 사용여부 (1024)
}supers;
typedef struct 
{
	_Bool file; 					// 0-file, 1-dir
	time_t now;						// 생성시간
	int size;     					// 파일크기
	//data num;						// 데이터 블럭 번호
/*
	int *direct;
	int *s_indirect;
	int *d-indirect;
 */
}i_node[512];
typedef struct
{
	char data[128];				// 128바이트
}data_block[1024];
typedef struct
{
	char *l_link;	// 왼쪽 파일 링크
	char name[4];		// 본 파일 이름
	char *r_link;		// 오른쪽 파일 링크
}binary_tree;


/*

   슈퍼블럭 inode 비트열 찾기
   슈퍼블럭 data 비트열 찾기


i_node get_f_inode(char z)     //파일의 inode생성
{
	i_node[z].file = 0;
	i_node[z].now = time(NULL);
	i_node[z].size = ;
	i_node[z].a,direct_num = ;
}
i_node get_d_inode(char z)     //디렉터리의 inode생성
{
	i_node[z].file = 1;
	i_node[z].now = time(NULL);
	i_node[z].size = ;
	i_node[z].a,direct_num = ;
}

	inode삭제
	비트열 수정
	data삭제
	비트열 수정
*/

int main()
{
	FILE *ifp;	//myfs파일 포인터
	char com[4][10];
	char dir[10]={"/  "};
	int i;
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
			break;
	}
	if((ifp=fopen("myfs", "r"))!=NULL)		//myfs 파일 유무 검사
	{
		if(strcmp("myfs_shell", com[0])==0)
		{
			while(1)
			{
				printf("[ %s]$ ", dir);	//현재 위치 출력
				for(i=0;i<4;i++)
				{
					scanf("%s", com[i]);       //명령어 입력
					c=getchar();
					if(c=='\n')
						break;
				}
				if(strcmp("ls", com[0])==0)
				{
					if(strcmp("-l", com[1])==0)
						system("ls -l");
					else if(strcmp("-i", com[1])==0)
						system("ls -i");
					else if(strcmp("-ii", com[1])==0)
						system("ls -il");
					else
						system("ls");
				}
				if(strcmp("mycd", com[0])==0)
					strcpy(dir, com[1]); 
				if(strcmp("mypwd", com[0])==0)
					printf("%s\n", dir);
				if(strcmp("byebye", com[0])==0)
					break;
			}			
		}	
	}
}
