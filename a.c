#include<stdio.h>
int main()
{
	int i=10, j=20;
	int *p=NULL;
	printf("i=%d, j=%d\n", i, j);
	p = &i;
	printf("p = %d", &p);
	printf("i=%d, j=%d\n", i, j);
	return 0;
}
	
