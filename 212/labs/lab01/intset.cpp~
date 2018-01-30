/*
Elizabeth Stauder (estaude) CPSC 2121
August 25, 2015.
This program converted original code for arrays into linked list coding,
and inserted, located, removed, and printed a list of numbers.
*/
#include <iostream>
#include <assert.h>
#include "intset.h"

using namespace std;

Intset::Intset()
{
  first = NULL;
}

Intset::~Intset()
{
  Node *temp;
  while (first->next != NULL){
	temp = first->next;
	delete first;
	first = temp;
	}
}

/* Return true if key is in the set */
bool Intset::find(int key)
{
 Node *current = first;
 while(current != NULL){
   	if(current->value == key){
		return true;
  	}
	if(current->value > key){
		return false;
  	}
   	current = current->next;
 }
 return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Intset::insert(int key)
{
  
  if (first == NULL){
  	Node *newNode = new Node;
  	newNode->value = key;
  	newNode->next = NULL;
	first = newNode;
  	return;
  	}
  if(first->value > key){
	Node *newNode = new Node;
  	newNode->value = key;
  	newNode->next = first;
  	first = newNode;
  	return;
	}
  if(first->value == key){
	return;
	}
  Node* current = first;
  while (current->next != NULL){
	if(current->next->value > key){
		Node *newNode = new Node;
  		newNode->value = key;
  		newNode->next = current->next;
  		current->next = newNode;
  		return;
	}
	if(current->next->value == key){
		return;
		}
  current = current->next;
  }
  Node *newNode = new Node;
  newNode->value = key;
  newNode->next = NULL;
  current->next = newNode;
}

/* Removes a key.  It is an error if key isn't in the set */
void Intset::remove(int key)
{  
  Node* current = first;
  if(first == NULL)
	{
	return;
	}
  if(first-> value > key)
	{
	return;
	}
  if(first->value == key)
	{
	first = current->next;
	return;
	}
  while (current != NULL){
	if(current->next->value > key)
		{
		return;
		}
	if(current->next->value == key)
		{
		Node *temp = current->next;
		current->next = current->next->next; 
		delete temp;
		return;
		}
	current = current->next;
	}
}
void Intset::print(void)
{
  Node* current = first;
  while (current != NULL){
	cout << current->value << " " << endl;
	current = current->next;
	}
  return;
}
