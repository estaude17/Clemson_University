/*Elizabeth Stauder (estaude) CPSC 1010-001; 12/01/14
mirror.c:  takes in the width, height, and pointer to the memory
allocation, as well as pixels. to mirror them think of all the 
pixels in a 1-D array and then draw how they would be moved use 
width and height to manipulate the space the pixel info will be stored in*/

#include "transform.h"

void mirror (int x, int y, pixel_t mirror_image[g_width*g_height]) {
	//for convenience, g_width and g_height were replaced with x and y.

	int i, j;
	/*always print header first, not in loop - etc. for all other 
	manipulation files */
	fprintf (stdout,"P6\n%d %d 255\n", x, y);
	for (i = 1; i <= y; i++) {
	     for (j = (i*x); j > (i*x)-x; j--) {
		fprintf (stdout,"%c%c%c", mirror_image[j].r, mirror_image[j].g, 
				          mirror_image[j].b);
		}
	}
}

