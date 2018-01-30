// class exerise for loops and conditional statements
// modified version of program 6.9 from book
/* user will enter an expression like 3 + 2
   the program will use an if statement to see which operator the user entered
   then it wil compute the result and display it
   the if statement will be in a loop that will allow the user to go again 
   continually until avalue is entered to indicate they are don */

#include <stdio.h>
int main (void)
{
  int num1, num2, result = 0, goAgain = 0;
  float result2 = 0.0;
  char operator;

do {
  printf("Enter a mathematical expression: ");
  scanf ("%i %c %i", &num1, &operator, &num2);
  
  if (operator == '+') {
     result = num1 + num2;
     printf ("\nResult is: %d \n\n", result);
}
  else if (operator == '-'){
    result = num1 - num2;
     printf("\nResult is: %d \n\n", result);
}
  else if (operator == '*'){
    result = num1 * num2;
     printf("\nResult is: %d \n\n", result);
}
   else if (operator == '/'){
    result2 = (float)num1 / num2;
     printf("\nResult is: %.2f\n\n", result2);
}
  else 
    printf("You entered an incorrect operator\n\n");
   
  printf("\n\nDo you want to go again? 1 for yes, 0 for no\n");
  scanf ("%d", &goAgain);
  } while (goAgain == 1);
  return 0;
}


