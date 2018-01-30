/*Elizabeth Stauder (estaude) CPSC 1010-001; 12/01/14
flipHoriz.c: takes in width, height, and pointer.
Program
*/
#include "transform.h"

void flipHoriz(int x, int y, pixel_t flip_image[x*y])
{
  int i, j;

   fprintf (stdout,"P6\n%d %d 255\n", x, y);

   for (i = 1; i <= x; i++) {
	for (j = (i * y); j > (i * y) - y; j--) {
		fprintf (stdout,"%c%c%c", flip_image[j].r, flip_image[j].g, 
						flip_image[j].b);
           }
      }
}
