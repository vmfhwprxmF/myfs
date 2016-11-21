#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct supers
{
	int c_i_bit[9];		// i-node 사용여부
	int c_d_bit[10];	// data block 사용여부
}
struct i_node
{
	_Bool file; 		// 0-file, 1-dir
	int number;  		// i-node number
	char name[4]; 		// 파일이름
	int size;     		// 파일크기
	struct i_node *num_inode;	// 자기참조
}
struct datas
{
	int direct;
	int single_indirect; // 1차간접
	int double_indirect; // 2차간접
	struct datas *num_data;
}
int main(int argc,char *argv[])
{

	while(1)
	{
		printf("[/ ]$");
		scanf(&);
	return 0;
}
