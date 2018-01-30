#include <stdio.h>
#include "lab8.h"

int main (void)
{
int count;
int a[count];
int b[count];
int i;
printf("How many elements are in the arrays?\n");
scanf("%d", &count);

printf("Enter the array elements for the first array\n");

for (i = 0; i < count ; i++)
  scanf("%d", &a[i]);

printf("Enter the array elements for the second array\n");

for (i = 0; i < count ; i++)
  scanf("%d", &b[i]);

inner_product(a, b, count);

reverse(a, count);
return 0;
}

