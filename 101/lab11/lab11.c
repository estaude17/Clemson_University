#include <stdio.h>
#include <string.h>

int my_strlen (char s1[])
{
 int ndx = 0;
 while (s1[ndx] != '\0')
  {
   ndx++;
  }
 return ndx + 1;
}

void my_strcat (char s1[], char s2[])
{
 int i = 0;
 int j = 0;
 while (s1[i] != '\0')
 {
  i++;
 }
 
 while (s2[j] != '\0')
 {
   s1[i] = s2[j];
   i++;
   j++;
 }
 s1[i] = '\0';
 printf("%s\n", s1); 
}

int main (void)
{
 char v1[16];
 char v2[16];
 int i1, i2;


 scanf("%7s", v1);
 scanf("%7s", v2);

 i1 = my_strlen(v1);
 i2 = my_strlen(v2);

 printf("len: %3d - string: %s\n", i1, v1); 
 printf("len: %3d - string: %s\n", i2, v2); 
  
 my_strcat(v1, v2);

return 0;
}

