#include <stdio.h>

void make_pixel (int r, int g, int b)
{
  fprintf(stdout, "%c%c%c", r, g, b);
}

void make_ppm_header(int width, int height)
{
  fprintf(stdout, "P6\n");
  fprintf(stdout, "%d %d %d\n", width, height, 255);
}

void make_ff_rows(int width)
{
int i;
for (i = 0; i < (width/3); i++)
{
    make_pixel(0, 85, 164);
}
for (; i < 2*(width/3); i++)
{
    make_pixel(255, 255, 255);
}
for (; i < (width); i++){
    make_pixel(250, 60, 50);}
}

void make_france_flag(country_code, width){
int i;
int height = (width * 2) / 3;

make_ppm_header(width, height);

for (i = 0; i < height; i++)
{
    make_ff_rows(width);
}
}
void make_german_flag(country_code, width)
{
int i;
int height = (width * 3) / 5;
int area = width * height;

make_ppm_header(width, height);

for (i = 0; i < area/3; i++)
{
    make_pixel(0, 0, 0);

}
for (; i < 2*area/3; i++)
{
    make_pixel(255, 0, 0);
}
for (; i < area; i++)
{
    make_pixel(255, 204, 0);
}
}

void make_lith_flag(country_code, width)
{
int i;
int height = (width * 3) / 5;
int area = width * height;

make_ppm_header(width, height);

for (i = 0; i < area/3; i++)
{
    make_pixel(253, 185, 19);
}
for (; i < 2*area/3; i++)
{
    make_pixel(0, 106, 68);
}
for (; i < area; i++)
{
    make_pixel(193, 37, 45);
}
}
int main (void)
{
int width;
int country_code;

fscanf(stdin, "%d %d", &country_code, &width);
fprintf(stderr, "Making country %d width %d\n", country_code, width);

if (country_code == 0)
{
     make_france_flag(country_code, width);
}
if (country_code == 1)
{
     make_german_flag(country_code, width);
}
if (country_code == 2)
{
     make_lith_flag(country_code, width);
}

return 0;
}

