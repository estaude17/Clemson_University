#include <stdio.h>

int main()
{
 int v1=3;
 int v2=8;
 fscanf(stdin,"%d %d", &v1, &v2);
 int e1 = v1 + 2 * v2 / 3 * v1;
 int e2 = v1 + ((2 * v2) / (3 * v1));
 int e3 = v1+(2*(v2/3))*v1;
 int e4 = (v2 % v1)%(v2/v1);
 fprintf(stdout, "%d %d %d %d\n", e1, e2, e3, e4);
 return(0);
}

