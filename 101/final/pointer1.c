#include <stdio.h>

int main (void){

int values[10] = {-1, 14, -24, 6, 9, 2, -3, 4, 7, 3};
char word[26] = {"More pointers!"};
int i, n = 10;

int *pv0 = values + 3;
printf("pv0 = %i\n", *(pv0 - 2));

printf("check: ");
char *pv4 = word;
for (i = 0; i < 5; i++){
	printf("%c", *pv4);
	pv4 += 3;
}
return 0;
}
