#include <stdio.h>

int modify (int a){
	printf("The address of modify's a is %p \n", &a);
	a = 15;
	printf("The value of modify's a is %i \n", a);
}

int main(void){
	int a = 20;
	int *ptr = &a;

	printf("The address of main's a is %p \n", &a);
	printf("The address of the value of main's ptr is %p \n", ptr);
	modify(a);
	printf("The value of main's a is %i \n", a);
return 0;
}
