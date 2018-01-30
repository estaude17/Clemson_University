#include <stdio.h>

int main (void)
{
char words[] = "Programming is my favorite class!";
int i = 17;

words[i + 2] = '\0';
words[i + 1] = '!';
words[i] = 'n';
words[i - 1] = 'u';
words[i - 2] = 'f';

//printf("%c", words[18]);
//printf("%s", words);

if ('n' == words[17])
   printf("They are the same\n");

return 0;
}
