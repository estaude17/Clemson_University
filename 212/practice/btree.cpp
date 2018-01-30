

struct Node{
  int key;
  Node *next;
  Node (int k) { key = k; next = NULL;}
  Node () { key = 0; next = NULL;}
};

Node *head = NULL;

Node *insert(Node *head, int key)
{
  if(head == NULL) return new Node(k);
  head->next = insert(head->next, k);
  return head;
}

Node *find(Node *T, int k)
{
  if (T == NULL) return NULL;
  if (k == T->key) return T;
  if (k < T->key) return find(T->left, k);
  else return find(T->right, k);
}

int main (void)
{
  while(1 > 0){
	count++;
  	head = insert(head, 17);
	cout << count << "\n";
	}
  return 0;
}
