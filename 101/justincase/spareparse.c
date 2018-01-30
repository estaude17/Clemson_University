include <stdio.h>
#include <stdlib.h>
#define RGB_COMPONENT_COLOR 255

int main (int argc, int *argv[])
{
	int c=0, count=0, loop;
	char buff[190];
	dim_t size;

	//Check for file readin
	if(argc<3)
	{
		fprintf(stderr, "File wasnt retrieved!\nProgram Terminated\n");
		exit(1);
	}
	
	//Open file
	FILE *file=fopen(arv[2], "r");
	fgets(buff,190, file);
	//Header check
	if((buff[0]!='P')||(buff[1]!='6'))
	{
		fprintf(stderr, "Improper Header!\nProgram Terminated\n");
		exit(1);
	}
	//Retrieve dimensions/different checks
	if(count==0)
	{
		do
		{
			fgets(buff,190,file);
		}
		while(buff[count]=='#');
		count+=sscanf(buff, "%d %d %d", &size.x, &size.y, &size.z);
		if(count==0)
		{
			fprintf(stderr, "Failed Length Input!\nProram Terminated\n");
			exit(1);
		}
	}
	if(count==1)
	{
		do
		{
			fgets(buff, 190, file);
		}
		while(buff[count]=='#');
		count+=sscanf(buff, "%d %d", &size.y, &size.z);
		if(count==1)
		{
			fprintf(stderr, "Failed height Input!\nProgram Terminated.\n");
			exit(1);
		}
	}
	if(count==2)
	{
		do
		{
			fgets(buff, 190, file);
		}
		while(buff[count]=='#');
		count+=sscanf(buff, "%d", &size.z);
		if(count==2)
		{
			fprintf(stderr, "Failed color input!\nProgram Terminated.\n");
			exit(1);
		}
	}
	//mem allocation
	size.data=(pix_t *) malloc(sizeof(pix_t) * size.x * size.y);
	//storing Image
	for(loop=0; loop<(size.x * size.y); loop++;)
	{
		fscanf(file, "%c%c%c", &size.data[loop].r, &size.data[loop].g, &size.data[loop].b);
	}
	//close file
	fclose(file);
	
	//Insert any function calls here

	//Printout
	//header 
	fprintf(stdout, "P6\n %d %d %d\n", size.x, size.y, size.z);
	//pixel printout
	for(loop=0; loop<(size.x * size.y); loop++)
	{
		fprintf(stdout, "%c%c%c", size.data[loop].r, size.data[loop].g, size.data[loop].b);
	}
	return 0;
}
