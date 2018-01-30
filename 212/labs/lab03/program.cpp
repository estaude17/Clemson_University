/*
Elizabeth Stauder (estaude)
CPSC 2121-001, 09/08/15
This program uses "spatial hashing" to find the closest pair 
among 1 million points spread uniformly across a unit square 
in the 2D plane.  */
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct Node
{
  double x;
  double y;
  Node* next;  
};

Node ***allocate_table(int b)//dynamically allocating 2-D array
{
  Node ***table = new Node **[b];
  for (int i = 0; i < b; i++){
	table[i] = new Node *[b];	
  }
  for (int x = 0; x < b; x++){
	for (int y = 0; y < b; y++){
    		table[x][y] = NULL;
	}
  }
  return table;
}

void deallocate(Node ***table)//De-allocate array/linked lists
{
  for(int delx = 0; delx < 1000; delx++){
	for (int dely = 0; dely < 1000; dely++){
		while (table[delx][dely] != NULL){
			Node *current = table[delx][dely];
			table[delx][dely] = table[delx][dely]->next;
			delete current;
			}
	}
	delete [] table[delx];
  }
  delete [] table;
}


double distance(Node *n1, Node *n2) //measures distance between 2 points.
{
  return sqrt(((n1->x - n2->x) * (n1->x - n2->x)) + ((n1->y - n2->y) * (n1->y - n2->y)));
}

int main (void)//reads points.txt and prints out minimum distance.
{
  int b = 1000; //1000 * 1000 = 1 million.
  double minidist = (2 * b);
  double x, y;
  
  Node ***table = allocate_table(b);
  
  ifstream text;
  text.open ("points.txt");
  while(text >> x >> y){
	Node *Node2 = new Node;
	Node2->x = x;
	Node2->y = y;
	
	Node2->x *= b;
	Node2->y *= b;

	Node2->next = table[(int)Node2->x][(int)Node2->y];
	table[(int)Node2->x][(int)Node2->y] = Node2;
	}
  //Compare each pt. to the others in its cell and adjacent cells.
  for (int x = 0; x < b; x++){
	for (int y = 0; y < b; y++){
	Node *current = table[x][y];
		while(current != NULL){
			for (int w = (x-1); w <= (x+1); w++){
				if(w >= 0 && w < b)
			for (int z = (y-1); z <= (y+1); z++){
				if(z >= 0 && z < b){
					Node *c2 = table[w][z];
					while(c2 != NULL){
						if(distance(current, c2) < minidist
						&& distance(current, c2) != 0){
					     		minidist = 
							distance(current, c2);
							}
 						c2 = c2->next;
						}
					}
				}
			}
		current = current->next;
     		}
   	}
  }

  cout << "Minimum distance is "<< (minidist / b)<< endl;
  // dividing minidist by b returns everything to original scale.
  text.close();
  deallocate(table);
  return 0;
}
