#include <stdio.h>
#include <math.h>

int min(int a, int b){
  if(a < b) return a;
  else if (b < a) return b;
  //else return 0;
}


int main(void){
 int i, j, x, y, a[1000][1000], b[1000], c[1000];
  int n = 1000;
  for (i = 0; i < n; i += 2) {
    c[i] = 0;
    c[i + 1] = 0;
    for (j = 0; j < n; j += 2) {
      for (x = i; x < min(i + 2, n); x++) {
        for (y = j; y < min(j + 2, n); y++) {
          c[x] = c[x] + a[x][y] * b[y];
        }
      }
    }
  }

}
