/*Elizabeth Stauder(estaude)
CPSC 2120-001
Project 3-1
October 30, 2015
*/
#include <fstream>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

struct Wire
	{
	double x;
	double y;
	};

//randomizes tour
void Random(int* i)
{
  for(int a = 0; a < 936; a++)
	{
	i[a] = a;
	int b = rand() % (a+1);
	swap(i[a], i[b]);
	}
}

//computes distance between two points
double tourdistance(int* location, int x1, int y1)
{
  double start = location[x1];
  double end = location[y1];
  double result = ((end-start) * (end-start));
  return result;
}

//computes total distance of tour
double tourtotal(int* W, Wire* Wires)
{
  double tour = 0;
  for (int i = 0; i < 2664; i++)
	{
  	tour += tourdistance(W, Wires[i].x, Wires[i].y);
  	}	
  return tour;
}

//refines tour
void Tour(int* location, int* sequence, Wire* Wires)
{
  double a, b, best;
  for(int i = 0; i < 935; i++)
	{
	int point = i;
	int point2 = i+1;

	a = tourtotal(location, Wires);
	swap(sequence[point], sequence[point2]);
	swap(location[sequence[point]], location[sequence[point2]]);
	b = tourtotal(location, Wires);
	if(a < b)
		{
		best = a;
		swap(sequence[point], sequence[point2]);
		swap(location[sequence[point]], location[sequence[point2]]);
		}
	else	best = b;
	}
}

int main(void)
{
  srand(time(NULL));
  double x, y;
  Wire* Wires = new Wire[2664];
  int sequence[936];
  int location[936];
  int i = 0;
  //reads in input points from wires.txt
  ifstream fin("wires.txt");
  while(fin >> x >> y)
	{
	Wires[i].x = x;
	Wires[i].y = y;
	i++;
	}
  fin.close();

  Random(sequence);//This randomly permutes the contents of the array
 
  int number;
  for (int a = 0; a < 936; a++)
	{
	number = sequence[a];
	location[number] = a;
	}
  cout << "Random value is " << tourtotal(location, Wires) << endl;
  for(int j = 0; j < 2; j++)//repeats process for optimal refinement.
  {
  for(int b = 0; b < 1500; b++)
	{
	Tour(location, sequence, Wires);
	}
  }
  //just in case tourtotal still over a million; runs functions again.
  if(tourtotal(location, Wires) > 1000000){
	 
	Random(sequence);//creates new random sequence to be refined.
  	int number;
  	for (int a = 0; a < 936; a++)
        {
        	number = sequence[a];
        	location[number] = a;
        }
  	cout << "Second random value is " << 
		tourtotal(location, Wires) << endl;
  	for(int j = 0; j < 2; j++)//repeats process for optimal refinement.
  		{
  		for(int b = 0; b < 1500; b++)
        		{
        		Tour(location, sequence, Wires);
        		}
  		}
	}
  cout << "Best objective value is "<< tourtotal(location, Wires) << endl;
  delete [] Wires;
  return 0;
}