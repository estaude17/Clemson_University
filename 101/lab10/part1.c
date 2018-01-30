#include <stdio.h>
int main (int argc, char *argv[])
{
 double value1, value2;
 char opchar;
 double answer;

 sscanf(argv[1], "%lf", &value1);
 sscanf(argv[2], "%c", &opchar);
 sscanf(argv[3], "%lf", &value2);

 switch (opchar)
  {
   case '+':
  	answer = value1 + value2;
  	break;

   case '-':
  	answer = value1 - value2;
  	break;
 
   case 'x':
  	answer = value1 * value2;
  	break;

   case '/':
  	answer = value1 / value2;
  	break;
  
   default:
  	fprintf(stderr, "bad op code %c\n", opchar);
  }

 fprintf(stdout, "%12.3lf", answer);
return 0;
}
