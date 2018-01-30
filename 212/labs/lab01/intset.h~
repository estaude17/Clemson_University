/*
Elizabeth Stauder (estaude) CPSC 2121
August 25, 2015.
This program converted original code for arrays into linked list coding,
and inserted, located, removed, and printed a list of numbers.
*/
#ifndef INTSET_H /* Prevent multiple inclusion... */
#define INTSET_H

struct Node
{
  int value;
  Node* next;  
};

class Intset {

 private:
 Node *first;

 public:
  Intset();
  ~Intset();
  bool find(int key);
  void insert(int key);
  void remove(int key);
  void print(void);
};

#endif

