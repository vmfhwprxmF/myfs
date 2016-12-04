#include<stdio.h>
char check(int num);
int find(unsigned char []);
void bit_printf(char []);
int main()
{
	int j, g, q, a, m;
	unsigned char num[64]={0};
	while(1)
	{
		printf("1 : 생성, 2: 삭제, 3: 가장 가까운 빈칸, 4: 비트열 출력, 5: 끝내기\n");
		scanf("%d", &a);
	   if(a==1)
	   {
	   	   printf("사용하고싶은 번호(1~512) : ");
	   	   scanf("%d", &q);
	   	   if(q%8!=0)
				num[q/8]+=check(q%8);
	   	   else
		   	   num[q/8-1]+=check(8);
	   }
	   else if(a==2)
	   {
	   	   printf("삭제하고싶은 번호(1~512) : ");
	   	   scanf("%d", &q);
	   	   if(q%8!=0)
				num[q/8]-=check(q%8);
	   	   else
		   	   num[q/8-1]-=check(8);
	   }
	   else if(a==3)
	   {
		   printf("%d", num[0]);
		m=find(num);
		printf("%d 번 비었움.\n", m);
	   }
	   else if(a==4)
	   {
			for(j=0;j<64;j=j+2)
			{
				bit_print(num[j]);
				bit_print(num[j+1]);
				g++;
				if(g%2==0)
					printf("\n");
			}
	   	}
   		else if(a==5)
	 		break;		
	}
	return 0;
}
char check(int num)
{
	int i;
	unsigned int n=128;
	int mask = 1 << (8-num);
	return mask;
}
int find(unsigned char num[])
{
	int i;
	for(i=0;i<64;i++)
	{
		printf("%d\n", num[i]);
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
void bit_print(char a)
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
