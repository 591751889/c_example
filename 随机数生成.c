#include<stdio.h>

int main()

{
	srand((unsigned int)time(0));
	int n=5,i;
	for ( i = 0; i < n; i++)

	{
		int random = rand();
		int m = random % (100 - 1+1) + 1;//ÉèÖÃ·¶Î§  1-100
		Sleep(500);
	
		printf("%d %d\n",random,m);
	}
 } 
