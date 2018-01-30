#include <iostream>
#include <cstdio>
using namespace std;

int foo;

fight_foo(int foo)
{
 return foo;
}

void swap(int &x, int &y)
{
  int temp = x;
  x = y;
  y = temp;
}

int main(void)
{
  int a = 3, b = 4;
  swap(a, b);
  cout << a << " " << b << endl;
  fight_foo() = 7;
  return 0;
}
