#include <stdio.h>

int main (void){
	int y;
	int *ptr;
	static int a;
	
	ptr = &y;
	*ptr = 99;
	
	printf("y is %i\n ptr is %i\n address of ptr is %p\n", y, *ptr, &ptr);

	ptr = &a;
	printf("the address of a is %p\n", ptr);
return 0;
}
