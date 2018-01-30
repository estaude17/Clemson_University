/*Elizabeth Stauder (estaude)
04/20/15
CPSC 1020-001
This file contains the find_closest_object() function.
if an object is hit, retdist will end up with the mindist
and minobj will be a non-NULL object that is returned.
It also contains the add_illumination function, which adds illumination
to objects hit by lights.
raytrace.c  */

#include "ray.h"

object_t *find_closest_object(model_t  *model, vec_t  *base, vec_t  *dir,
                              object_t  *last_hit, double  *retdist)
{
   object_t *minobj = NULL;
   double mindist = -1.0;
   double dist;
   object_t *obj;
   list_t *list = model->objs;
   list->reset();

   while (list->not_end()){
        obj = (object_t *)list->get_entity();
        if(obj != last_hit){
                dist = obj->hits(base, dir);
        /*if no object is hit, then retdist will have the value -1, 
        and NULL will be returned */
                if(dist > 0){
                        if(mindist == -1 || dist < mindist){
                                minobj = obj;
                                        mindist = dist;
                                        }
                                }
                        }
        list->next_link();
        }
   /*if an object is hit, retdist will end up with the mindist
   and minobj will be a non-NULL object that is returned.*/
   *retdist = mindist;
   return(minobj);
}
void add_illumination(
model_t *model,     //object list                    
vec_t *base,
object_t *hitobj,   //object that was hit by the ray 
drgb_t   *pixel)    // where to add intensity         
{
   light_t *light;
   list_t *list = model->lgts;
   list->reset();
   while (list->not_end())
   {
      light = (light_t *)list->get_entity();
      light->illuminate(model, base, hitobj, pixel);
      list->next_link();
   }
}
