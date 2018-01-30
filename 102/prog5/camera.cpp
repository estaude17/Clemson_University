/*Elizabeth Stauder (estaude)
CPSC 1020-001 
04/20/15
This program allocates memory for a camera structure
and loads the data for the structure.

camera.c */

#include "ray.h"

static pparm_t camera_parse[] =
{
   {"pixeldim",  2, 4, "%d",  0},
   {"worlddim",  2, 8, "%lf", 0},
   {"viewpoint", 3, 8, "%lf", 0}
};

#define NUM_ATTRS (sizeof(camera_parse) / sizeof(pparm_t))

/**/
int camera_t::getydim(void)
{
   return(pixel_dim[1]);
}

/**/
void camera_t::getviewpt(vec_t *view)
{
   vec_copy(&view_point, view);
}

/**/
int camera_t::getxdim(void)
{
   return(pixel_dim[0]);
}

camera_t::camera_t(FILE *in)
{
   char buf[256];
   int mask;

   assert(fscanf(in, "%s", name) == 1);   
   
   fscanf(in, "%s", buf);
   assert(buf[0] == '{');

   cookie = CAM_COOKIE;

   camera_parse[0].loc = &pixel_dim;
   camera_parse[1].loc = &world_dim;
   camera_parse[2].loc = &view_point;
 
   mask = parser(in, camera_parse, NUM_ATTRS, 0);
   assert(mask == 7);

   // This part will allocate a structure to hold the image data.
   pixmap = (irgb_t*)malloc(sizeof(irgb_t)*pixel_dim[0]*pixel_dim[1]);
}       
//=============================================================================
void camera_t::camera_print (FILE *out)
{
   fprintf(out, "camera %-12s \n",name);
   fprintf(out, "pixeldim %5d %5d\n", pixel_dim[0], pixel_dim[1]);
   fprintf(out,"worlddim %5lf %5lf\n", world_dim[0], world_dim[1]);
   fprintf(out,"viewpoint %5lf %5lf %5lf\n", view_point.x,
   	view_point.y, view_point.z);
}

//=============================================================================

void camera_t::getdir(int x, int y, vec_t *dir){
   //assert(cam->cookie == CAM_COOKIE);
   vec_t world;
   double dx = x;
   double dy = y;

   //This part converts pixel coordinates to world screen coordinates.
   world.x = dx * world_dim[0] / (pixel_dim[0] - 1);
   world.y = dy * world_dim[1] / (pixel_dim[1] - 1);
   world.z = 0.0;

   // This computes vector from viewpoint to world screen coordinates.
   vec_copy(&world, dir);
   vec_diff(&view_point, &world, dir);

   // This will convert vectors to unit length vectors.
   vec_unit(dir, dir);
}

//=============================================================================
// These next two functions convert a pixel from drgb_t to irgb_t and
//      stores it in the image associated with the camera 
//=============================================================================
unsigned char scale_and_clamp(float pixel_color)
{
   float new_value = pixel_color * (255.0 + 0.5);

   if(new_value < 0.0)
   {
      	return(unsigned char)0;
   }

   else if(new_value > 255.0)
   {
   	return(unsigned char)255;
   }

   else
   {
      	return(unsigned char)new_value;
   }
}
void camera_t::store_pixel(int x, int y, drgb_t *pix)
{
   int maprow;
   irgb_t *maploc;

   maprow = pixel_dim[1] - y - 1;
   maploc = pixmap + maprow * pixel_dim[0] + x;

   maploc->r = scale_and_clamp(pix->r);
   maploc->g = scale_and_clamp(pix->g);
   maploc->b = scale_and_clamp(pix->b);   
}

//=============================================================================

void camera_t::camera_write_image(FILE *out)
{
   fprintf(out, "P6\n %d %d 255\n", pixel_dim[X], pixel_dim[Y]);
   fwrite(pixmap, sizeof(irgb_t), pixel_dim[X] * pixel_dim[Y], out);
}
