/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#ifndef BTREE_H
# define BTREE_H

# include "common.h"
# include "array_list.h"

typedef struct  s_btree_node {
    void                * value;
    struct s_btree_node * left;
    struct s_btree_node * right;
}               t_btree_node;

typedef struct  s_btree {
    t_array_list        * values;
    t_btree_node        * head;
    t_cmp_function      cmpf;
    unsigned long int   size;
}               t_btree;

/**
 *  create a new binary tree
 */
t_btree * btree_new(t_cmp_function cmpf);

/**
 *  delete the btree from the heap
 */
void btree_delete(t_btree * btree);

/**
 *  insert a value into the btree
 */
void * btree_insert(t_btree * tree, void * data);

/**
 *  return  the item which match with the cmpf return value,
 *          when comparing the node value and the given value reference
 *          if the cmpf is NULL, the btree one is use
 *          return NULL if the value isnt found
 */
void * btree_get(t_btree * btree, void * dataref, t_cmp_function cmpf); 

/**
 *  remove the node if the test with node's value and given value return 0
 */
void * btree_remove_if(t_btree * tree, void * valueref, t_cmp_function cmpf);

/**
 *  remove the node which contains the given value, and return it value address
 */
void * btree_remove(t_btree * tree, void * valueref);

/**
 *	remove the given node from the btree
 */
void * btree_remove_node(t_btree * tree, t_btree_node * node);

/**
 *	Apply the function to every bin tree data, in the prefix, infix, or suffix order
 */
void btree_apply_prefix(t_btree * btree, t_function iterf);
void btree_apply_infix(t_btree * btree, t_function iterf);
void btree_apply_suffix(t_btree * btree, t_function iterf);

/**
 *	Iterate on the binary tree. Item are set in insertion order (not in sorted order)
 */

# define BTREE_ITER_START(B, T, V)\
{\
    ARRAY_LIST_ITER_START((B)->values, T, V, __btree_iterator) {
# define BTREE_ITER_END(B, T, V)		}\
    ARRAY_LIST_ITER_END((B)->values, T, V, __btree_iterator)\
}

#endif
