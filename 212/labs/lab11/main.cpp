/*Elizabeth Stauder(estaude)
CPSC 2121-001
Lab 11, November 17, 2015
Breadth-first search.
*/
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct State {
  string name;
  vector<string> neighbors;
};

map<string, State *>:: iterator it;//global iterator

typedef pair<int, string> Point;
Point p;

vector<Point> states;
set<Point> s;

map<string, int> dists;
map<string, State *> Nodes;
 
int BFS(string s)//s is the source.
{
  //create new iterator for breadth-first search
  map<string, State *>:: iterator iter;
  int dist;
  for(iter = Nodes.begin(); iter != Nodes.end(); iter++){
	dists[iter->first] = 51;
	}
  //51 chosen because the number is larger than the number of states on the map
  dists[s] = 0;
  queue<string> state;
  state.push(s);
  while(!state.empty()){
	string temp = state.front();
	state.pop();
  	for(int i = 0; i < Nodes[temp]->neighbors.size(); i++){
		if (dists[Nodes[temp]->neighbors[i]] == 51){
			dist=
			dists[Nodes[temp]->neighbors[i]] = dists[temp] + 1;
			//every neighbor's distance is +1 of the original.
			state.push(Nodes[temp]->neighbors[i]);
			}
		}
   	}
  return dist;
}

int main(void)
{
  string x, y;
  
  ifstream graph;
  graph.open("usa_48_state_graph.txt");

  while(graph >> x >> y)
	{
  	if(Nodes.count(x) > 0) Nodes[x]->neighbors.push_back(y);
	else	{
		Nodes[x] = new State;
		Nodes[x]->name = x;
		Nodes[x]->neighbors.push_back(y);
		}
	if(Nodes.count(y) > 0) Nodes[y]->neighbors.push_back(x);
	else{
		Nodes[y] = new State;
		Nodes[y]->name = y;
		Nodes[y]->neighbors.push_back(x);
		}
	}
  graph.close();

  for(it = Nodes.begin(); it != Nodes.end(); it++){
	int e = BFS(it->first);//calls breadth-first search function
	p.second = it->first;
	p.first = e;
	states.push_back(p);
	}
	
  sort(states.begin(), states.end());
  
  for(int i = 0; i < states.size(); i++) 
	cout << states[i].second << " " << states[i].first << endl;
  	
return 0;
}