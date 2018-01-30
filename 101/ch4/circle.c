// circle.c finds the area of a circle
/* algorithm:
   1. formula is pi*r*r 
   2. radius is given (int)
   3. pi is a float 
   4. float variable for area
   5. declare and initialize  variables
   6. plug in values into the formula to get the area
   7. print the area */

#include <stdio.h>

int main (void) 

{
 int radius;
 float pi= 3.14;
 float area;
 printf ("\n\nEnter an integer value for radius: ");
 scanf("%i", & radius);
 area = pi * radius * radius;
 printf("\n\n The area is %.2f \n\n", area);
 return 0;

}
