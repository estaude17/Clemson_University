#include <stdio.h>

typedef struct aStruct {
	int x;
	int y;
}myStruct;

int main (void){
	myStruct struct1;

	struct1.x = 10;
	struct1.y = 15;

	int *aPtr = &struct1.x;
	
	printf("%i\n", *aPtr);

	myStruct *ptr2 = &struct1;

	printf("%i\n", (*ptr2).x);
return 0;
}
