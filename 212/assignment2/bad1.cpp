/*
Elizabeth Stauder(estaude)
CPSC 2120-001
October 2, 2015
bad1.cpp
This program will print out the longest line of sight for prog1.cpp
given input N, but with an input N that causes it to run slowly.
*/
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 2) {
    cout << "Usage: bad1 <input size>\n";
    return 0;
  }

  int N = atoi(argv[1]);  // get first command-line argument
  if (N<1 || N>100000) {
    cout << "Invalid input size!\n";
    return 0;
  }
  
  // Generate and print bad input of size N for prog1
  cout << N << "\n";
  for (int i = N; i > N/2; i--)
  	{
	cout << i << "\n";
	}
  for (int i = N/2; i < N; i++)
	{
	cout << i << "\n";
	}
  return 0;
}
