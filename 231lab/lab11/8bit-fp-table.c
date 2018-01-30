/*
Elizabeth Stauder(estaude)
CPSC 2311-002
March 31, 2016
This generates a table of all 256 possible 8-bit floating point numbers
*/
#include <stdio.h>
int main()
{
  int sign, exp, fraction, significand;
  int i;
  float f;
  float prev = 0;

  for (i = 0; i < 256; i++)
  {
	/* begin your code*/
        int j = 0;
        sign =(i >> 7) & 1;
        exp = (i >> 3) & 15;
        fraction = i & 7;
        
        int denorm = 1;
        if(exp == 0 ){
                denorm = 0;
                exp = -7;
        }
        else exp = exp - 8;

        significand = denorm;
        significand = (significand << 3) | fraction;

        exp = exp-3;

        f = significand;

        if(exp > 0){
                for(j=0; j<exp; j++){ f= f * 2; }
        }
        else{
         for(j=0; j>exp; j--){ f = f/2; }
        }
        if(sign == 1)f=-1 *f;
       /*end your code*/

    printf ("%02x => %08x = %+11.6f (spacing = %+11.6f)\n",
            i, *(int*) &f, f, prev-f);
    prev = f;
  }

  return 0;
}
