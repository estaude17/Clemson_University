/*Elizabeth Stauder (estaude)
CPSC 1020-001, 02/25/2015
This program alocates memory for a plane 
structure and loads the data for the structure.
plane.c
*/

#include "ray.h"

//=============================================================================

void plane_init(FILE  *in, model_t  *model, int  attrmax)
{
   plane_t  *pln;
   object_t *obj;
   int count;

   object_init(in, model);

   obj = (object_t *)list_get_entity(model->objs);

   pln = (plane_t *)malloc(sizeof(plane_t));

   assert(pln != 0);

   obj->priv = (void *)pln;

   strcpy(obj->obj_type, "plane"); 

   count = plane_load_attributes(in, pln, attrmax);
   assert(count == 2);

   obj->hits = plane_hits;   
   obj->printer = plane_print; 

   pln->ndotq = vec_dot(&pln->normal, &pln->point);
	//the normal and point return values are set to N dot Q.
}


//=============================================================================
// ******* plane_load_attributes( ) *******
// 
// loads the attributes as in other load_attribute functions
//=============================================================================
int plane_load_attributes(FILE  *in, plane_t  *pln, int  attrmax)
{
	char attrib_name[NAME_LEN];
	int count = 0;     // number of item read
	int attrcount = 0; // total number of attributes

	count = fscanf(in, "%s", attrib_name);
	assert (count == 1);

	while (attrib_name[0] != '}') {
		if (strcmp(attrib_name, "normal") == 0) {
		    count = fscanf(in, "%lf %lf %lf", 
			&pln->normal.x, &pln->normal.y, &pln->normal.z);
		    assert(count = 3);
		    attrcount += 1;
		}
		else if (strcmp(attrib_name, "point") == 0) {
		    count = fscanf(in, "%lf %lf %lf", 
			&pln->point.x, &pln->point.y, &pln->point.z);
		    assert(count = 3);
		    attrcount += 1;
		}
		else {
		fprintf(stderr, "Bad plane attribute: %s \n", attrib_name);
			exit(1);
		}

		/* read next attribute name */
		fscanf(in, "%s", attrib_name);
	}

	return attrcount;
}


//=============================================================================
// ******* plane_print( ) *******
// 
// prints a formatted version of the plane structure
// format should be consistent with camera_print() or material_print()   
//=============================================================================
void plane_print(object_t  *obj, FILE  *out)
{
	plane_t *pln;

	pln = (plane_t *)obj->priv;

	object_print(obj, out);
	
	fprintf(out, "normal %1.1lf %1.1lf %1.1lf \n", 
                        pln->normal.x, 
                        pln->normal.y, 
                        pln->normal.z);
			//printing normal from local pointer pln.
        fprintf(out, "point %1.1lf %1.1lf %1.1lf \n\n",
                        pln->point.x, 
                        pln->point.y, 
                        pln->point.z);
			//printing point from local pointer pln.
}


//=============================================================================
// ******* plane_hits( ) *******
//=============================================================================
double  plane_hits(object_t  *obj, vec_t  *base, vec_t  *dir)    
{
  	plane_t *plane;
	double distance;
	double ndotv;
	double ndotd;
	vec_t hit;

	plane = obj->priv;

	ndotd = vec_dot(&plane->normal, dir);
	
	if(ndotd == 0) //If N dot (P-Q) = 0.
	{
		return(-1); //returns -1 if ray misses the object.
	}

	ndotv = vec_dot(&plane->normal, base); 

	plane->ndotq = vec_dot(&plane->normal, &plane->point);
		//N dot Q = N dot P

	distance = (plane->ndotq - ndotv)/(ndotd);//N dot Q - N dot V / N dot D

	if(distance <= 0.0)
	{
		return(-1); //returns -1 if ray misses the object.
	}

	vec_scale(distance, dir, &hit);
	vec_sum(&hit, base, &hit);

	if (hit.z > 0.0)
	{
		return -1; //returns -1 if ray misses the object.
	}

	vec_copy(&hit, &obj->last_hit);
	vec_copy(&plane->normal, &obj->last_normal);

return distance; // distance = distance from base to point of contact.
}
