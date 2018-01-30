#include<stdio.h>

typedef struct pixel_type {
 unsigned char r;
 unsigned char g;
 unsigned char b;
 } pixel_t; 

int main(void)
{
int width, height, color;

fscanf(stdin, "P6 %d %d %d\n", &width, &height, &color);

int area = width * height;

pixel_t list[area];
int i;
for (i = 0; i < area; i++){
	scanf("%c%c%c", &list[i].r, &list[i].g, &list[i].b);
}

fprintf(stdout, "P6\n");
fprintf(stdout, "%d %d %d\n", width, height, color);

for (i = 0; i < area; i++){
	list[i].r = 255 - list[i].r;
	list[i].g = 255 - list[i].g;
	list[i].b = 255 - list[i].b;
	fprintf(stdout, "%c%c%c", list[i].r, list[i].g, list[i].b);
     }
return 0;
}
