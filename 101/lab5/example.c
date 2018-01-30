/*  program 18.4, page 396  */

#include <stdio.h>

int main (void) {
	
	const int data[5] = {1, 2, 3, 4, 5};
	int i, sum;

	for (i = 0; i <= 5; i++) {
		sum += data[i];
	}

	printf ("sum = %d\n", sum);

	return 0;
}
