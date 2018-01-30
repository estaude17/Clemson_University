#include <stdio.h>

void exchange (int *intPtr1, int *intPtr2)
{
	int temp;
	
	temp = *intPtr1;
	*intPtr1 = *intPtr2;
	*intPtr2 = temp;
}

int main (void)
{
	int i1 = 34, i2 = -7, *p1 = &i1, *p2 = &i2;
	printf("i1 = %i, i2 = %i\n", i1, i2);

	exchange (&i1, &i2);
	printf("i1 = %i, i2 = %i\n", i1, i2);

	exchange (p1, p2);
	printf("i1 = %i, i2 = %i\n", i1, i2);
return 0;
}
