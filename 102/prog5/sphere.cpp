/* Elizabeth Stauder (estaude) 
04/20/15
CPSC 1020-001
This file contains sphere function definitions for raytracer

sphere.c */

#include "ray.h"
#include <math.h>

#define NUM_ATTRS (sizeof(sphere_parse) / sizeof(pparm_t))
static pparm_t sphere_parse[] =
{
   {"center",   3, 8, "%lf", 0},
   {"radius",  1, 8, "%lf", 0}
};

sphere_t::sphere_t(
FILE  *in, model_t  *model, int  attrmax) : object_t(in, model)
{
   int mask;

   strcpy(obj_type, "sphere");

   sphere_parse[0].loc = &center;
   sphere_parse[1].loc = &radius;
   mask = parser(in, sphere_parse, NUM_ATTRS, attrmax);
   assert(mask == 3);   
}

void sphere_t::printer(FILE  *out)
{
   object_t::printer(out);
   fprintf(out, "%-12s %3.1lf %3.1lf %3.1lf\n", "center", center.x,
                center.y, center.z);
   fprintf(out, "%-12s %3.1lf\n", "radius", radius);
}

double sphere_t::hits(vec_t  *base, vec_t  *dir)
{
   double a, b, c, dist, disc = 0.0;
   
   vec_t Vprime; // V - C (viewpoint - center); new base.
   vec_t H; //Vector for hitpoint.
   vec_t N; //Vector for normal.

   vec_diff(&center, base, &Vprime);
   a = vec_dot(dir, dir);
   b = 2.0 * vec_dot(&Vprime, dir);
   c = vec_dot(&Vprime, &Vprime) - (radius * radius);

   disc = (b * b) - (4 * a * c);

   if (disc <= 0 ||  a == 0.0)
	{
        return -1.0;
	}

   dist = ((-1.0 * b) - sqrt(disc)) / (2.0 * a);

   vec_scale(dist, dir, &H); //H = V + quad * D.
   vec_sum(&H, base, &H);
   vec_copy(&H, &last_hitpt);
   vec_diff(&center, &H, &H);
   vec_unit(&H, &N);
   vec_copy(&N, &last_normal);
   return dist;
}
