/* Elizabeth Stauder (estaude)
04/09/15
CPSC LAB 1021-004
This file contains function definitions for    
for 3D vector operations */

#include "vec.h"
vec_t::vec_t()
{
   x = y = z = 0.0;
}
vec_t::vec_t(double xi, double yi, double zi)
{
   x = xi;
   y = yi;
   z = zi;
}
void vec_t::vec_diff(const vec_t v2, vec_t &v3)
{
   v3.x = v2.x - x;
   v3.y = v2.y - y;
   v3.z = v2.z - z;
}
void vec_t::vec_diff(const vec_t *v2, vec_t &v3)
{
   v3.x = v2->x - x;
   v3.y = v2->y - y;
   v3.z = v2->z - z;
}
void vec_t::vec_diff(const vec_t &v2, vec_t *v3)
{
   v3->x = v2.x - x;
   v3->y = v2.y - y;
   v3->z = v2.z - z;
}
void vec_t::vec_read(void)
{
   cin >> x;
   cin >> y;
   cin >> z;
}
void vec_t::vec_prn(const char *label)
{
  cerr << label << x << "," << y << "," << z << endl;
}
double vec_t::vec_dot(const vec_t &v2)
{
   double product;
   product = (x * v2.x) + (y * v2.y) + (z * v2.z);
   return product;
}
double vec_t::vec_dot(const vec_t *v2)
{
   double product;
   product = (x * v2->x) + (y * v2->y) + (z * v2->z);
   return product;
}

void vec_t::vec_scale(double fact)
{
   x = fact * x;
   y = fact * y;
   z = fact * z;
}

double vec_t::vec_len(void)
{
   return sqrt((x *x) + (y * y) + (z * z));
}
