/*Elizabeth Stauder (estaude) CPSC 1010-001; 12/01/14
transform.h: the header file
File contains prototypes for all connecting files.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct pixel {
	unsigned char r, g, b;
} pixel_t;

int g_width, g_height;

//void parseHeader(int, FILE *infile, int);
//void parseImage( FILE *input, struct pixel *theArray );
int main(int, int);
void mirror(int, int, pixel_t mirror_image[g_width*g_height]);
void flipHoriz(int, int, pixel_t flip_image[g_width*g_height]);
void rotate(int, int, pixel_t rotate_image[g_width*g_height]);
