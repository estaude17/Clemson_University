#include <stdio.h>


int main (int argc, char *argv[])
{
double value1 = 0;
double value2;
char opchar;
int i;

sscanf(argv[1], "%lf", &value1);

for (i = 2; i < argc; i += 2)
{
  sscanf(argv[i], "%c", &opchar);
  sscanf(argv[i + 1], "%lf", &value2);

  switch (opchar)
  {
   case '+':
  	value1 = value1 + value2;
  	break;

   case '-':
  	value1 = value1 - value2;
  	break;
 
   case 'x':
  	value1 = value1 * value2;
  	break;

   case '/':
  	value1 = value1 / value2;
  	break;
  
   default:
  	fprintf(stderr, "bad op code %c\n", opchar);
  }
 }
fprintf(stdout, "%12.3lf\n", value1);

return 0;
}
