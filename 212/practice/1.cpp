#include <iostream>
using namespace std;

struct Node {
  Node (int _s, Node *_next) {
    s = _s;
    next = _next;
  }
  int s;
  Node *next;
};

Node *H[1000];

bool find(Node *head, string s)
{
  //int count = 0;
  while (head) {
    if (head->s == s) return true;
    head = head->next;
  }
  return false;
}

int hash(int k)
{
  return (unsigned)(2971*k + 101923) % 1000;
}

int main(void)
{
  //  Node *n = new Node("Brian", NULL);
  string s;
  Node *head = NULL;
  while (cin >> s) {
    int h = hash(s);
    if (find(H[h], s)){
      cout << "duplicate found\n";
      return 0;}
  H[h] = new Node(s, H[h]);
  return 0;
}

/*
  string s;
  cout << "What is your name: ";
  cin >> s;
  cout << "Hello, " << s << ".\n";
 */
