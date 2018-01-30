/*
Elizabeth Stauder
*/
#ifndef STRINGSET_H /* Prevent multiple inclusion... */
#define STRINGSET_H

#include <string>
using namespace std;

struct Node {
  string key;
  int value;
  Node *next;
  Node(string k, int val, Node *n) { key = k; value = val; next = n; }
  Node() { key = ""; next = NULL; }
};

class Stringset {

 private: 
  Node **table;  // array of pointers to linked lists
  int size;      // size of table, as currently allocated
  int num_elems; // number of elements stored in the table

 public:
  Stringset();
  ~Stringset();
  int find(string key);
  void insert(string key, int value);
  void remove(string key);
  void print(void);
};

#endif
