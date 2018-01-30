/* Elizabeth Stauder - estaude - 12/12/14
 * CPSC 1010 - section 001
 * Assignment #2
 * transform.h - the header file */

#include <stdio.h> 
#include <stdlib.h>

//pixelstruct of type pixel_t - remember it is a TYPE (ex int) not a name
typedef struct pixels {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} pixel_t;

int g_width, g_height;

/*prototypes - x is width, y height - They are seperate memory locations, 
	even though I used them in each function, I though this would help keep 
	things simple instead of having to come up with another pair of variables
	like t&p or q&z and try to keep them correlated to width and height */

void rotate(int x, int y, pixel_t rotate_image[x*y]);
void gray(int x, int y, pixel_t gray_image[x*y]);
void mirror(int x, int y, pixel_t mirror_image[x*y]);

