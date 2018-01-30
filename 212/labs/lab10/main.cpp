/*Elizabeth Stauder(estaude)
CPSC 2121-001
Lab 10, November 10, 2015
Finds the closest pair among 1 million points on a 2D plane.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

double D;
//storing points in STL pairs(p.first will be x, p.second will be y)
typedef pair<double, double> Point;
//Point p;

//storing points in STL vector
vector<Point> v;

//inserting point v[j] into STL set
set<Point> s;

set<Point>::iterator it;

double dist(double x1, double y1, double x2, double y2)
{
  return sqrt(((x1 - x2) * (x1 - x2)) + ((y1- y2) * (y1- y2)));
}

int main(void)
{
  double x, y;
  ifstream text;
  text.open ("points.txt");
  while(text >> x >> y) v.push_back(Point(x, y));
  //fills vector with points from the file.
  text.close();

  int i = 0; //as i increases, removes points from set
  sort(v.begin(), v.end());//sorts all the points on x.
  D = dist(v[1].first, v[1].second, v[0].first, v[0].second);

  //as j increases, inserts points into set;
  for(int j = 0; j < v.size(); j++){
  	//swaps x and y coordinates before inserting them into set.
	s.insert(Point(v[j].second, v[j].first)); 
	while((v[j].first - v[i].first) > D){
		s.erase(Point(v[i].second, v[i].first));
		i++;
		}
  	//find shortest distance within set:
  	it = s.find(Point(v[j].second, v[j].first));
	it++;
	//have we reached the one element past the end of the set?
	while(it != s.end() && (it->first - v[j].second) < D){
		double d = 
		dist(it->second, it->first, v[j].first, v[j].second);
		if(d < D) D = d;
		it++;//move to successor
		}

	it = s.find(Point(v[j].second, v[j].first));
 	//have we reached the beginning?
	while(it != s.begin() && (it->first - v[j].second) < D){
		it--;//move to predecessor
		double d = 
		dist(it->second, it->first, v[j].first, v[j].second);
		if(d < D) D = d;
		}
  	}
  cout << "Best distance is " << D << endl;
  return 0;
}