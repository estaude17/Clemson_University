//This program finds the area of a triangle, once the height and base have been given.//
#include <stdio.h>
#include <math.h>

int main (void)
{
 double base, height, area;
 area = (base * height) / 2;
 printf ("\n\nEnter two integer values for height and base: ");
 scanf("%lf%lf", &height, &base);
 printf("The area is %.2lf \n", area);
 return 0;
}
