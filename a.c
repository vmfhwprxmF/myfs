#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
typedef struct
{
	int direct_num;		//직접
	int single_num;		//1차간접
	int double_num;		//2차간접
}data_num;
typedef struct 
{
	int c_i_bit[9];		// i-node 사용여부 (512)
	int c_d_bit[10];	// data block 사용여부 (1024)
}supers;
typedef struct 
{
	struct i_node *before_inode;	// 자기참조
	_Bool file; 					// 0-file, 1-dir
	time_t now;					// 생성시간
	int size;     					// 파일크기
	data_num a;
	struct i_node *next_inode;		// 자기참조
}i_node;
typedef struct
{
	struct datas *before_data; 	// 자기참조
	char data;
	struct datas *next_data; 	// 자기참조
}datas;
typedef struct
{
	char l_link;	// 왼쪽 파일 링크
	char data;		// 본 파일 정보(?)
	char r_link;		// 오른쪽 파일 링크
}binary_tree;
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
