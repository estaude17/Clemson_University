/*Elizabeth Stauder (estaude)
CPSC 1020-001 
04/20/2015
This program contains a raytracer and  makes a ppm image based 
off of parameters it is passed from other functions.
image.c
*/
#include "ray.h"   

//============================================================================= 
void make_pixel(model_t  *model, int  x, int  y)
{
   vec_t raydir, viewpt;
   drgb_t pix = {0.0, 0.0, 0.0};
   camera_t *cam = model->cam;
   int i;

   cam->getviewpt(&viewpt);
   for (i = 0; i < AA_SAMPLES; i++)
   {
  	cam->getdir(x, y, &raydir);

   	ray_trace(model, &viewpt, &raydir, &pix, 0.0, NULL);
   }
   pix_scale(1.0 / AA_SAMPLES, &pix, &pix);
   cam->store_pixel(x, y, &pix);

   return;
}
//=============================================================================
void make_row(model_t  *model, int  y)
{
   int x, xdim;
   camera_t *cam = model->cam;

   //this part fires rays through each pixel in the window.
   xdim = cam->getxdim();
   for (x = 0; x < xdim; x++) 
	{
        make_pixel(model, x, y);
        }
}
//=============================================================================
void image_create(model_t  *model, FILE  *out)
{
   int y, ydim;
   camera_t *cam = model->cam;

   //this part fires rays through each pixel in the window.
   ydim = cam->getydim();

   for (y = 0; y < ydim; y++) 
	{
         make_row(model, y);
        }

   //  write the ppm image                           
   cam->camera_write_image(out);
}
//RAYTRACE.C FUNCTION: NOW INCLUDES SPECULAR REFLECTION
void ray_trace (
   model_t *model,
   vec_t *base,                // view point
   vec_t *dir,                 // unit direction vector
   drgb_t *pix,                // pixel return location
   double total_dist,          // distance ray has travelled so far
   object_t *last_hit)         // most recently hit object
{
   double dist;
   drgb_t thispix = {0.0, 0.0, 0.0};
   object_t *closest;
   
   if(total_dist > MAX_DIST)
	{
	return;
	}
   closest = find_closest_object(model, base, dir, last_hit, &dist);
   /* This part gets the distance and the color */
   if(closest == NULL)
	{
	return;
	}
   closest->getambient(&thispix);
   add_illumination(model, base, closest, &thispix);
   dist = closest->hits(base, dir);
   if(dist > 0.0)
       	{
        total_dist += dist;
	pix_scale((1/total_dist), &thispix, &thispix);
	//pix_sum(&thispix, pix, pix);
        }
   //SPECULAR REFLECTION CODING
   double specref;
   closest->getspecular(&specref);
   vec_t lasthit, last_norm;
   if(specref != 0)
	{
      	drgb_t specint = {0.0, 0.0, 0.0};
      	vec_t ref_dir;
      	closest->getlast_hitpt(&lasthit);
      	closest->getlast_normal(&last_norm);
      	vec_reflect(&last_norm, dir, &ref_dir);
      	ray_trace(model, &lasthit, &ref_dir, &specint,
         total_dist, closest);
      	pix_scale(specref, &specint, &specint);
      	pix_sum(&specint, &thispix, &thispix);
   	}
   pix_sum(&thispix, pix, pix);
}
