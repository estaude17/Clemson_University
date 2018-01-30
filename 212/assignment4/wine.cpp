#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

typedef pair<double, int> Neighbor;
priority_queue<Neighbor> kbest;

struct Point {
  double quality;
  double *data;
};

struct Node {
  int index;
  Node *left;
  Node *right;
  Node (int i) { index = i; left = right = NULL; }
};

int N, D, K;
Point *P;

Node *insert(Node *T, int index, int d)
{
  if (T == NULL) return new Node(index);
  if (P[index].data[d] <= P[T->index].data[d])
    T->left = insert(T->left, index, (d+1)%D);
  else
    T->right = insert(T->right, index, (d+1)%D);
  return T;
}

double dist(int i, int j)
{
  double total = 0.0;
  for (int d=0; d<D; d++) 
    total += pow(P[i].data[d] - P[j].data[d], 2);
  return sqrt(total);
}

/* By always guessing the same number (the average
   of all wine qualities), we get a squared error of
   0.793
*/

void find_nearest_nbrs(Node *T, int index, int d)
{
  if (T == NULL) return;
  if (index != T->index && 
      dist(index, T->index) < kbest.top().first) {
    kbest.pop();
    kbest.push(Neighbor(dist(index, T->index), T->index));
  }
  Node *visit_first = T->left, *visit_second = T->right;
  if (P[index].data[d] > P[T->index].data[d])
    swap (visit_first, visit_second);
  find_nearest_nbrs(visit_first, index, (d+1)%D);
  if (fabs(P[T->index].data[d] - P[index].data[d])
      > kbest.top().first) return;
  find_nearest_nbrs(visit_second, index, (d+1)%D);  
}

double classify(Node *T, int index)
{
  /* Find k nearest neighbors */
  while (!kbest.empty())
    kbest.pop();
  for (int k=0; k<K; k++)
    kbest.push(Neighbor(999999, 0));
  find_nearest_nbrs(T, index, 0);
  
  /* Compute a weighted average of their qualities */
  double num=0.0, den=0.0;
  while (!kbest.empty()) {
    double weight = exp(-0.1 * kbest.top().first);
    num += weight * P[kbest.top().second].quality;
    den += weight;
    kbest.pop();
  }
  return num/den;
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    cout << "Usage: wine <data file> <k>\n";
    return 0;
  }

  /* Read input data */
  ifstream fin(argv[1]);
  K = atoi(argv[2]);
  fin >> N >> D;
  P = new Point[N];
  for (int i=0; i<N; i++) {
    fin >> P[i].quality;
    P[i].data = new double[D];
    for (int j=0; j<D; j++)
      fin >> P[i].data[j];
    swap (P[i], P[rand() % (i+1)]);
  }
  fin.close();

  /* Normalize data in each coordinate */
  for (int j=0; j<D; j++) {
    double mean = 0.0;
    for (int i=0; i<N; i++) mean += P[i].data[j];
    mean /= N;
    for (int i=0; i<N; i++) P[i].data[j] -= mean;
    double var = 0.0;
    for (int i=0; i<N; i++) var += pow(P[i].data[j],2);
    double stddev = sqrt(var/N);
    for (int i=0; i<N; i++) P[i].data[j] /= stddev;
  }

  /* Build kd-tree */
  Node *T = NULL;
  for (int i=0; i<N; i++) 
    T = insert(T, i, 0);

  /* Classification */
  double error = 0.0;
  for (int i=0; i<N; i++)
    error += pow(P[i].quality - classify(T, i),2);
  error /= N;
  
  cout << error << "\n";

  return 0;
}
