#include <stdio.h>

int main (void)
{
int numberofGrades, i, grade;
int gradeTotal = 0;
int failures = 0;
float average;

printf("How many grades are there?");
scanf ("%i", &numberofGrades);

for (i = 1; i <= numberofGrades; i++){
     printf("Enter grade #%i: ", i);
     scanf("%i", &grade);

gradeTotal = gradeTotal + grade;

if(grade < 65)
     ++failures;
}

average = (float)gradeTotal / numberofGrades;

printf("\nGrade average is %.2f\n", average);
printf("Number of failures = %i\n", failures);

return 0;
}
