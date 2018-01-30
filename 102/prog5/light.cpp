/*
Elizabeth Stauder
CPSC 1020-001
04/20/15
This program parses and loads the data for the light class.
light.c */

#include "ray.h"

/* Parser parameter array for light attributes */
static pparm_t light_parse[] =
{
   {"location",   3, sizeof(double), "%lf", 0},
   {"emissivity",  3, sizeof(double), "%lf", 0}
};

#define NUM_ATTRS (sizeof(light_parse) / sizeof(pparm_t))

void light_t::printer(FILE *out)
{
   fprintf(out, "%-12s %s \n", "light", name);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "location", 
				location.x, location.y, location.z);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "emissivity", 
				emissivity.r, emissivity.g, emissivity.b);
}
void light_t::illuminate(
model_t *model, vec_t *base, object_t *hitobj, drgb_t *pixel)
{
   vec_t    dir;    // unit direction to light from hitpt
   object_t *obj;   // closest object in dir to light
   double   close;  // dist to closest object in dir to light
   double   cos;    // of angle between normal and dir to light
   double   dist;   // to the light from hitpoint
   drgb_t   diffuse = {0.0, 0.0, 0.0};

   drgb_t emiss = {0.0, 0.0, 0.0};
   getemiss(&emiss);   

   vec_t hitnorm, last_hitpt;

   hitobj->getlast_hitpt(&last_hitpt);
   vec_diff(&last_hitpt, &location, &dir);
   dist = vec_len(&dir);
   vec_unit(&dir, &dir);

   hitobj->getlast_normal(&hitnorm);

   cos = vec_dot(&dir, &hitnorm);
   if(cos <= 0)
 	{
	return;
	}
  int val = vischeck(&last_hitpt);

  if (val == 1)
	{
	return;
	}

   // Ask find_closest_object() if a ray fired toward the light 
   // hits another object.
   obj = find_closest_object(model, &last_hitpt, &dir, hitobj, &close);

   // If an object is hit and the distance to the hit is 
   // closer to the hitpoint than the light is, return     

   if(obj != NULL && close < dist)
	{
	return;
	}

   /* Arriving at this point means the light does illuminate 
   object. Ask hitobj->getdiff() to return diffuse
   reflectivity. */                                       
   hitobj->getdiffuse(&diffuse);

   /* Multiply componentwise the diffuse reflectivity by 
   the emissivity of the light. */                         

   pix_prod(&diffuse, &emissivity, &diffuse);

   // Scale the resulting diffuse reflectivy by cos/dist     
   cos = cos / dist;
   pix_scale(cos, &diffuse, &diffuse);

   // Add scaled value to pixel.                            

   pix_sum(&diffuse, pixel, pixel);

   add_glint(hitobj, base, &dir, pixel);
   //this part calls the add_glint function.
}

/* Create a new light object and initialize it */

light_t::light_t(FILE *in, model_t *model, int attrmax)
{
   int mask, count;
   char attrname[NAME_LEN];

   cookie = LGT_COOKIE;

   count= fscanf(in, "%s", name);
   assert(count == 1);   
   //this part grabs the attrname with fscanf.
   count = fscanf(in, "%s", attrname);
   assert(attrname[0] == '{');

   light_parse[0].loc = &location;
   light_parse[1].loc = &emissivity;
   mask = parser(in, light_parse, NUM_ATTRS, attrmax);
   assert(mask == 3);

   model->lgts->add((void *)this);
   //this part adds the instance of the light to the lgts list.
}

/* Produce a formatted print of the light list */
void light_list_print(model_t *model, FILE *out)
{
   light_t *light;
   list_t *list = model->lgts;
   list->reset();

   while (list->not_end())
   {
    	light = (light_t *)list->get_entity();
      	light->printer(out);
      	list->next_link();
   }
}
void light_t::getemiss(drgb_t *dest)
{
   assert(cookie == LGT_COOKIE);
   pix_copy(&emissivity, dest);
}
void light_t::getloc(vec_t *dest)
{
   assert(cookie == LGT_COOKIE);
   vec_copy(&location, dest);
}
int light_t::vischeck(vec_t *vis)
{
   return 0;
}
void light_t::add_glint(
object_t *hitobj, 
vec_t *base, 
vec_t *dir, 
drgb_t *pixel)
{
   double shine, dot, spec;
   vec_t lasthit, hitnorm, g;
   drgb_t pix;

   hitobj->getshine(&shine);
   if(shine == 0)
      	{
	return;
	}  
   hitobj->getlast_hitpt(&lasthit);
   //this part gets the lasthit and stores it in a local variable.
   vec_diff(&lasthit, &location, dir);
   vec_unit(dir, dir);
   //these parts compute unit vectors from the hitpoint to the light
   vec_diff(&lasthit, base, &g);
   vec_unit(&g, &g);
   //these parts compute unit vectors from the hitpoint to the base
   vec_sum(&g, dir, &g);
   vec_unit(&g, &g);
   
   hitobj->getlast_normal(&hitnorm);
   vec_unit(&hitnorm, &hitnorm);
   dot = vec_dot(&g, &hitnorm);
   dot = pow(dot, shine);

   hitobj->getspecular(&spec);
   
   dot = dot * spec;
   pix_scale(dot, &emissivity, &pix);
   //this part scales the emissivity of the light by dot * specular.
   pix_sum(pixel, &pix, pixel);
}
