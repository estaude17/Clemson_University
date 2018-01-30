#include <stdio.h>
#include "lab8.h"

int inner_product(int a[], int b[], int count)
{
int product = 0; 
int i;

for (i=0; i<count; i++)
{
    product+=a[i]*b[i];
}
   
return product;
}


void reverse(int a[], int count)
{
   int i;
   int temp;

   for (i=0; i<(count/2); i++)
{
      temp = a[i];
      a[i]=a[count - (i+1)];
      a[count - (i+1)]=temp;
}
}

