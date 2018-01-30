#include <stdio.h>

int main (void){
	int values[10] = {-1, 14, -24, 6, 9, 2, -3, 4, 7, 3};
	char word[32] = "The semester is just beginning!";
	int i;

	printf("\n\n");
	int *ptr1 = values;
	printf("ptr1 = %i\n", *ptr1);
	
	int *ptr2 = ptr1 + 3;
	printf("ptr2 = %i\n", *ptr1);

	char *ptr3;
	ptr3 = word;
	printf("*ptr3 = %c\n", *ptr3);
	printf("*(ptr3 + 4) = %c\n", *(ptr3 + 4));

	printf("Letters: ");
	char *ptr4 = word;
	for (i = 0; i < 8; i++){
		printf("%c", *ptr4);
		ptr4 += 4;
		}
	printf("\n%s\n", word);
	printf("\n\n");
return 0;
}
