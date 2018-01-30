/*
Elizabeth Stauder (estaude)
CPSC 1020-001
04/20/15
This program parses and loads the data for the triangle structure.
*/
#include "ray.h"

pparm_t triangle_parse[ ] =
{
   {"point1", 3, sizeof(double), "%lf", 0},
   {"point2", 3, sizeof(double), "%lf", 0},
   {"point3", 3, sizeof(double), "%lf", 0},
};

#define NUM_ATTRS (sizeof(triangle_parse) / sizeof(pparm_t))

triangle_t::triangle_t(FILE *in, model_t *model, int attrmax)
 : plane_t(in,model,2)
{
   int mask;
   strcpy(obj_type, "triangle");

   triangle_parse[0].loc = &point1;
   triangle_parse[1].loc = &point2;
   triangle_parse[2].loc = &point3;
   //this part parses in the three points of the triangle.
   mask = parser(in, triangle_parse, NUM_ATTRS, attrmax);
   assert(mask == 7);
}

void triangle_t::printer(FILE *out)
{
   plane_t::printer(out);
   //since this connects to the plane_t class, I call the plane printer to
   //print out the normal stuff first.
   fprintf(out, "%-12s %3.1lf %3.1lf %3.1lf\n", "point1", point1.x,
		point1.y, point1.z);
   fprintf(out, "%-12s %3.1lf %3.1lf %3.1lf\n", "point2", point2.x,
		point2.y, point2.z);
   fprintf(out, "%-12s %3.1lf %3.1lf %3.1lf\n", "point3", point3.x,
		point3.y, point3.z);
   //this part prints out the triangle attributes.
}

double triangle_t::hits(vec_t *base, vec_t *dir)
{
   double dist = 0.0, a = 0.0, b = 0.0;
   vec_t prime, e1, e2;

   dist = plane_t::hits(base,dir); 
   //this part calls the plane's hit point.
   if(dist < 0)
	{	
      	return -1;
	}
   //determines if triangle was hit.
   vec_diff(&point1, &last_hitpt, &prime);
   //q' = q - vo
   vec_diff(&point1, &point2, &e1);
   //e1 = v1 - vo
   vec_diff(&point1, &point3, &e2);
   //e2 = v2 - vo
   a = (vec_dot(&prime, &e2)) / (vec_dot(&e1, &e2));
   //alpha = (q' * e2) / (e1 * e2)
   b = (vec_dot(&prime, &e1)) / (vec_dot(&e1, &e2));
   //beta = (q' * e1) / (e1 * e2)
   if(a < 0 || b < 0 || (a+b) > 1)
	{
      	return -1;
	}
   //this part rejects the function if alpha or beta are less than zero
   //or when alpha plus beta is less than one.
   return dist;
}
