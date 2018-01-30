#include <stdio.h>

void f(int n)
{
//	printf("%d\n", n);
	if (n > 1)
	{
		f(n - 1);
	}
	printf("%d\n", n);
}
int main (void)
{
int n = 5;
f(n);
return 0;
}
