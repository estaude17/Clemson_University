/*
Elizabeth Stauder(estaude)
CPSC 2121-001
December 1, 2015
Decode text using trie
*/
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

// A node in our decoding trie
struct Node{
  int letter;
  int pID; //ID of parent.
  Node (int l, int p) {letter = l; pID = p;}
};

vector<Node> t; //creating decoding trie

//recursively print path except for parent, then print parent.
void print(int n)
{
  if(n == 0) return;
  print(t[n].pID);
  if(t[n].letter != -1) cout << (char) t[n].letter;

}

int main(void)
{
  t.push_back(Node(0,0));
  int l2, p2; //variables hold ASCII input from encoding program
  while(cin >> l2 >> p2) t.push_back(Node(p2, l2));

  //walking down trie until at the end of text
  for(int i = 1; i < t.size(); i++) print(i);
  return 0;
}
