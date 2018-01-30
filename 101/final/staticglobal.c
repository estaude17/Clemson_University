#include <stdio.h>
void practice (void)
{
	static int aNumber = 2;
	int anotherNumber = 5;
	
	aNumber++;
	anotherNumber += 5;
	printf("%i, %i\n", aNumber, anotherNumber);
}
int main (void)
{
	int index;
	void practice (void);

	for(index = 0; index < 3; ++index)
		practice();
return 0;
}
