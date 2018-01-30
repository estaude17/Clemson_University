#include <stdio.h>

int main (void){

struct dateOfBirth {
	int month, day, year;};

struct student{
	int age;
	int cuid;
	float gpr;
	struct dateOfBirth dob;
	char lastName[11];
};

/*struct student David;

David.age = 19;
David.cuid = 12345;
David.gpr = 3.6;

David.dob.month = 9;
David.dob.day = 17;
David.dob.year = 1992;

David.lastName[0] = 'S';
David.lastName[1] = 'm';
David.lastName[2] = 'i';
David.lastName[3] = 't';
David.lastName[4] = 'h';
David.lastName[5] = '\0';

struct student class[10];

class[0] = David;

class[1].age = 20;
*/
struct student David = {19, 12345, 3.6, 9, 17, 1994, "Smith"};
printf("%s", David.lastName);
return 0;
}
