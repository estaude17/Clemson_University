#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

const int N = 936;

double position[N];
int rounded_position[N];
bool pinned[N];
vector<int> nbrs[N];

void read_input(void)
{
  ifstream fin("wires.txt");
  int a, b;
  while (fin >> a >> b) {
    nbrs[a].push_back(b);
    nbrs[b].push_back(a);
  }
  fin.close();
}

int per_node_objective(int n)
{
  int total = 0;
  for (int i=0; i<nbrs[n].size(); i++) {
    int p1 = rounded_position[n];
    int p2 = rounded_position[nbrs[n][i]];
    total += (p1-p2) * (p1-p2);
  }
  return total;
}

int total_objective(void)
{
  int total = 0;
  for (int i=0; i<N; i++)
    total += per_node_objective(i);
  return total/2;
}

bool refine(void)
{
  double movement = 0.0;
  for (int i=0; i<N; i++)
    if (!pinned[i]) {
      double pos_sum = 0.0;
      for (int j=0; j<nbrs[i].size(); j++) 
	pos_sum += position[nbrs[i][j]];
      double new_pos = pos_sum / nbrs[i].size();
      movement += fabs(new_pos - position[i]);
      position[i] = new_pos;
    }
  return movement / (N-2) > 0.0001;
}

typedef pair<double, int> pdi;

int main(void)
{
  read_input();
  int best = 999999999;
  int best_order[N];
  vector<pdi> V;
  for (int iter=0; iter<100; iter++) {
    for (int i=0; i<N; i++) position[i] = (double)i;
    random_shuffle(position, position+N);
    for (int i=0; i<N; i++)
      pinned[i] = (position[i] == 0.0 || position[i] == (double)(N-1));
    int count = 0;
    while (refine()) {
      if (0 && count % 1000 == 0)
	cout << "Iteration " << count << " " << total_objective() << "\n";
      count++;
    }
    for (int i=0; i<N; i++) V.push_back(pdi(position[i], i));
    sort(V.begin(), V.end());
    for (int i=0; i<N; i++) rounded_position[V[i].second] = i;
    V.clear();
    if (total_objective() < best) {
      best = total_objective();
      for (int i=0; i<N; i++) best_order[i] = rounded_position[i];
    }
    cout << iter << ": " << total_objective() << "\n";
  }
  cout << "Best solution: " << best << "\n";
  //  for (int i=0; i<N; i++) cout << position[i] << " ";
  //  cout << "\n";
  return 0;
}
