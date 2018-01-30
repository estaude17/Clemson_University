#include <stdio.h>

void modify(int p, int *q, int *r){
	printf("\n\n1. p is %i, q is %i, r is %i\n", p, *q, *r);
	p = 27;
	*q = 27;
	*r = 27;
}

int main (void){
	int a = 1;
	int b = 1;
	int c = 1;
	int *x = &c;
	
	modify(a, &b, x);
	printf("2. a is %i, b is %i, c is %i, x is %i\n\n", a, b, c, *x);
return 0;
}
