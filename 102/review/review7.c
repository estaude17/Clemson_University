#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	int a = 10;
	int b = 12;
	int *base = NULL;
	
	base = (int *) malloc(sizeof(int) * 100);

	printf("a is %p\n", &a);
	printf("b is %p\n", &b);
	printf("base is %p\n", base);

return 0;
}
