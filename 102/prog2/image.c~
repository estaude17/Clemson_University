/*Elizabeth Stauder (estaude)
CPSC 1020-001, 02/25/2015
This program contains a raytracer and  makes a ppm image based 
off of parameters it is passed from other functions.
image.c
*/
#include "ray.h"

//=============================================================================

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
   object_t *obj;

   obj = (object_t *)list_get_entity(model->objs);

	/* This part gets the distance and the color */
   dist = obj->hits(obj, base, dir);  
   obj->ambient(obj, obj->mat, &thispix);

   if(obj->hits(obj, base, dir) != -1.0)
	{
	total_dist += dist;
	thispix.r = (1/total_dist) * thispix.r;
	thispix.g = (1/total_dist) * thispix.g;
	thispix.b = (1/total_dist) * thispix.b;

	pix->r += thispix.r;
	pix->g += thispix.g;
	pix->b += thispix.b;
	}
}

//============================================================================= 

void make_pixel(model_t  *model, int  x, int  y) {
   
   vec_t raydir;
   drgb_t pix = {0.0, 0.0, 0.0};
   camera_t *cam = model->cam;

   camera_getdir(cam, x, y, &raydir);

   ray_trace(model, &cam->view_point, &raydir, &pix, 0.0, NULL);

   camera_store_pixel(cam, x, y, &pix);

   return;
}

//=============================================================================

void make_row(model_t  *model, int  y) 
{
   int x;
   camera_t *cam = model->cam;

//this part fires rays through each pixel in the window.

   for (x = 0; x < cam->pixel_dim[0]; x++) {
 	make_pixel(model, x, y);
 	}
}
 
//=============================================================================

void image_create(model_t  *model, FILE  *out) 
{
   int y;
   camera_t *cam = model->cam;

//this part fires rays through each pixel in the window.

   for (y = 0; y < cam->pixel_dim[1]; y++) {
	 make_row(model, y);
 	}

   /*  write the ppm image                           */
   camera_write_image(model->cam, out);
}

