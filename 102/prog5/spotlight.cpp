/*
Elizabeth Stauder (estaude)
04/20/15 
CPSC 1020-001
This program allocates memory for a plane structure,
parses, and loads the data for the structure.
tplane.c
*/
#include "ray.h"

#define NUM_ATTRS (sizeof(spotlight_parse) / sizeof(pparm_t))

static pparm_t spotlight_parse[] =
{
   {"point", 3, sizeof(double), "%lf", 0},
   {"theta", 1, sizeof(double), "%lf", 0},
};

void spotlight_t::printer(FILE *out)
{
   light_t::printer(out);
   //This part prints the spotlight attributes after after light's printer.
   fprintf(out, "point %5.1lf %5.1lf %5.1lf\n", 
	point.x, point.y, point.z);
   fprintf(out, "direction %5.1lf %5.1lf %5.1lf\n", 
	direction.x, direction.y, direction.z);
   fprintf(out, "halfwidth %5.1lf\n", halftheta);
   

}
spotlight_t::spotlight_t(
FILE *in, model_t *model, int attrmax) : light_t(in, model, 2)
{
   int mask;
   double radians;
   vec_t newvec;

   spotlight_parse[0].loc = &point;
   spotlight_parse[1].loc = &halftheta;
   mask = parser(in, spotlight_parse, NUM_ATTRS, 0);
   assert(mask == 3);

   vec_diff(&location, &point, &newvec);
   vec_unit(&newvec, &direction);
   //this part computes the unit vector and stores it in direction
   radians = (halftheta / 180)* M_PI;
   costheta = cos(radians);
   //this converts halftheta to radians and stores its cosine in costheta.
}

int spotlight_t::vischeck(vec_t *hitloc)
{
   vec_t vec;
   double cosVal;
   vec_diff(&location, hitloc, &vec);
   vec_unit(&vec, &vec);
   //this part computes the unit vector from the location of the spotlight to
   //the hit location and stores it in vec.
   cosVal = vec_dot(&vec, &direction);
   //this part calculates the dot product of vec and spotlight's direction and
   //stores it in cosVal.
   if (cosVal > costheta)//this means that the hitpoint should be illuminated.
	{
	return 0;
	}
   else{
	return 1;
	}
}
