/* Elizabeth Stauder
02/19/15
Lab 1021-004
This file contains the find_closest_object() function.
if no object is hit, then retdist will have the value -1, 
and NULL will be returned 
if an object is hit, retdist will end up with the mindist
and minobj will be a non-NULL object that is returned.

raytrace.c  */

#include "ray.h"

object_t *find_closest_object(model_t  *model, vec_t  *base, vec_t  *dir,
                              object_t  *last_hit, double  *retdist)     {
	object_t *minobj = NULL;
	double mindist = -1.0;
	double dist;
	object_t *obj;

	list_reset(model->objs);

	while (list_not_end(model->objs)){
		obj = (object_t *)list_get_entity(model->objs);
		if(obj != last_hit){
			dist = obj->hits(obj, base, dir);
		
			if(dist > 0){
				if(mindist == -1 || dist < mindist){		
					minobj = obj;
					mindist = dist;
			}
				}
			}			
	list_next_link(model->objs);
	}
*retdist = mindist;
return(minobj);
}


