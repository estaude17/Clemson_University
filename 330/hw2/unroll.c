#include <stdio.h>

int main(void){
  int i, j, k;
  int N = 1000;
  int A[1000], B[1000], C[1000];
  for (i=0; i<N; i++) 
 	for (j=0; j<N; j++) 
 		for (k=0; k<N; k++) 
 			C[i,j] += A[i,k] * B[k,j];

}
