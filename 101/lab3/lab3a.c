#include <stdio.h>

int main(void)
{
 int x;
 int n = 1;
 int xn = 1;
 printf ("State input value\n");
 scanf ("%d", &x);
 printf ("Powers of %d\n", x);
  while(n <= 10)
  {
    xn = x * xn;
    printf ("%3d %12d %8x\n", n, xn, xn);
    n = n+1;
  }
 return 0;
}
//warning: program will not work for x values greater than 8//
