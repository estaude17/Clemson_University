/*
Elizabeth Stauder (estaude)
03/11/15 CPSC 1020-001
This program allocates memory for a tiled plane structure,
parses, and loads the data for the structure.
tplane.c
*/
#include "ray.h"

pparm_t tplane_parse[ ] =
{
   {"xdir", 3, sizeof(double), "%lf", 0},
   {"dimensions", 2, sizeof(double), "%lf", 0},
   {"altmaterial", 1, sizeof(NAME_LEN), "%s", 0},
};

#define NUM_ATTRS (sizeof(tplane_parse) / sizeof(pparm_t))

tplane_t::tplane_t(FILE *in, model_t *model, int attrmax)
 : plane_t(in,model,2)
{
   int mask;
   char buff [NAME_LEN];
   strcpy(obj_type, "tiled_plane");

   tplane_parse[0].loc = &xdir;
   tplane_parse[1].loc = &dims;
   tplane_parse[2].loc = &buff;
   
   mask = parser(in, tplane_parse, NUM_ATTRS, attrmax);
   assert(mask == 7);

   altmat = material_getbyname(model, buff);

   vec_unit(&normal, &normal);
   vec_project(&normal, &xdir, &projxdir);

   if (projxdir.x == 0.0 && projxdir.y == 0.0 && projxdir.z == 0.0)
   {
   	return;//ensures that projxdir is not (0.0, 0.0, 0.0)
   }
   vec_unit(&projxdir, &projxdir);
   vec_copy (&projxdir, &rot.row[0]);
   vec_copy (&normal, &rot.row[2]);
   vec_cross(&rot.row[2], &rot.row[0], &rot.row[1]);
}

void tplane_t::printer(FILE *out)
{
   plane_t::printer(out);
   //plane_t printer prints out normal stuff, move on to tplane attributes.
   fprintf(out, "%-12s %3.1lf %3.1lf %3.1lf\n", "xdir", xdir.x, 
	xdir.y, xdir.z);
   fprintf(out, "%-12s %3.1lf %3.1lf\n", "dimensions", dims[0], dims[1]);
   fprintf(out, "%-12s %5s\n", "altmaterial", altmat->material_getname());
}

int tplane_t::select(void)
{
   int dx, dy;
   vec_t newloc;

   vec_xform(&rot, &last_hitpt, &newloc);
   //this part applies rotation to the last_hit to rotate
   //it in the plane.
   newloc.x += 10000;
   newloc.y += 10000;

   dx = newloc.x / dims[0];
   dy = newloc.y / dims[1];

   if((dx + dy) % 2 == 0)// if (dx + dy) is even
      return (1);
   else
      return (0);
}

void tplane_t::getambient(drgb_t *value)
{
   int fg = select();
   if (fg == 0)
	{
      	object_t::getambient(value);
	//asks the default getambient to fill in value.
	}
   else
	{
      	altmat->material_getambient(value);
	//asks getambient to fill in the reflectivity of altmat.
	}
}

void tplane_t::getdiffuse(drgb_t *value)
{
   int fg = select();
   if (fg == 0)
	{
      	object_t::getdiffuse(value);
	//asks the default getdiffuse to fill in value.
   	}
   else
	{
      	altmat->material_getdiffuse(value);
	//asks getdiffuse to fill in the diffuse reflectivity of altmat.
	}
}
