//Elizabeth Stauder (estaude); CPSC 1010-001; 
//20 October 2014; Program Assignment #1: Phase 3
//User inserts numbers corresponding with their birthmonth
//and their favorite color. A personality summary is printed
//based on their input.

#include <stdio.h>
#include "carnival.h"

void enter_month(month)
{
switch (month){ //This coordinates the month you chose with a statement.
  case(1):
       printf ("Born in January, you are bold and alert.\n");
       break;
  case(2):
       printf ("Born in February, you are lucky and loyal.\n");
       break;
  case(3):
       printf ("Born in March, you are naughty and genius.\n");
       break;
  case(4):
       printf ("Born in April, you are caring and strong.\n");
       break;
  case(5):
       printf ("Born in May, you are loving and practical.\n");
       break;
  case(6):
       printf ("Born in June, you are romantic and curious.\n");
       break;
  case(7):
       printf ("Born in July, you are adventurous and honest.\n");
       break;
  case(8):
       printf ("Born in August, you are active and hardworking.\n");
  case(9):
       printf ("Born in September, you are sensitive and pretty.\n");
       break;
  case(10):
       printf ("Born in Ocotber, you are stylish and friendly.\n");
       break;
  case(11):
       printf ("Born in November, you are nice and creative.\n");
       break;
  case(12):
       printf ("Born in December, you are confident and freedom-loving.\n");
       break;
  }
}

void enter_color(color)
{
switch (color){//This coordinates the color you chose with a statement.
  case (1):
       printf ("Red means you are action oriented with a deep need for\n");
       printf ("physical fulfillment and to experience life through\n");
       printf ("the five senses.\n");
       break;
  case (2):
       printf ("Orange means you have a great need to be with people, to\n"); 
       printf ("socialize with them, and be accepted and respected as part\n");
       printf ("of a group. You also have a need for challenges in your\n"); 
       printf ("life, whether it is physical or social challenges.\n");
       break;
  case (3):
       printf ("Yellow means you have a deep need for logical order in\n");
       printf ("your everyday life and to be able to express your\n");
       printf ("individuality by using your logical mind to inspire and\n");
       printf ("create new ideas.\n");
       break;
  case (4):
       printf ("Green means you have a deep need to belong, to love and\n");
       printf ("be loved, and to feel safe and secure. You need acceptance\n"); 
       printf ("and acknowledgment for the everyday things you do for\n");
       printf ("others -- just a 'thank you' is sufficient.\n");
       break;
  case (5):
       printf ("Blue means you have a deep need to find inner peace and\n");
       printf ("truth, to live their life according to their ideals and\n");
       printf ("beliefs without having to change their inflexible\n");
       printf ("viewpoint of life to satisfy others.\n");
       break;
  case (6):
       printf ("Purple means you have a deep need for emotional security\n");
       printf ("and to create order and perfection in all areas of your\n");
       printf ("life, including your spiritual life. You also have a deep\n");
       printf ("need to initiate and participate in humanitarian projects,\n");
       printf ("helping others in need.\n");
       break;
  case (7):
       printf ("Pink means you have a deep need to be accepted and loved\n");
       printf ("unconditionally.\n");
       break;
  }
}

int doPersonality (int game)
{

int month, color; 

printf("Enter the corresponding integer for your birth month(1-12)\n");
scanf ("%i", &month);

if (month > 12 || month < 1){
   printf("Invalid number! Try again!\n");
   scanf ("%i", &month);
}

printf("What is your favorite color? Enter the corresponding integer.\n");
printf("1 = red\n2 = orange\n3 = yellow\n4 = green\n5 = blue\n");
printf("6 = purple\n7 = pink\n");
scanf("%i", &color);

if (color > 7 || color < 1){
    printf("Invalid number! Try again!\n");
    scanf ("%i", &color);
}

enter_month(month);
    //calls function "enter_month" with the integer you entered for month.
enter_color(color);
    //calls function "enter_color" with the integer you entered for color.

return 0;
}
