#include <stdio.h>

int main()
{
 int v1 = 3;
 int v2 = 8;
 float e1, e2, e3, e4;
 e1 = v1 + 2 * v2 / 3 * v1;
 e2 = v1 + ((2 * v2) / (3 * v1);
 e3 = v1 + (2 * (v2 / 3)) * v1;
 e4 = (v2 % v1) % (v2 / v1);
 printf("e1 is %f, e2 if %f, e3 %f, and e4 is %f", e1, e2, e3, e4);
}
