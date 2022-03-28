#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	for(int i = 0; i < argc; i++)
	{
		printf("argc[%d] = %s\n", i, argv[i]);
	}
	
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	
	printf("%d + %d = %d\n", x, y, x + y);
	printf("%d - %d = %d\n", x, y, x - y);
	printf("%d * %d = %d\n", x, y, x * y);
	printf("%d / %d = %d\n", x, y, x / y);
 
	return 1;
 
}
