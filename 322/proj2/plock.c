/*Elizabeth Stauder (estaude)
CPSC 3220 project 2 due June 19, 2017
*/
#include "plock.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

plock_t *plock_create(){
  /*calls malloc() to allocate space for an instance of the
plock_t data type, initializes the plock value to FREE, initializes
the mutex mlock using the appropriate pthread library call,
initializes the waiting list head pointer, and returns a
pointer to the instance.*/
  plock_t *datatype = (plock_t *) malloc(sizeof(plock_t));
  datatype->value = FREE;
  node_t *waitlist = (node_t *) malloc(sizeof(node_t));
  pthread_mutex_init(&datatype->mlock, NULL);
  datatype->head = waitlist;
  //datatype->head = NULL;
  return datatype;  
}

void plock_destroy(plock_t *lock){
  /*first garbage collects any nodes remaining on the waiting list by
destroying the condition variables using the appropriate pthread library
call and freeing the nodes. 
It then destroys the mutex mlock using the 
appropriate pthread library call and finally frees the plock data
structure itself.*/
  //create 2 nodes, one in front of the dummy head and the other in front of the 1st 
  node_t *searchnode = lock->head->next;
  node_t *searchnode2 = searchnode->next;
  lock->head->next = NULL;
  //make while loop with nodes traversing list
  while(searchnode2->next != NULL){
	pthread_cond_destroy(&searchnode->waitCV);
  	pthread_cond_destroy(&searchnode2->waitCV);
	//set searchnode to NULL
 	//searchnode=NULL;
	searchnode->next= NULL;
	free(searchnode);
	//set searchnode1 so it is now in front of searchnode2
	searchnode=searchnode2->next;
	//searchnode2=NULL;
	searchnode2->next=NULL;
	free(searchnode2);
 	//put searchnode2 in front of searchnode1 again
	searchnode2=searchnode->next;
 	}
  //destroys both nodes' condition variables
  pthread_cond_destroy(&searchnode->waitCV);
  pthread_cond_destroy(&searchnode2->waitCV);
  //frees nodes, including dummy head
  searchnode->next =NULL;
  searchnode2->next = NULL;
  free(searchnode);
  free(searchnode2);
  lock->head->next = NULL;
  free(lock->head);
  //destroy mlock and free lock
  pthread_mutex_destroy(&lock->mlock);
  free(lock);
 // }  
}
/*You don't have to have a helper function, but a possible one is a function 
to allocate a node, initialize the CV in the node, and add the node to the priority wait list. 
The caller can then wait on the CV in its node within the wait loop.
operates similar to destroy wrt traveling down waitlist
*/
void list_adder(plock_t *lock, node_t *node1){
  //pthread_cond_init(&node1->waitCV, NULL);
  //if no nodes exist in waiting list, node1 just gets added
  if(lock->head->next == NULL) lock->head->next = node1;
  else if(lock->head->next != NULL){
	node_t *firstnode = lock->head;
	node_t *secondnode = firstnode->next;
	while(secondnode->next !=NULL && secondnode->priority >= node1->priority){
		//shifts down list until the end of list is reached or there is a spot for node1
		firstnode = secondnode;
		secondnode = secondnode->next;
	}
 	//if end of line is reached or there is a spot for node1
	if(secondnode->next == NULL || node1->priority > secondnode->priority){
		//this condition is for end of list
		if(secondnode->next == NULL && node1->priority <= secondnode->priority){
			secondnode->next = node1;
			//at new end of waiting list, the spot at right of node1 is new NULL area
			//printf("HELLO\n");
			node1->next = NULL;
		}
		//this condition is for placing node1 within the list in order of priority
		else if(secondnode->priority < node1->priority){
			firstnode->next = node1;
			//printf("HELLO!!!\n");
			//node1 goes between first and second nodes.
			node1->next = secondnode;		
	//		}
		}
	//pthread_cond_wait(&node1->waitCV, &lock->mlock);		
	}
   //pthread_cond_wait(&node1->waitCV, &lock->mlock);
  }
  //pthread_cond_wait(&node1->waitCV, &lock->mlock);

}
void plock_enter(plock_t *lock, int priority){
  /*This function checks the state variables of the plock data structure 
to determine if the calling thread can proceed or instead must be added to
a waiting list. 
If the thread must be added, a node instance is created
and the condition variable within the node must be initialized using the
appropriate pthread library call. 
(The creation and addition could be structured as a private helper function 
if you wish. Helper functions should be contained in the plock.c source file.) 
The thread can then wait on the condition variable in the node.*/
  pthread_mutex_lock(&lock->mlock);
	if(lock->value == FREE) lock->value = BUSY;

	else if(lock->value == BUSY){//add to waitlist
		node_t *node1 = (node_t *) malloc(sizeof(node_t));
		node1->priority = priority; //is this what is meant to be done w/this?
		node1->next = NULL;
		pthread_cond_init(&node1->waitCV, NULL);
		//printf("%p, %p\n",&lock, &node1);
		list_adder(lock, node1);//helper function to add to waitlist
		while(!(lock->value)) pthread_cond_wait(&node1->waitCV, &lock->mlock);		
	}
  pthread_mutex_unlock(&lock->mlock);
}

void plock_exit(plock_t *lock){
  /*This function checks the state variables of the plock data structure to
determine what update action to take. 
For example, it may need to signal a waiting thread using the appropriate 
pthread library call.*/
  pthread_mutex_lock(&lock->mlock);
  //lock->value = FREE;
  if(lock->value == BUSY && lock->head->next == NULL) lock->value = FREE;
  //if(lock->head->next != NULL){
  else{
	lock->value=FREE;
	node_t *newnode = lock->head->next;
	//lock->head->next = newnode->next;
	pthread_cond_signal(&newnode->waitCV);
	pthread_cond_destroy(&newnode->waitCV);
	lock->head->next = newnode->next;
	newnode->next=NULL;
	free(newnode);
 	//free(lock);
	}
  pthread_mutex_unlock(&lock->mlock);
}
