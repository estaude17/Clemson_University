/*Elizabeth Stauder (estaude) CPSC 1010-001; 12/01/14
rotate.c: takes in width, height, and image pointer. 
Program reverses width and height in order to get the right dimensions.
*/
#include "transform.h"

void rotate(int x, int y, pixel_t rotate_image[x*y]) {

	//height is y, width is x - will be reversed because image is on side
	int i, j;

	fprintf (stdout,"P6\n%d %d 255\n", y, x);

	for (i = 0; i < x; i++){
	     for (j = x - i; j < x*y; j = j + x) {
		fprintf (stdout,"%c%c%c", rotate_image[j].r, rotate_image[j].g, 
						rotate_image[j].b);
		}
	}
}
