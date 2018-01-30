#include <stdio.h>
#include <stdlib.h>

//struct definitions
typedef struct pixel_type
{
   unsigned char r;
   unsigned char g;
   unsigned char b;
}  pixel_t;

typedef struct color_type
{
   char name[64];
   pixel_t pixel;
   unsigned char luminance;
}  color_t;


//function prototypes
int get_color(color_t *color);
void compute_luminance(color_t *color);
color_t *find_brightest(color_t *colors, int count);

