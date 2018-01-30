#include <stdio.h>

int main(void) {
 int i;
 printf("P6\n");
 printf("400 400 255\n");

 //r = 255, g = 255, b = 0
 for(i = 0; i < 400 * 400; i++) {
   printf("%c%c%c", 255, 255, 0);
 }
 return 0;
}
