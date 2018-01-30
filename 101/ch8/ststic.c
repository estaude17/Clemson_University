#include <stdio.h>

int increment ();
int number = 3;

int main (void){
  int i;
  for (i = 0; i < 5; i++){
     increment ();
  }
  printf ("Number from main is %i\n", number);
  number = increment ();
  printf("Number after call to increment is %i\n", number);
}

int increment () {
  static int number; 
  number = 0;
  number++;
  printf("Number in increment is %i\n", number);
  return number;
}
