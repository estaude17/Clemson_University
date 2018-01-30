#include <iostream>
using namespace std;

struct Node {
  int key;
  Node *next;
  Node (int k) { key = k; next = NULL; }
  Node (int k, Node *n) { key = k; next = n; }
  Node () { key = 0; next = NULL; }
};

Node *head = NULL;

Node *insert_at_end(Node *head, int k)
{
  if (head == NULL) return new Node(k);
  head->next = insert_at_end(head->next, k);
  return head;
}

int main(void)
{
  int count = 0;
  while(1 > 0) {
    count++;
    head = insert_at_end(head, count);
    cout << count << "\n";
  }
  return 0;
}
