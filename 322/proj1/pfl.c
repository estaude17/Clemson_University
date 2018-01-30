/*Elizabeth Stauder (estaude)
CPSC 3220, Project 2
Due Monday, June 5, 2017
*/
#include <stdio.h>
#include "pfl1.h"

struct region_node *get_free_node(){
  //searches thru node array for the 1st node w/node_state==free 
  //& returns address
  int i = 0;
  //struct region_node *node[NUM_NODES];
 
  for (i = 0; i < NUM_NODES; i++){
	if(node[i].node_state == FREE)
	{
		//printf("%p\n", &node[i]);//address of node
		return &node[i];
	}
  }
	//else return null ptr?
  return NULL;
}

void return_node( struct region_node * n ){
  int j = 0;
  //for(j = 0; j < NUM_NODES; j++){
  	n[j].node_state = IN_USE;
  	n[j].region_state = IN_USE;
  	n[j].start_address = NULL;
  	n[j].size =0;
  	n[j].prev = NULL;
	n[j].next = NULL;
//	}
}

unsigned char *alloc( int size ){
  if(size < 0 || size == 0){
 	//printf("hello!");
	return NULL;
 } //int k = 0;
  struct region_node *mynode = head;
  //struct region_node *node2;
  struct region_node *freenode;
  //for (k = 0; k < NUM_NODES; k++){
  while((mynode->region_state != FREE || mynode->size < size) && mynode->next != head){
	//search the mem. reg. list in order, looking for
	//a free mem. reg. that is >= than "size"
	mynode = mynode->next;
  }	
  if(mynode->region_state != FREE || mynode->size < size){
	return NULL;
  }
  if(mynode->size == size){
 	mynode->region_state = IN_USE;
  	return mynode->start_address;
  }
  if(mynode->size > size){
	freenode = get_free_node();
	if(freenode == NULL){
		mynode->region_state = IN_USE;
		return mynode->start_address;
 	}	
	freenode->start_address = mynode->start_address + size;	
  	freenode->size = mynode->size - size;
 	mynode->size = size;
	freenode->prev = mynode;
 	freenode->next = mynode->next;
	mynode->next->prev = freenode;
 	mynode->next = freenode;
	freenode->node_state=IN_USE;
	freenode->region_state=FREE;
    	mynode->region_state=IN_USE;
  	return mynode->start_address;  
  }
 }

int release( unsigned char *ptr ){
  int l = 0, result = 0;
  //unsigned char *pn, *nn, *rn;
  struct region_node *searchnode = head->next;
  if(ptr == NULL || ptr < &mem[0] || ptr > &mem[MEM_SIZE]) {
	return 2;
	}  
  //for(l = 0; l < NUM_NODES; l++){
  while(searchnode->start_address != ptr && searchnode->next != head){
	
	searchnode = searchnode->next;
  }
    
  //if(searchnode->start_address == ptr){

  	if(searchnode == head){
			result = 2;
		}
 	else if(searchnode->region_state == FREE){
//			printf("RC=1,%p\n", searchnode->start_address);
                        result= 1;
                }
  	else{ 
		result = 0;
		searchnode->region_state = FREE;
		if(searchnode->prev->region_state == FREE && searchnode->next->region_state == FREE){
			struct region_node *node2 = searchnode->next;
			searchnode->next = node2->next;
			node2->next->prev = searchnode;
			searchnode->size =node2->size + searchnode->size;
			return_node(node2);
			node2=searchnode->prev;
			searchnode->next->prev = node2;
			node2->next = searchnode->next;
			node2->size = node2->size + searchnode->size;
			return_node(searchnode);
			}
		else if(searchnode->prev->region_state == FREE && searchnode->next->region_state == IN_USE){
			struct region_node *node3 =searchnode->prev;
                        searchnode->next->prev = node3;
                        node3->next = searchnode->next;
                        node3->size = node3->size + searchnode->size;
                        return_node(searchnode);
			}
		else if(searchnode->prev->region_state == IN_USE && searchnode->next->region_state == FREE){
			struct region_node *node4= searchnode->next;
                        searchnode->next = node4->next;
                        node4->next->prev = searchnode;
                        searchnode->size =node4->size + searchnode->size;
			return_node(node4);
			}
		/*else if(searchnode->prev->region_state == IN_USE && searchnode->next->region_state == IN_USE){
			struct region_node *node5;
			
			return_node(node5);
			}*/
		}
//  }
  
  return result;
}
