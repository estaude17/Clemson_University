/* main.c */

#include "color.h"

//global-scope array
color_t cvals[1000];

int main() {
   int count = 0;
   int i;
   color_t *cloc = NULL;

	/* Read color name and (r, g, b) values into current entry in */
	/* the color table.                                           */
   while ( get_color(&cvals[count])==0 ) {
      count++;
   }

	/* Compute the luminance of each of the colors */
   for (i = 0; i < count; i++) {
      compute_luminance(&cvals[i]);
   }

	/* Find the color having the greatest luminance */
   cloc = find_brightest(cvals, count);

	/* Print out the details of that color */
   printf("Lum: %d  Comps: %d %d %d  Name: %s \n",
                   cloc->luminance,
                   cloc->pixel.r, cloc->pixel.g, cloc->pixel.b,
                   cloc->name);

   return(0);
}
