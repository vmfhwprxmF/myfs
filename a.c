#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct 
{
	int c_i_bit[9];		// i-node 사용여부 (512)
	int c_d_bit[10];	// data block 사용여부 (1024)
}supers;
typedef struct 
{
	_Bool file; 				// 0-file, 1-dir
	int number;  				// i-node number
	char name[4];	 			// 파일이름
	int size;     				// 파일크기
	struct i_node *next_inode;	// 자기참조
}i_node;
typedef struct
{
	int direct;
	int single_indirect; 		// 1차간접
	int double_indirect; 		// 2차간접
	struct datas *next_data; 	// 자기참조
}datas;
typedef struct
{
	char l_link;	// 왼쪽 파일 링크
	char data;		// 본 파일 정보(?)
	char r_link		// 오른쪽 파일 링크
}binary_tree;

int main(int argc,char *argv[])
{
	FILE *ifp;	//myfs파일 포인터

	if(strcmp("mymkfs", argv[0])==0)
	{
		if((ifp=fopen("myfs", "r"))==NULL)		//myfs 파일 유무 검사
		{ 
			printf("errpr : myfs exists."); //파일 있을때 오류처리
		}
		else
		{
			system("touch myfs");	//파일 만들기
		}
	}	
	else
	{
		while(1)
		{
			printf("[/ ]$");	//현재 위치 출력
			scanf(&);			//
		return 0;
		}	
	}
}
