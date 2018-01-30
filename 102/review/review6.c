#include <stdio.h>

int tryToModify(int a){
	static int b = 5;
	
	a = a + 5;
	b = b + 5;
	printf("a is %i, b is %i\n", a, b);
}

int main (void){
	int x = 20;
	printf("\n\n");
	tryToModify(x);
	tryToModify(x);
	tryToModify(x);
	printf("\n\n");
return 0;
}
