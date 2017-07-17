/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "common.h"

typedef struct  s_list_node {
    struct s_list_node * next;
    struct s_list_node * prev;
}               t_list_node;

typedef struct  s_list {
    t_list_node         * head;
    unsigned long int   size;
}               t_list;

/** initialize the given list */
int list_init(t_list * list);

/**
 * Create a new linked list
 */
t_list * list_new(void);

/**
 *  Add an element at the end of the list
 */
void * list_add(t_list * lst, void const * content, unsigned int content_size);

/**
 * Add an element in head of the list
 */
void * list_addfront(t_list * lst, void const * content, unsigned int content_size);

/**
 *  Return the list node data which match with the given comparison function
 *  and reference data. (cmpf should acts like 'strcmp()')
 */
void * list_get(t_list * lst, t_cmp_function cmpf, void * cmpd);

/**
 * Remove the node which datas match with the given comparison function
 * and the given data reference
 */
int list_remove(t_list * lst, t_cmp_function cmpf, void * cmpref);

/**
 *	remove the given node from the list
 */
void list_remove_node(t_list * lst, t_list_node *node);

/**
 * Remove first / last element of the list. Return 1 if it was removed, 0 else
 */
int list_remove_first(t_list * lst);
int list_remove_last(t_list * lst);

/**
 * Remove the first element of the list, and return it data
 */
void * list_pop(t_list * lst);

/**
 *  Return the first element of the list
 */
void * list_head(t_list * lst);

/**
 * Clear the list (remove every node)
 */
void list_clear(t_list * lst);

/**
 *	remove the list for the heap
 */
void list_delete(t_list * lst);

/**
 *	iterate the function to every node content of the list
 */
void list_iterate(t_list * lst, t_function f);


/**
 * Return a buffer which holds pointers to every elements of the list, allocated with 'malloc()'
 */
void * list_buffer(t_list * lst);


/** iterate on the list using a macro (optimized) */
# define LIST_ITER_START(L, T, V)\
{\
	if (L != NULL && L->head != NULL) {\
    	t_list_node *__node = L->head->next;\
    	while (__node != L->head) {\
        	T V = (T)(__node + 1);
# define LIST_ITER_END(L, T, V) \
        	__node = __node->next; \
    	}\
    }\
}

//ABOVE FUNCTIONS ARENT IMPLEMENTED YET:

/**
 *  write the list to a file descriptor
 */
int     list_to_fd(t_list *list, int fd);

/**
 *  read and return a list from the given file descriptor
 */
t_list  list_from_fd(int fd);

#endif
