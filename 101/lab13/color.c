/* color.c */

#include "color.h"

int get_color(color_t *color)
{
int r, g, b;

if(fscanf(stdin, "%d %d %d", &r, &g, &b) == 3)
{
    color -> pixel.r = r;
    color -> pixel.g = g;
    color -> pixel.b = b;

    fgets(color -> name, 64, stdin);

return (0);
}

else{
return (-1);
}
}

void compute_luminance(color_t *color)
{
   color -> luminance = (color -> pixel.r * 0.30) + (color -> pixel.g * 0.59) + (color -> pixel.b * 0.11);

}

color_t *find_brightest(color_t *colors, int count)
{
color_t *max = &colors[0];
int i;
for(i = 0; i < count; i++)
{
if (colors[i].luminance > max -> luminance){
	max = &colors[i];
}
}
return max;
}
