#include <stdio.h>

int main(void){
 int i, j, a[100][100], b[100], c[100];
  int n = 100;
  for (i = 0; i < n; i++) {
    c[i] = 0;
    for (j = 0; j < n; j++) {
      c[i] = c[i] + a[i][j] * b[j];
    }
  }

}
