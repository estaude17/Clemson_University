#include <stdio.h>
int main (void)
{
char input;
printf ("Give me a letter.\n");
scanf ("%c", &input);

switch (input) {
   case 'a':
   case 'A':
   case 'e':
   case 'E':
   case 'i':
   case 'I':
   case 'o':
   case 'O':
   case 'u':
   case 'U':
     printf ("The letter is a vowel!\n\n");
     break;
   default:
     printf ("The letter is NOT a vowel!\n\n");
}
return 0;
}
