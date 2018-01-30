#include <stdio.h>

int main (void){
 int a, b, c, d;
 
 a = 6;
 b = ++a * 3;
 c = b++;
 d = c++;
 printf("%i %i %i %i\n", a, b, c, d);
return 0;
}
