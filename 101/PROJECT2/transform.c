// Elizabeth Stauder - estaude - 12/12/14
// CPSC 1010 - section 001
//mainDriver.c - reads in header info & sends into transformation functions

#include "transform.h"

int main (int argc, char *argv[]) {

	char lettertype, numbertype;
	int width, height, maxcolor, commentSearch;
	char offset;

	//opens the file
	FILE *infile = fopen (argv[2], "r");
	if (infile == NULL) { 
		printf ("File Open error. Exiting program...\n");
		exit (1);
	}
	
	//stores the 'P6' - used when originally parsing header only stores 
	//	dummy variables now
	fscanf (infile,"%c", &lettertype);
	fscanf (infile,"%c", &numbertype);
	
	//searches for comments and w & h, reads line by line one at a time
	commentSearch = getc(infile);
	commentSearch = getc(infile);
	if(commentSearch == '#') {
		while (commentSearch != '\n') {
			commentSearch = getc(infile);
		}
		fscanf(infile, "%i %i", &g_width, &g_height);
	}
	else {
		ungetc(commentSearch, infile);
		fscanf(infile, "%i %i", &g_width, &g_height);
	}
	
	//check for comments and the maxcolor - mainly used when originally 
	//	parsing header
	commentSearch = getc(infile);
	if(commentSearch == '#') {
		while (commentSearch != '\n') {
			commentSearch = getc(infile);
		}
		fscanf(infile, "%i", &maxcolor);
	}
	else {
		ungetc(commentSearch, infile);
		fscanf(infile, "%i", &maxcolor);
	}

	//restores colors to not weird negatives
	offset = getc(infile);
	
	//allocation and stores pixel data 
	pixel_t *image = (pixel_t *) malloc (sizeof(pixel_t) * g_width * g_height);
	fread (image, sizeof(pixel_t), g_width*g_height, infile);

	//used to determine which manipulation
	if (*argv[1] == '1') {
		mirror(g_width, g_height, image);
	}
	else if (*argv[1] == '2') {
		flipHoriz(g_width, g_height, image);
	}
	else if (*argv[1] == '3') {
		rotate(g_width, g_height, image);
	}
	else {
		printf ("Wrong input number\n");
	}
	
	fclose(infile);
	free(image);
	return 0;
}

