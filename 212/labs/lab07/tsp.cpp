/*
Elizabeth Stauder(estaude)
CPSC 2120-001
Traveling Salesman Problem
October 20, 2015
*/
#include <fstream>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

struct Point
	{
	double x;//x coordinate of Points
	double y;//y coordinate of Points
	};

void Random(int* i)
{
  for(int a = 0; a < 50; a++)
	{
	i[a] = a;
	int b = rand() % (a+1);
	swap(i[a], i[b]);
	}
}

//computes distance between two points
double tourdistance(Point i, Point j)
{
  return sqrt(((i.x - j.x) * (i.x - j.x)) + ((i.y - j.y) * (i.y - j.y)));
}

//computes total distance of tour
double tourtotal(int* P, Point Points[])
{
  double tour = 0;
  for (int i = 0; i < 50; i++)
	{
	int j;
	if(i < 49)j = i+1;
	else j = 0;
  	tour += tourdistance(Points[i], Points[j]);
  	}	
  return tour;
}

void Tour(int* P, Point* Points)
{
  double a, b, best;
  for(int i = 0; i < 50; i++)
	{
//	for(int j = 1; j < 50; j++)
//		{//two randomly generated cities.
		int City = rand() % 50;
		int City2 = rand() % 50;
		while (City == City2) City2 = rand() % 50;
		a = tourtotal(P, Points);
		swap(P[City], P[City2]);
		b = tourtotal(P, Points);
		if(a < b)
			{
			best = a;
			swap(P[City], P[City2]);
			}
		else	best = b;
//		}
	}
}

int main(void)
{
  srand(time(NULL));
  double x, y;
  Point* Points = new Point[50];
  int P[50];
  int i = 0;
  //reads in input points from tsp_points.txt
  ifstream input;
  input.open("tsp_points.txt");

  while(input >> x >> y)
	{
	Points[i].x = x;
	Points[i].y = y;
	i++;
	}

  input.close();

  Random(P);//This randomly permutes the contents of the array

  for (int a = 0; a < 500; a++) Tour(P, Points);

  cout << "The best tour value is " << tourtotal(P, Points) << endl;

  for(int r = 0; r < 50; r++) cout << P[r] << endl;

  delete [] Points;

  return 0;
}
