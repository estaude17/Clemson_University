#include <stdio.h>
int main (void)
{
int x;
printf("Enter a number.\n");
scanf ("%i", &x);
   if (x % 2 ){
     printf ("odd!\n");
   }
   else {
     printf ("even!\n");
   }
return 0;
}
