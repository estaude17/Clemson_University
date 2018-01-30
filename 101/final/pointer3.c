#include <stdio.h>
int main (void)
{
int x[] = {1, 2, 3, 4};
int *p = &x[2];
int *q = &x[1];
int *r = ++q;

printf("%i\n", *(p + 1));
printf("%i\n", *(p - 1));
printf("%i\n", *q);
printf("%i\n", *r);

//printf("%i\n", p);

return 0;
}
