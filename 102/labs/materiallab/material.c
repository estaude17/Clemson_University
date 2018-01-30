/* Elizabeth Stauder
2/05/15
Lab 1021-004
This file contains function definitions for    
for material operations */

/* material.c */

#include "ray.h"

void material_init(FILE *in, model_t *model, int attrmax)    
{
	material_t *mat = (material_t*)malloc(sizeof(material_t));
	memset (mat, 0, sizeof(material_t));
	mat->cookie = MAT_COOKIE;

   	material_load_attributes(in, mat);

   	list_add(model->mats, (void *)mat);


}
void material_load_attributes(FILE *in, material_t *mat)
{
  char attrib_name[16];
  int count = 0;     
  
  count = fscanf(in, "%s", mat->name);
  assert(count == 1);


  count = fscanf(in, "%s", attrib_name);
  assert(count == 1);
  assert(attrib_name[0] == '{');

  count = fscanf(in, "%s", attrib_name);
  assert(count == 1);
 
  while(attrib_name[0]  !=  '}'  ){
	if(strcmp(attrib_name,  "ambient")  == 0){
	  count = fscanf(in, "%lf %lf %lf", &mat->ambient.r, &mat->ambient.g, &mat->ambient.b);
	  assert(count  ==  3);
		}
	else if(strcmp(attrib_name,  "diffuse")  == 0){
	  count = fscanf(in, "%lf %lf %lf", &mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b);
	  assert(count  ==  3);
		}
	else if(strcmp(attrib_name,  "specular")  == 0){
	  count = fscanf(in, "%lf", &mat->specular);
	  assert(count  ==  1);
		}
	else {
	  fprintf(stderr, "Bad camera attribute: %s \n", attrib_name);
	  exit(1);
		}
	fscanf(in, "%s", attrib_name);
    }
}

material_t *material_getbyname(model_t *model, char *name)    
{
   material_t *mat;

   list_reset(model->mats);
   while(list_not_end(model->mats)){
	mat = list_get_entity(model->mats);
	assert(mat->cookie == MAT_COOKIE);
	if(strcmp(mat->name, name) == 0){
		return(mat);
	}
	list_next_link(model->mats);
   }
return NULL;
}

void material_print(material_t *mat, FILE *out)
{ 
   fprintf(out, "material %-12s \n",mat->name);
   fprintf(out, "ambient %.1lf %.1lf %.1lf\n", mat->ambient.r, mat->ambient.g, mat->ambient.b);
   fprintf(out,"diffuse %.1lf %.1lf %.1lf\n", mat->diffuse.r, mat->diffuse.g, mat->diffuse.b);
   fprintf(out,"specular %.1lf\n\n", mat->specular);


}

void material_list_print(model_t *model, FILE *out)
{
    	material_t *mat;
  	list_reset(model->mats);
 	while(list_not_end(model->mats)){
		mat = list_get_entity(model->mats);
		assert(mat->cookie == MAT_COOKIE);
  		material_print(mat, out);
  		list_next_link(model->mats);
	}
}

void material_getambient(object_t *obj, material_t *mat, drgb_t *dest)   
{
	pix_copy(&mat->ambient, dest);
}

void material_getdiffuse(object_t *obj, material_t *mat, drgb_t *dest)
{
	pix_copy(&mat->diffuse, dest);
}

double material_getspecular(object_t *obj, material_t *mat)
{
	return mat->specular;
}
