//Elizabeth Stauder (estaude); CPSC 1010-001; 
//20 October 2014; Program Assignment #1: Phase 2
//User inputs their weight as an integer betwenn 50 and 200.
//The program creates a random number. If the number is within a 10-unit
//range of the user's weight, they win a teddy bear.

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "carnival.h"

int doWeight (game)
{
int weight;
int number;
int repeat;
int teddybear = 0;

srand (time (NULL)); //generates a new random number each time program is run.

    printf ("Enter your weight as an integer between 50-200:\n");
    scanf ("%i", &weight);
 do{  
    number = 50 + rand () % (151);
       //The above part makes a random number and sets it equal to "number".
    printf ("I guessed %d\n", number);

    if (number >= (weight - 10) && (weight + 10) >= number ){
      printf ("I guessed within 10 pounds of your weight! Sorry, no prize.\n");
      printf ("Summary:\n");
      printf ("You won %i teddy bear(s)\n", teddybear);
      return (0);
    }//The game ends if "number" is within ten pounds of the entered weight.
   else {
      printf ("I wasn't even close to your weight! You win a teddy bear!");
      teddybear++;
      printf ("\nWant to play again? 1 for yes, 0 for no\n");
      scanf ("%i", &repeat);
    }
   }while (repeat == 1);

printf ("Summary:\n");
printf ("You won %i teddy bear(s)\n", teddybear);

return (0);
}
