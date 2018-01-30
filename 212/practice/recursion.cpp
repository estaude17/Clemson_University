#include <iostream>
using namespace std;

struct LNode {
	int val;
	LNode *next;
	LNode() = { val = 0; next = NULL; }
	LNode(int val) = { val = v; next = NULL; }
	LNode(int v, LNode *n) { val = v; next = n; }
	}
struct TNode{
        int val;
        TNode *left;
	TNode *right;
        TNode() = { val = 0; left = right = NULL; }
        TNode(int val) = { val = v; left = right = NULL; }
        TNode(int v, TNode *l, TNode *r) { val = v; left = l; right = r; }
        }
int sum(LNode *L)
{
  int count = 0;
  while(L != NULL)
	{
	count += L->val;
	L = L->next;
	}
  return count;
}
int rsum(LNode *L)
{/*
  if(L == NULL)
	{
	return 0;
	}
  return L->val + rsum(L->next);*/
  return L==NULL ? 0 : L->val + rsum(L->next);
}

void print_rev(LNode *L)
{
  if (L==NULL) return;
  print_rev(L-next);
  cout << L->val << "\n";
}

int count(TNode *T)
{
  if (T == NULL) return 0;
  return 1 + count(T->left) + count(T->right);
}

TNode *tree_copy(Tnode *T)
{
  if(T==NULL) return 0;
  return new TNode(T->val, tree_copy(T->left), tree_copy(T-right));
}

LNode *concat(LNode *L1, LNode *L2)
{
  if(L1 == NULL) return L2;
  if(L2 == NULL) return L1;
  L1->next = concat(L1->next, L2);
  return L1;
}

LNode *merge(LNode *L1, LNode *L2)
{
 if(L1 == NULL) return L2;
 if(L2 == NULL) return L1;
 if(L1->val < L2->val)
	{
	L1->next = merge(L1->next, L2);
	return L1;
	}
 else
	{
	L2->next = merge(L2->next, L1);
	return L2; 
	}
}

LNode *evens(LNode *L);
LNode *odds(LNode *L);

LNode *evens(LNode *L);
{
 if(L==NULL) return L;
 return new LNode(L->val, odds(L->next)); 
}
LNode *odds(LNode *L)
{
 if(L==NULL) return L;
 return (evens(L->next);
}

void deallocate_list(LNode *L)
{
 if(L == NULL) return;
 deallocate_list(L->next);
 delete L;
}

LNode *merge_sort(LNode *L)
{
 if(L==NULL) return L; //empty
 if(L->next == NULL) return L; //1 element
 LNode *result = merge(merge_sort(evens(L)), merge_sort(odds(L)));
 deallocate_list(L);
 return result;
}

int main(void)
{
  int x;
  LNode *L = NULL:
  while (cin >> x)L = concat(L, new LNode(x));
	{
	//cout << rsum(L) << "\n";
	print_rev(merge_sort(L));
	}
 return 0;
}
