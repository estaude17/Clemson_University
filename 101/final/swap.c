#include <stdio.h>
/*
void swap(int first, int second){
int temp;
temp = first;
first = second;
second = temp;

printf("first is %d and second is %d\n", first, second);
}*/

int main (void) {
int a = 5;
int b = 6;
//swap(a, b);
int temp;
temp = a;
a = b;
b = temp;

printf("a is %d and b is %d\n", a, b);

return 0;
}
