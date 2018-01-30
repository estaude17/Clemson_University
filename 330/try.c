#include <stdio.h>
int main(){
    int row, col;
    scanf(" %i%i", &row, & col);
    int a[row][col];
    int i, j;
    for ( i = 0; i < row; i++ ) {
      for ( j = 0; j < col; j++ ) {
         printf("a[%d][%d] = %d\n", i,j, a[i][j] );
      }
    }
return 0;
}
