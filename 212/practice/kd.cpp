#include <iostream>

int D;
struct Node{
	//int index; //these two are other ways to make key[11]
	//Point *p;
	int key[11];//11 dimensional array
	Node *left; *right;
	Node(int *k) { key = k; left = right = NULL; }
	Node() { key = 0; left = right = NULL; }
};

Node *insert(Node *T, int *val, int d)
{
  if(T == NULL) return Node(val);
  if(val[d] < T->key[d]) T->left = insert(T->left, val, (d+1)%D);
  else T->right = insert(T->right, val, (d+1)%D);
  return T;
}

int main()
{
  //randomize input
  for(int i = 0; i < N; i++)
	T = insert(T, A[i], 0);
}
