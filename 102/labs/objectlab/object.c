/* Elizabeth Stauder
2/08/15
Lab 1021-004
This file contains object function definitions for raytracer
object.c */

/* object_init()
	object_list_print()
	object_print()
	object_no_hit()
*/

#include "ray.h"


//**
// initializes a new object:
// 	the object's name, and its material 
// 	(this function is already complete, but look it over)
void  object_init(FILE  *in, model_t  *model)
{
   object_t   *obj;
   material_t *mat;
   char buf[NAME_LEN];
   int count;

   /* Create a new object structure and zero it */
   obj = malloc(sizeof(object_t));
   assert(obj != NULL);
   memset(obj, 0, sizeof(object_t));
   obj->cookie = OBJ_COOKIE;

   /* Read the descriptive name of the object   */
   /* e.g. left_wall, center_sphere, floor, etc. */
   count = fscanf(in, "%s", obj->obj_name);
   assert(count == 1);

   /* Consume the delimiter { */
   count = fscanf(in, "%s", buf);
   assert(buf[0] == '{');

   /* The first attribute must be material */
   count = fscanf(in, "%s", buf);
   assert(count == 1);
   assert(strcmp(buf, "material") == 0);

   /* Now get the name of the material (blue, green, etc) */
   count = fscanf(in, "%s", buf);
   assert(count == 1);

   /* If the material is defined,  save a pointer to the */
   /* mat structure in the object structure. Failure to  */
   /* find the material is a fatal error.                */
   mat = material_getbyname(model, buf);
   assert(mat != NULL);
   obj->mat = mat;

   /* Initialize default handlers */
   obj->printer  = object_print;
   obj->hits     = object_no_hit;
   obj->ambient  = material_getambient;
   obj->diffuse  = material_getdiffuse;
   obj->specular = material_getspecular;

   /* Finally add the object to the list */
   list_add(model->objs, (void *)obj);
}

void object_list_print(model_t  *model, FILE  *out)
{
   object_t *obj;

   list_reset(model->objs);

	while(list_not_end(model->objs)){
		obj = list_get_entity(model->objs);
		assert(obj->cookie == OBJ_COOKIE);
		obj->printer(obj, out);
		list_next_link(model->objs);	
	}
}

void object_print(object_t *obj, FILE *out)
{
   assert(obj->cookie == OBJ_COOKIE);
 
   fprintf(out,"\n%-12s %-6s\n", obj->obj_type, obj->obj_name); 
   fprintf(out, "%-12s %-6s\n", "material", obj->mat->name);
 
}

double object_no_hit(object_t  *obj, vec_t  *base, vec_t  *dir)      
{
   assert(obj->cookie == OBJ_COOKIE);
   fprintf(stderr, "Object %s failed to provide hit func \n",
                    obj->obj_name);

   return(-1.0);    // negative distance means miss.
}

