
#include <stdio.h>

int main(void){
  int i, j, k;
  int A[1000], B[1000], C[1000];
	for (i=0; i<1000; i+=2) {
 		for (j=0; j<1000; j++) {
 			for (k=0; k<1000; k++) {
 				C[i,j] += A[i,k] * B[k,j];
 				C[i+1,j] += A[i+1,k] * B[k,j];
 		}
	}
  }
} 
