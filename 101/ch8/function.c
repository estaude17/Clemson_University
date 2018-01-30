#include <stdio.h>
int square(int x);
int main (void)
{
int value;
int Square = square(value);
printf ("Input number.\n");
scanf ("%i", &value);
printf ("x squared is %i.\n", square(value));
printf ("x cubed is %i.", cube(value));
return 0;
}
int square(int x)
{
 return x * x;
}
int cube (int x)
{
 return x * x * x;
}
