/* Elizabeth Stauder (estaude) 02/09/15
CPSC 1020-001
In this assignment, camera functions were made that will be implemented to 
store, write, load, and print values associated with the camera.
*/

#include "ray.h"

void camera_init(FILE *in, model_t *model, int attrmax) {
	int attribcount;

	camera_t *mycam = (camera_t*)malloc(sizeof(camera_t));
	mycam->cookie = CAM_COOKIE;

	attribcount = camera_load_attributes(in, mycam);
	assert(attribcount == 3);

	// This part will allocate a structure to hold the image data.
	
	mycam->pixmap = (irgb_t*)malloc(
		sizeof(irgb_t)*mycam->pixel_dim[0]*mycam->pixel_dim[1]);

  	model->cam = mycam;
}

//=============================================================================

int camera_load_attributes(FILE *in, camera_t *cam) {
  char attrib_name[16];
  int count = 0;     // This signifies the number of items read.
  int attrcount = 0; // This signifies the total number of attributes.

  count = fscanf(in, "%s", cam->name);
  assert(count == 1);


  count = fscanf(in, "%s", attrib_name);
  assert(count == 1);
  assert(attrib_name[0] == '{');

  count = fscanf(in, "%s", attrib_name);
  assert(count == 1);

  while (attrib_name[0] != '}'){
 	if (strcmp(attrib_name, "pixeldim") == 0){
	count = fscanf(in, "%d %d", &cam->pixel_dim[X], &cam->pixel_dim[Y]);
	assert(count == 2);
	attrcount += 1;
 	}	

	else if (strcmp(attrib_name, "worlddim") == 0){
	count = fscanf(in, "%lf %lf", &cam->world_dim[X], &cam->world_dim[Y]);
	assert(count == 2);
	attrcount += 1;
	}

	else if (strcmp(attrib_name, "viewpoint") == 0){
	count = fscanf(in, "%lf %lf %lf", &cam->view_point.x, 
		&cam->view_point.y, &cam->view_point.z);
	assert(count == 3);
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
//=============================================================================
void camera_print (camera_t *cam, FILE *out) {
	assert(cam->cookie == CAM_COOKIE);

fprintf(out, "camera %-12s \n",cam->name);
fprintf(out, "pixeldim %5d %5d\n", cam->pixel_dim[0], cam->pixel_dim[1]);
fprintf(out,"worlddim %5lf %5lf\n", cam->world_dim[0], cam->world_dim[1]);
fprintf(out,"viewpoint %5lf %5lf %5lf\n", cam->view_point.x, 
	cam->view_point.y, cam->view_point.z);
}

//=============================================================================

void camera_getdir(camera_t *cam, int x, int y, vec_t *uvec) {
	assert(cam->cookie == CAM_COOKIE);
	vec_t world;

	//This part converts pixel coordinates to world screen coordinates.

	world.x = (double) x / (cam->pixel_dim[0] - 1) * cam->world_dim[0];
        world.y = (double) y / (cam->pixel_dim[1] - 1) * cam->world_dim[1];
        world.z = 0.0;


	// This computes vector from viewpoint to world screen coordinates.
 	vec_diff(&cam->view_point, &world, uvec);



	// This will convert vectors to unit length vectors.
	vec_unit(uvec, uvec);


}

//=============================================================================
// These next two functions convert a pixel from drgb_t to irgb_t and
// 	stores it in the image associated with the camera 
//=============================================================================

unsigned char get_rgb(float pixel_color){
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
void camera_store_pixel(camera_t *cam, int x, int y, drgb_t *pix)
{
   assert(cam->cookie == CAM_COOKIE);

   int row, col;
   row = cam->pixel_dim[Y] - y - 1;
   col = x;

   irgb_t *ipix;
   ipix = cam->pixmap + row * cam->pixel_dim[X] + col;
   ipix->r = get_rgb(pix->r);
   ipix->g = get_rgb(pix->g);
   ipix->b = get_rgb(pix->b);
}

//=============================================================================

void camera_write_image(camera_t *cam, FILE *out) {
	fprintf(out, "P6\n");
	fprintf(out, "%d %d 255\n", cam->pixel_dim[X], cam->pixel_dim[Y]);
	fwrite(cam->pixmap, 
		sizeof(irgb_t), cam->pixel_dim[X] * cam->pixel_dim[Y], out);
}
