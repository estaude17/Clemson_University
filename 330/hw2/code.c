#include <stdio.h>
int main(void){
  int i, j, k;
  int x[1000][1000];  
  for(k = 0;  k < 1000; k++)
	for(j = 0; j < 1000; j++)
		for(i=0; i < 1000; i++)
			x[i][j] = 2 * x[i][j];
  return 0;
}
