#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "common.h"

typedef struct  s_list_node
{
    unsigned int        content_size;
    struct s_list_node  *next;
    struct s_list_node  *prev;
}               t_list_node;

typedef struct  s_list
{
    t_list_node *head;
    long unsigned int size;
}               t_list;

/**
 * Create a new linked list
*/
t_list  list_new(void);

/**
 *  Add an element at the end of the list
*/
void    *list_push(t_list *lst, void const *content, unsigned int content_size);

/**
 * Add an element in head of the list
*/
void    *list_add(t_list *lst, void const *content, unsigned int content_size);

/**
 *  Return the list node data which match with the given comparison function
 *  and reference data. (cmpf should acts like 'strcmp()')
*/
void    *list_get(t_list *lst, t_cmp_function cmpf, void *cmpd);

/**
 * Remove the node which datas match with the given comparison function
 * and the given data reference
*/
int     list_remove(t_list *lst, t_cmp_function cmpf, void *cmpref);

/**
 * Remove first / last element of the list. Return 1 if it was removed, 0 else
*/
int     list_remove_first(t_list *lst);
int     list_remove_last(t_list *lst);

/**
 * Remove the first element of the list, and return it data
*/
void    *list_pop(t_list *lst);

/**
 *  Return the first element of the list
*/
void    *list_head(t_list *lst);

/**
 * Clear the list (remove every node)
*/
void    list_clear(t_list *lst);

/**
 *  write the list to a file descriptor
 */
int     list_to_fd(t_list *list, int fd);

/**
 *  read and return a list from the given file descriptor
*/
t_list  list_from_fd(int fd);


/** iterate on the list using a macro (optimized) */
#define LIST_ITER_START(L, T, V) \
{\
    t_list_node *node;\
    T V;\
    \
    node = L.head->next;\
    while (node != L.head)\
    {\
        V = (T)(node + 1);
#define LIST_ITER_END() \
        node = node->next; \
    }\
}

#endif
