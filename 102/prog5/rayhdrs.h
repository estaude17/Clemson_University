/*Elizabeth Stauder (estaude)
04/20/15
CPSC 1020-001 */

/*  == material.c  ==  */

material_t *material_getbyname(model_t  *, char  *);

void material_list_print(model_t  *, FILE  *);

/*  == object.c ==  */
void object_list_print(model_t  *, FILE  *);
void light_list_print(model_t *, FILE *);

//find_closest_object prototype added:
object_t *find_closest_object(model_t  *model, vec_t  *base, vec_t  *dir,
                              object_t  *last_hit, double  *retdist);
/*  == raytrace.c == */
void ray_trace (
   model_t *model,
   vec_t *base,             //  view point
   vec_t *dir,              //  unit direction vector
   drgb_t *pix,             //  pixel return location
   double total_dist,       //  distance ray has travelled so far
   object_t *last_hitobj);  //  most recently hit object
void add_illumination(
   model_t *model,          //object list                    
   vec_t *base,
   object_t *hitobj,        //object that was hit by the ray 
   drgb_t   *pixel);        // where to add intensity   
/* == image.c == */
void make_pixel(model_t  *model, int  x, int  y);

void make_row(model_t  *, int );

void image_create(model_t  *, FILE  *);


/*==  parser.c ==  */
int parser(
FILE    *in,
pparm_t *pct,         /* parser control table                */
int      numattrs,    /* number of legal attributes          */
int      attrmax);    /* Quit after this many attrs if not 0 */

//randomize function in camera.cpp
//double randomize (double );
