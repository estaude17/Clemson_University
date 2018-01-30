/*
Elizabeth Stauder (estaude)
CPSC 1020-001
04/20/15
This program parses, prints, and loads the data for the fplane structure.
fplane.cpp */

#include "ray.h"


#define NUM_ATTRS (sizeof(fplane_parse) / sizeof(pparm_t))

void fplane_t::printer(FILE *out)
{
   plane_t::printer(out); 
   //I called the regular plane printer to print the regular stuff.
   
   fprintf(out, "%-12s %5.1lf %5.1lf\n", "dims", dims[0], dims[1]);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "xdir", 
	xdir.x, xdir.y, xdir.z);
   fprintf(out, "%-12s %5.3lf %5.3lf %5.3lf\n", "projxdir", 
	projxdir.x, projxdir.y, projxdir.z);
   fprintf(out, "%-12s %5.3lf %5.3lf %5.3lf\n", "rot.row[0]",
       	rot.row[0].x, rot.row[0].y, rot.row[0].z);
   fprintf(out, "%-12s %5.3lf %5.3lf %5.3lf\n", "rot.row[1]",
      	rot.row[1].x, rot.row[1].y, rot.row[1].z);
    fprintf(out, "%-12s %5.3lf %5.3lf %5.3lf\n", "rot.row[2]",
     	rot.row[2].x, rot.row[2].y, rot.row[2].z);
}
double fplane_t::hits(
vec_t    *base,      /* ray base              */
vec_t    *dir)       /* unit direction vector */
{
   vec_t newloc;
   double t;

   t = plane_t::hits(base, dir);
   //this part invokes the plane's hit point.
   if(t == -1)
	{
	return(-1);
  	//this indicates that there was no hit within fplane bounds.
	}
   vec_diff(&point, &last_hitpt, &newloc);
   vec_xform(&rot, &newloc, &newloc);

   if(0 <= newloc.x && newloc.x <= dims[0])
	{
	if(0 <= newloc.y && newloc.y <= dims[1])
		{
		vec_copy(&newloc, &rothit);
		return(t);
		//this means that the hit is within the bounds of fplane.
		}
	}
   return(-1);
}

static pparm_t fplane_parse[] =
{
   {"xdir",    3, 8, "%lf", 0},
   {"dimensions", 2, 8, "%lf", 0}
};

fplane_t::fplane_t(FILE *in, model_t *model, 
int attrmax) : plane_t(in, model, 2)
{
   int mask;
   strcpy(obj_type, "fplane");
	
   fplane_parse[0].loc = &xdir;
   fplane_parse[1].loc = &dims;
   mask = parser(in, fplane_parse, NUM_ATTRS, attrmax);
   assert(mask == 3);
	
   vec_unit(&normal, &normal);
   vec_project(&normal, &xdir, &projxdir);
   //this part projects xdir onto plane, creating projxdir.
   if (projxdir.x == 0.0 && projxdir.y == 0.0 && projxdir.z == 0.0)
	{
	return;//this part ensures that projxdir isn't (0, 0, 0)
	}
   //this part makes a matrix that can rotate the projxdir vector into
   //the x-axis and the plane normal into the positive z-axis.
   vec_unit(&projxdir, &projxdir);
   vec_copy (&projxdir, &rot.row[0]);
   vec_copy (&normal, &rot.row[2]);
   vec_cross(&rot.row[2], &rot.row[0], &rot.row[1]);
}

