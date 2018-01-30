#include <stdio.h>

int main(void){
  int i;
  int a[10000], b[10000], c[10000];
  for(i = 1; i<10000;i++)
        a[i] = b[i];
  for(i=1; i<10000;i++)
        c[i] = c[i-1]+1;
        

}

