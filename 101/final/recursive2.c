#include <stdio.h>

int sum(int n, int i)
{
int result;

for (i = 0; i <= n; i++)
{
	result = i + sum(n, (i + 1));
}
return result;
}


int main (void)
{

int n, i;

printf("What is the parameter?\n");
scanf("%i", &n);

printf("%i\n", sum(n, i));

return 0;
}
