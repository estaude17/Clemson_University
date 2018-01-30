/*November 24, 2015
Elizabeth Stauder(estaude)
CPSC 2121-001
Write an implementation of Dijkstra's 
single-source shortest path algorithm.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

struct Edge {
  int src, dst;
  float travel_time;
};

typedef pair<float, int> p;
int N, M;
Edge *E;
int start = 17731931;
float *dists;
int *first_edge;
priority_queue<p> q;

// compare two edges based on their source nodes 
// (break ties using destination nodes)
bool comp(Edge e1, Edge e2)
{
  if (e1.src == e2.src) return e1.dst < e2.dst;
  return e1.src < e2.src;
}
//runs Dijkstra's algorithm
double dijkstra(float *dists, int *first_edge)
{
  for(int i = 0; i < N; i++)dists[i] = 99999999999; //set to "infinity".
	dists[start] = 0;
	q.push(p(dists[start], start));//build priority queue
	float x = 0;
	//create path
	while(!q.empty()){
		p temp = q.top();
		q.pop();
		for(int i = first_edge[temp.second]; i < M && 
		E[i].src == temp.second; i++)
			{
			if(dists[temp.second] + E[i].travel_time < 
			dists[E[i].dst])
				{
				dists[E[i].dst] = dists[temp.second] + 
				E[i].travel_time;
				q.push(p(-dists[E[i].dst], E[i].dst));
				if(dists[E[i].dst] > x) x = dists[E[i].dst];
				}
			}
		}
  return x;
}

int main(void)
{
  FILE *fp = popen ("zcat /tmp/usa_network.txt.gz", "r");
  fscanf (fp, "%d %d", &N, &M);
  E = new Edge[M];
  printf ("Reading input");
  for (int i=0; i<M; i++) {
    fscanf (fp, "%d %d %f", &E[i].src, &E[i].dst, &E[i].travel_time);
    if (i % 1000000 == 0) { printf ("."); fflush(stdout); }
  }
  fclose(fp);
  printf (" Done.\n" ); fflush(stdout); 

  sort(E, E+M, comp);
  
  first_edge = new int [N];
  dists = new float [N];

  int i = 0;
  for(int j = 0; j < M; j++){
	if(E[j].src != E[j-1].src)
		{
		i++;
		first_edge[i] = j;
		}
	}
  //all elements of first_edge array first initialized to 0.
  float x = dijkstra(dists, first_edge);
 
  for(int k = 0; k < M; k++) swap(E[k].src, E[k].dst);
  
  //repeat process to find both upper and lower bounds.
  sort(E, E+M, comp);
  
  first_edge = new int [N];
  dists = new float [N];

  int j = 0;
  for(int l = 0; l < M; l++){
	if(E[l].src != E[l-1].src)
		{
		j++;
		first_edge[j] = l;
		}
	}
  //all elements of first_edge array first initialized to 0.
  float y = dijkstra(dists, first_edge);

  float result1 = (x + y) / 2;
  float result2 = x + y;
 
  cout << "The diameter is bound between the lower bound " << result1 
  << " and the upper bound " << result2 << endl;

  return 0;
}
