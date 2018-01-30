/*
Elizabeth Stauder(estaude)
CPSC 2120-001
October 2, 2015
bad3.cpp
By using the insert_random function, this file creates an input N 
that causes the prog3.cpp to run much more slowly.
*/
#include <iostream>
#include <cstdlib>
using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = NULL; }
};

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}
  
// prints out the inorder traversal of T (i.e., the contents of T in 
//sorted order)
void print_inorder(Node *T)
{
  if (T == NULL) return;
  print_inorder(T->left);
  cout << T->key << "\n";
  print_inorder(T->right);
}
// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R)
{
  int Rank;
  if(T == NULL)
        {
        *L = NULL;
        *R = NULL;
        return;
        }
  if(T->left == NULL)
        {
        Rank = 0;
        }
  else
        {
        Rank = T->left->size;
        }
  if(r <= Rank)
        {split(T->left, r, L, &T->left);
        *R = T;
        }
  else
        {
        split(T->right, (r - Rank - 1), &T->right, R);
        //r-Rank-1 because right side of tree ranks separate from rest of tree.
        *L = T;

        }
  return fix_size(T);
}

// insert value v at rank r
Node *insert_random(Node *T, int v, int r)
{
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert_random k recursively left or right of the root of T
  if (T == NULL) return new Node(v);
  if (rand() % (T->size + 1) == 0) {
    // insert at root
    Node *new_root = new Node(v);
    split(T, r, &new_root->left, &new_root->right);
    fix_size(new_root);
    return new_root;
  }
  // otherwise insert recursively...
  int Rank;
  if (T->left == NULL)
        {
        Rank = 0;
        }
  else {
        Rank = T->left->size;
        }
  if(r <= Rank )
        {
        T->left = insert_random(T->left, v, r);
        fix_size(T);
        return T;
        }
  else{
        T->right = insert_random(T->right, v, (r - Rank - 1));
        //r-Rank-1 because right side of tree ranks separate from rest of tree.
        fix_size(T);
        return T;
        }
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    cout << "Usage: bad1 <input size>\n";
    return 0;
  }

  int N = atoi(argv[1]);  // get first command-line argument
  if (N<1 || N>100000) {
    cout << "Invalid input size!\n";
    return 0;
  }
  
  // Generate and print bad input of size N for prog3
  //create binary search tree
  Node *X = NULL;
  //insert N elements into tree
  for(int i = 0; i < N; i++)
	{
	X =insert_random(X, i, (123456789 % (i+1)));
	}
  cout << N  << "\n";
  //print out bst content
  print_inorder(X);
  return 0;
}
