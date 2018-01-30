//Elizabeth Stauder (estaude) CPSC 1010-001; 12/01/14;
//The main driver: This program readers in header info from parse.c and
//sends the information into the three transformation functions.

#include "transform.h"

int main (int argc, char *argv[]) 
{
        int search, width, height, color;
        char offset;

	// opening input file

        FILE *infile = fopen(argv[2], "r");
	if(infile == NULL)
	{
	   fprintf(stderr, "Improper Header!\n");
	   exit(1);
	}
   //searches for widths and heights and reads lines one at a time.
       search = getc(infile);
       search = getc(infile);

       if (search == '#'){
          while (search != '\n'){
              search = getc(infile);}
           fscanf(infile, "%i %i", &width, &height);
       }
       search = getc(infile);
       if (search == '#'){
          while (search != '\n'){
              search = getc(infile);
          }
           fscanf(infile,"%i", &color);
       }
 
       //this is used to restore colors so you don't get negatives.
       offset = getc(infile);

//      parseHeader(argc, *infile, *argv);
 
	// malloc space for the array (allocation and store pixel data)
     pixel_t * image = (pixel_t*) malloc(sizeof(pixel_t) * g_width * g_height);
     fread (image, sizeof(pixel_t), g_width * g_height, infile);

//      parseImage(infile, image);
 
        fclose(infile);
        free (image);    

	// chooses manipulate the image according to command-line parameter
	            if (*argv[1] == '1'){  		
                     // 1: mirror image
                            mirror(g_width, g_height, image);
}
                    else if (*argv[1] == '2'){
	//		2: upside down image
                            flipHoriz(g_width, g_height, image);
}
                    else if (*argv[1] == '3'){
	//		3: rotate to the right 90 degrees
                            rotate(g_width, g_height, image);
}
    
	return 0;
}


	
