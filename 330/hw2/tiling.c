#include <stdio.h>

int main(void){

int i, j, a[1000][1000], b[1000], c[1000];
  int n = 1000;
  for (i = 0; i < n; i++) {
    c[i] = 0;
    for (j = 0; j < n; j++) {
      c[i] = c[i] + a[i][j] * b[j];
    }
  }
}
