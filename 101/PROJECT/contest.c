//Elizabeth Stauder (estaude); CPSC 1010-001; 
//20 October 2014; Program Assignment #1: Phase 1
//User inserts six numbers between 1 and 10. The smallest number is dropped.
//The rest of the numbers are averaged together. If the average is higher 
//than 9.0, the user wins a T-shirt. The program can be repeated as many 
//times as the user wants.

#include <stdio.h>
#include "carnival.h"

int doPumpkin (int game)
{
 float num1, num2, num3, num4, num5, num6;
 int shirt = 0;
 int aveNumber = 0;
 int goAgain = 0;
 int pumpkintotal = 0;
 int pumpkinScore;
 static float avePumpkin = 0;
 float average, aveTotal;
do {
 printf ("Enter the six scores(1-10): \n");
 scanf ("%f %f %f %f %f %f", &num1, &num2, &num3, &num4, &num5, &num6);

//This next part finds the smallest of the six scores and sets it equal to 0.

if (num1 < num2 && num1 < num3 && num1 < num4 && num1 < num5 && num1 < num6)
   {num1 = 0;}

if (num2 < num1 && num2 < num3 && num2 < num4 && num2 < num5 && num2 < num6)
   {num2 = 0;}

if (num3 < num1 && num3 < num2 && num3 < num4 && num3 < num5 && num3 < num6)
   {num3 = 0;}

if (num4 < num1 && num4 < num2 && num4 < num3 && num4 < num5 && num4 < num6)
   {num4 = 0;}

if (num5 < num1 && num5 < num2 && num5 < num3 && num5 < num4 && num5 < num6)
   {num5 = 0;}

if (num6 < num1 && num6 < num2 && num6 < num3 && num6 < num4 && num6 < num5)
   {num6 = 0;}

pumpkinScore = (num1 + num2 + num3 + num4 + num5 + num6);

average = (float)pumpkinScore / 5;
avePumpkin += average; //This will create a sum of all the averages.

if (average >= 9.0)
   { ++aveNumber; //The aveNumber is the number of average scores.
     shirt++;
     pumpkintotal++;
     printf ("\nThe average score is: %.2f\n", average);
     printf ("You win a T-Shirt!\n"); }
if(average < 9.0) 
   { pumpkintotal++;
     ++aveNumber;
     printf ("\nThe average score is: %.2f\n", average); }
printf("\n\nDo you want to submit another score? 1 for yes, 0 for no\n");
scanf ("%d", &goAgain);
} while (goAgain == 1);
//This do-while loop repeats the scoring cycle as many times as the user wants.

aveTotal = (float)avePumpkin / aveNumber;
//aveTotal equals the sum of all the averages divided by the number
//of submissions given.
printf("SUMMARY:\n");
printf ("Pumpkins in the contest: %i\n", pumpkintotal);
printf ("# of T-shirts won: %i\n", shirt);
printf("The average of the scores is %.2f\n", aveTotal);
return 0;
}
