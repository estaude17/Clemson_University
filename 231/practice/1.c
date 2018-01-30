#include <stdio.h>
int main(void){
 int x = 7;
 int y = x >> 1;//shifting x by 1(0111 = 7 = x, 0011 = 3 = y)
 printf("x = %d y = %d\n", x, y);
 return 0;
}
