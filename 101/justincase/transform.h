#include <stdio.h>
#include <stdlib.h>

struct pixel {
	char r, g, b;
};

int g_width, g_height;

void parseHeader( FILE *input );
void parseImage( FILE *input, struct pixel *theArray );


// other function prototypes here


