#include <stdio.h>

int F_chk_8( int bval, int cval ) {

    return ( bval + cval ) % 256;
}

int main(){
  int a, b;
  printf("Enter two numbers\n");
  scanf("%i %i", &a, &b);
  int c = F_chk_8(a, b);
  printf("%i", c);
  return 0;
}
