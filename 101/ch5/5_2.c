#include <stdio.h>

int main (void)
{
 int count, n, number;
 int triangularNumber = 0;

 for (count = 1; count <= 5; ++count){    
 printf("What triangular number do you want?\n");
 scanf("%i", &number);

 for (n = 1; n <= number; n = n++)
  triangularNumber += n;

 printf ("The triangular number %i is %i\n", number, triangularNumber);
}
 return 0;
}
