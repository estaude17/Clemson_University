/*
Elizabeth Stauder (estaude)
CPSC 1021-004
04/02/15
This program creates lists and malloc's a new list header,
initializes it, and returns its address.
list.c
*/

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

link_t::link_t(void *newentity)
{
   next = NULL;
   entity = newentity;
}

link_t::~link_t(void)
{
   fprintf(stderr, "in link destructor \n");
}

void link_t::set_next(link_t *new_next)
{
   next = new_next;
}

link_t * link_t::get_next()
{
   return(next);
}

void * link_t::get_entity()
{
   return(entity);
}


list_t::list_t()
{
   first = NULL;
   current = NULL;
   last = NULL;
}


void list_t::add(void *entity)
{
   link_t *link;
   link = new link_t(entity);
   // Create a new link passing it the entity pointer
   if(first == NULL){
        first = link;
        }
   else{
        last->set_next(link);
        }
   last = link;
   current = link;
/* Now add the link to the list using generally the */
/* same approach as the C version                   */
}

void list_t::reset(void)
{
   current = first;
}

int list_t::not_end(void)
{
   if (current == NULL){
        return 0;
        }
   else{
        return 1;
        }
}

void list_t::next_link(void)
{
   assert(current != NULL);
   current = current->get_next();

}

void *list_t::get_entity(void)
{
   assert(current != NULL);
   return (current->get_entity());
}

list_t::~list_t()
{
   link_t *kill;
   fprintf(stderr, "in list destructor \n");
   reset();
   while(not_end() == 1)
        {
                kill = current;
                next_link();
                delete kill;
        }
/* Delete each link_t in the list */
}

void list_t::insert(void *entity)
{
	link_t *link = new link_t(entity);

	if(first == NULL)
	{
		first = link;
		current = link;
		last = link;
	}	
	else if(current == first)
	{
		link->set_next(current);
		first = link;
		current = link;
	}
	else
	{
		link_t *traverse = first;
		while(traverse->get_next() != current)
		{
			traverse = traverse->get_next();
		}
		traverse->set_next(link);
		link->set_next(current);
		current = link;
	}
}

void list_t::remove(void)
{	
	if (first == NULL)
	{
	}
	else if(first == last)
	{
		delete current;
		first = NULL;
		last = NULL;
		current = NULL;
	}
	else if((current == first) && (current != last))
	{
		first = current->get_next();
		delete current;
		current = first;
	}
	else
	{
		link_t *traverse = first;
		
		while(traverse->get_next() != current)
		{
			traverse = traverse->get_next();
		}
		if(current == last)
		{
			last = traverse;
			delete(current);
			last->set_next(NULL);
			current = last;
		}		
		else 
		{
			traverse->set_next(current->get_next());
			delete current;
			current = traverse;
		}
	}
}
