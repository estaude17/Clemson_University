/* Elizabeth Stauder (estaude)
2/25/15
CPSC 1020-001
This file contains sphere function definitions for raytracer

sphere.c */

#include "ray.h"
#include <math.h>

void sphere_init(FILE  *in, model_t  *model, int  attrmax)
{
   sphere_t *sph;
   object_t *obj;
   int count;

        object_init(in, model);

        obj = (object_t *)list_get_entity(model->objs);

        sph = (sphere_t*)malloc(sizeof(sphere_t));

        obj->priv = sph;

        strcpy(obj->obj_type, "sphere");


   count = sphere_load_attributes(in, sph, attrmax);
   assert(count == 2);

        obj->hits = sphere_hits;
        obj->printer = sphere_print;

}

int sphere_load_attributes(FILE  *in, sphere_t  *sphere, int  attrmax)
{
  char attrib_name[16];
  int count = 0;
  int attrcount = 0;

  count = fscanf(in, "%s", attrib_name);
  assert(count == 1);

  while (attrib_name[0] != '}'){
        if (strcmp(attrib_name, "center") == 0){
        count = fscanf(in, "%lf %lf %lf", &sphere->center.x, &sphere->center.y, &sphere->center.z);
        assert(count == 3);
        attrcount += 1;
        }

        else if (strcmp(attrib_name, "radius") == 0){
        count = fscanf(in, "%lf", &sphere->radius);
        assert(count == 1);
        attrcount += 1;
        }

        else {
        fprintf(stderr, "Bad camera attribute: %s \n", attrib_name);
        exit(1);
                }
        fscanf(in, "%s", attrib_name);
        }

return(attrcount);
}

void sphere_print(object_t  *obj,FILE  *out)
{
   sphere_t *sph;

   sph = obj->priv;

   object_print(obj, out);

   fprintf(out, "%-12s %3.1lf %3.1lf %3.1lf\n", "center", sph->center.x,
                sph->center.y, sph->center.z);
   fprintf(out, "%-12s %3.1lf\n", "radius", sph->radius);
}



double sphere_hits(object_t  *obj, vec_t  *base, vec_t  *dir)
{
        double a, b, c, quad, discriminant;
	sphere_t *sph;
	
	vec_t Vprime; // V - C (viewpoint - center); new base.
	vec_t H; //Vector for hitpoint.
	vec_t N; //Vector for normale.
	vec_t Nu; //new value of N vector after unit function.
	
        assert (obj->cookie == OBJ_COOKIE);

	sph = obj->priv;
	
	vec_diff(&sph->center, base, &Vprime);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(&Vprime, dir);
	c = vec_dot(&Vprime, &Vprime) - (sph->radius * sph->radius);

	discriminant = (b * b) - (4 * a * c);
    
	if (discriminant <= 0){
		return -1.0; }

	quad = (b * (-1.0) - sqrt(discriminant)) / (2 * a);

	vec_scale(quad, dir, &H); //H = V + quad * D.
	vec_sum(base, &H, &H);	
	vec_copy(&H, &obj->last_hit); //copy H to obj->last->hit.
	vec_diff(&sph->center, &H, &N);
	vec_unit(&N, &Nu); // Nu = (H-C) / ||(H-C)||.
	vec_copy(&Nu, &obj->last_normal); //copy Nu to obj->last->normal.

        return quad;
}
