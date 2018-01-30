#include <stdio.h>

int increment(int x);
int number = 3;

int main (void)
{
int i, x = 2;
for (i = 0; i < 5; i++){
	increment(x);
}
printf("number from main is %i\n", number);
printf("x from main is %i\n", x);

number = increment(x);

printf("number after call to increment is %i\n", number);
printf("x after call is %i\n", x);
return 0;
}


int increment (int x)
{
static int number = 0;
number++;
x += 5;

printf("number in increment is %i\n", number);
printf("x in increment is %i\n", x);
return number;
}
