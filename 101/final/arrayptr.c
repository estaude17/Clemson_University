#include <stdio.h>
int main (int argc, char *argv[])
{
int i;
int j = 5;
//int k = i + j;

printf("There are %d arguments\n", argc);
printf("The executable is %s\n", argv[0]);

printf("Hi, %s\n", argv[1]);

sscanf(argv[2], "%d", &i);
//sscanf(argv[3], "%d", &j);
printf("%d + %d = %d\n", i, j, i + j);
 
return 0;
}
