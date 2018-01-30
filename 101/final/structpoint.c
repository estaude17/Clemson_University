#include <stdio.h>
int main (void)
{
	struct date {
		int month, day, year;
		};
	struct date today, *datePtr;
	datePtr = &today;
	
 	datePtr->month = 8;
	datePtr->day = 6;
	datePtr->year = 2004;

	printf("%i / %i / %i\n", datePtr->month, datePtr->day, datePtr->year); 

	today.month = 11;
	today.day = 17;
	today.year = 1995;
	
	printf("%i/%i/%i\n", today.month, today.day, today.year);	
return 0;
}
