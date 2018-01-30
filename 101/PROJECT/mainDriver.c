#include <stdio.h>
#include "carnival.h"

int main (void)
{
int game, redo;
do{
printf("~*WELCOME TO THE CARNIVAL!*~\n");
printf("Which game would you like to play?\n");
printf("1. Pumpkin contest\n2. Guess my weight\n3. Personality test\n");
printf("Enter the integer that corresponds to your choice: ");
scanf("%d", &game);

 if(game == 1)
{
 printf("\n~* PUMPKIN CONTEST! *~\n"); 
 doPumpkin(game);

}

if(game == 2)
{
 printf("\n~* GUESS MY WEIGHT! *~\n");
 doWeight (game);

}

if(game == 3)
{
 printf("\n~* PERSONALITY READING! *~\n");
 doPersonality (game);

}

 printf("\nWant to play a different game? 1 for yes, 0 for no\n");
 scanf("%i", &redo);
}while (redo == 1);

return 0;
}
