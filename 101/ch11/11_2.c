#include <stdio.h>

int main (void)
{
  char c = 'Q';
  char *char_pointer = &c;
  char a = *char_pointer; 
  printf("%c %c\n", c, *char_pointer);
  
  c = '/'; 
  printf("%c %c\n", c, *char_pointer);
  
  *char_pointer = '(';
   printf("%c %c %c\n", c, a, *char_pointer);

   return 0;
}
