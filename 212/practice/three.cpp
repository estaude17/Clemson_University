#include <iostream>
#include <string>
using namespace std;

template <class T>
T min3(T a, T b, T c)
{
  if(a < b && a < c) return a;
  if(b < c) return b;
  return c;
}

int main(void)
{
  cout << min3(1, 2, 3);
  return 0;
}
