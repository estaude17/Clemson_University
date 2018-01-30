#include<stdio.h>
int main (void)
{
int u, v, temp;

printf("Enter two non-negative integers.\n");
scanf ("%i%i", &u, &v);

do{
  temp = u % v;
  u = v;
  v = temp;
}
 while (v != 0);
printf ("Their greatest common divisor is %i\n", u);
return 0;
}
