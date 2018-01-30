#include <stdio.h>
float absoluteValue (float x)
 {
 if (x < 0)
 x = -x;
 return x;
 }
 int main (void)
 {
 float f1 = -25.5, f2 = 20.0, f3 = -5.2;
 float result;
 result = absoluteValue (f1);
 printf ("f1 = %.1f \n", f1);
    // Outcome is -25.5; to get 25.5, variable must be result, not f1
 return 0;
 }
