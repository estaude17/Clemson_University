/*
Elizabeth Stauder (estaude)
CPSC 2121
September 15, 2015
The  goal of this lab is to gain familiarity with binary search trees.
You will code a number of primitive operations on a BST, 
ultimately building the code base for a randomly-balanced BST.
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = NULL; }
};

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if(T == NULL)
	{
	return new Node(k);
	}
  else if(k < T->key)
	{
    	T->left = insert(T->left, k);
  	}
  else
  	{
      	T->right = insert(T->right, k);
  	}

  T->size++;
  return T;

}

// prints out the inorder traversal of T (i.e., the contents of T in sorted order)
void print_inorder(Node *T)
{
  if(T != NULL)
	{
  	print_inorder(T->left);
  	cout << T->key << "" << endl;
  	print_inorder(T->right);
  	return;
	}
}

// return a pointer to the node with key k in tree T, or NULL if it doesn't exist
Node *find(Node *T, int k)
{
  if(T == NULL)
	{
	return NULL;
	}
  if(k == T->key)
	{
	return T;
	}
  else if(k < T->key)
	{
    	return find (T->left, k);
  	}
  else
  	{
      	return find (T->right, k);
  	}
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T != NULL && r >= 0 && r < T->size);

  int x;
  if (T->left == NULL)
	{
	x = 0;
	}
  else
	{
	x = T->left->size; // x is rank of root.
	}

  if (r == x)
	{
	return T;
	}
  else if (r < x)
	{
	return select(T->left, r);
	}
  else
	{
	return select(T->right, (r - x - 1));
	}

}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
  if (L == NULL)
	{
	return R;
	}
  if (R == NULL)
	{
	return L;
	}

  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)

  int r = rand() % (L->size + R->size);
  if (r < (L->size))
	{
	L->right = join(L->right, R);
	return L;
	}
  else
	{
	R->left = join(L, R->left);
	return R;
	}
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  assert (find(T,k) != NULL);
  if(k == T->key)
	{
	Node *temp = join(T->left, T->right);
	delete T;
	return temp;
	}
  if(k < T->key)
	{
    	T->left = remove(T->left, k);
  	}
  else
  	{
      	T->right = remove(T->right, k);
  	}
  return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
  //assert (find(T,k) != NULL);
  if(T == NULL)
	{
	*L = NULL;
	*R = NULL;
	return;	
	}
  if(T->key >= k)
	{
	split(T->right, k, &T->right, R);
	*L = T;
	return;
	}
  else
	{
	split(T->left, k, L, &T->left);
	*R = T;
	return;
	}
}
// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert_random k recursively left or right of the root of T

  if(T == NULL) 
	{
	return new Node(k); 
	}
  if(rand() % (T->size + 1) == 0 )
	{ 
	Node *newN = new Node(k);
	split(T, k, &newN->left, &newN->right);
	return newN;
	} 
  if(T->key > k )
	{ 
        T->left = insert_random(T->left,k);
	} 
  else{
        T->right = insert_random(T->right,k);
	} 
  return T;
}

int main(void)
{
  int A[10];
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  
  // insert contents of A into a BST
  Node *T = NULL;
  for (int i=0; i<10; i++) T = insert(T, A[i]);
  
  // print contents of BST (should be 0..9 in sorted order)
  print_inorder(T);

  // test select
  for (int i=0; i<10; i++) {
    Node *result = select(T, i);
    if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  for (int i=0; i<11; i++) 
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  print_inorder(L);
  cout << "Contents of right tree after split (should be 5..9):\n";
  print_inorder(R);
    
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  print_inorder(T);
  
  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    print_inorder(T);
  }
  
  // test insert_random
  cout << "Inserting 10 million elements in order; this should be very fast if insert_balance is working...\n";
  for (int i=0; i<10000000; i++) T = insert_random(T, i);
  cout << "Done\n";
  
  return 0;
}
