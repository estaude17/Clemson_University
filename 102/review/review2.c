#include <stdio.h>

int main (void){
	int count1 = 10;
	int *ptr1 = &count1;

	int count2 = 20;
	int *ptr2 = &count2;

	printf("ptr1 is %i, ptr2 is %i \n", *ptr1, *ptr2);
	
	ptr1 = ptr2;
	printf("ptr1 is %i, ptr2 is %i \n", *ptr1, *ptr2);
return 0;
}

