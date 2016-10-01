/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#include "btree.h"

/**
 *  create a new binary tree
 */
t_btree * btree_new(t_cmp_function cmpf) {
    t_btree * btree = (t_btree *)malloc(sizeof(t_btree));
    if (btree == NULL) {
        return (NULL);
    }

    btree->head = NULL;
    btree->size = 0;
    btree->cmpf = cmpf;
    btree->values = array_list_new(16, sizeof(void *));
    return (btree);
}

/** internal function to create a new node */
static t_btree_node *_btree_new_node(void * value) {
    t_btree_node *node = (t_btree_node*)malloc(sizeof(t_btree_node));

    if (node == NULL) {
        return (NULL);
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

/** internal function : swip the head to the left */
static void btree_node_swip_left(t_btree_node ** node) {
    t_btree_node *head = *node;
    t_btree_node *right = head->right;

    if (right == NULL) {
        return ;
    }

    t_btree_node *tmp = right;
    while (tmp->left != NULL) {
        tmp = tmp->left;
    }

    tmp->left = head;
    tmp->left->right = NULL;

    *node = right;
}

/** internal function : swip the head to the right */
static void btree_node_swip_right(t_btree_node ** node)
{
    t_btree_node *head = *node;
    t_btree_node *left = head->left;

    if (left == NULL) {
        return ;
    }

    t_btree_node *tmp = left;
    while (tmp->right != NULL) {
        tmp = tmp->right;
    }

    tmp->right = head;
    tmp->right->left = NULL;

    *node = left;
}

static int _btree_insert(t_cmp_function cmpf, t_btree_node ** parent, t_btree_node ** node, void * value) {
    if (*node == NULL) {
        *node = _btree_new_node(value);
        if (*node == NULL) {
            return (0);
        }
        if (parent != NULL) {
            if ((*parent)->left == NULL) {
                btree_node_swip_left(parent);
            } else if ((*parent)->right == NULL) {
                btree_node_swip_right(parent);
            }
        }
        return (1);
    }

    if (cmpf((*node)->value, value) < 0) {
        return (_btree_insert(cmpf, node, &((*node)->right), value));
    }
    return (_btree_insert(cmpf, node, &((*node)->left), value));
}

/**
 *  insert a value into the btree
 */
void * btree_insert(t_btree * tree, void * value) {
    if (_btree_insert(tree->cmpf, NULL, &(tree->head), value)) {
        array_list_add(tree->values, &(value));
        tree->size++;
        return (value);
    }
    return (NULL);
}

/** intern function to remove a node and it childs */
static void _btree_delete_node(t_btree_node ** node) {
    if (*node == NULL) {
        return ;
    }
    _btree_delete_node(&((*node)->left));
    _btree_delete_node(&((*node)->right));
    free(*node);
    *node = NULL;
}

/**
 *  delete the btree from the heap
 */
void btree_delete(t_btree * btree) {
    _btree_delete_node(&(btree->head));
    array_list_delete(btree->values);
    btree->size = 0;
    btree->cmpf = 0;
}

/** internal function to apply a function infix */
static void _btree_apply_infix(t_btree_node * node, t_function f) {
    if (node->left != NULL) {
        _btree_apply_infix(node->left, f);
    }
    f(node->value);
    if (node->right != NULL) {
        _btree_apply_infix(node->right, f);
    }
}

/**
 *  call the function f to every value in the btree
 *  (from left to head to right) (sort order)
 */
void btree_apply_infix(t_btree * btree, t_function f) {
    _btree_apply_infix(btree->head, f);
}

/** internal function to apply a function suffix */
static void _btree_apply_suffix(t_btree_node * node, t_function f)
{
    if (node->left != NULL) {
        _btree_apply_suffix(node->left, f);
    }
    if (node->right != NULL) {
        _btree_apply_suffix(node->right, f);
    }
    f(node->value);
}

/**
 *  call the function f to every value in the btree
 *  (from (head to right) to (head to left))
 */
void btree_apply_suffix(t_btree * btree, t_function f) {
    _btree_apply_suffix(btree->head, f);
}

/** internal function to apply a function prefix */
static void _btree_apply_prefix(t_btree_node * node, t_function f) {
    f(node->value);
    if (node->left != NULL) {
        _btree_apply_prefix(node->left, f);
    }
    if (node->right != NULL) {
        _btree_apply_prefix(node->right, f);
    }
}

/**
 *  call the function f to every value in the btree
 *  (from (head to left) to (head to right))
 */
void btree_apply_prefix(t_btree * btree, t_function f) {
    _btree_apply_prefix(btree->head, f);
}

static t_btree_node *_btree_search(t_btree_node * node, void * valueref, t_cmp_function cmpf)    {
    if (node == NULL) {
        return (NULL);
    }

    int r = cmpf(node->value, valueref);
    if (r == 0) {
        return (node);
    }

    if (r > 0) {
        return (_btree_search(node->left, valueref, cmpf));
    }

    return (_btree_search(node->right, valueref, cmpf));
}

/**
 *  return  the item which match with the cmpf return value,
 *          when comparing the node value and the given value reference
 *          if the cmpf is NULL, the btree one is use
 *          return NULL if the value isnt found
 */
void * btree_get(t_btree * btree, void * valueref, t_cmp_function cmpf) {
    t_btree_node * node = _btree_search(btree->head, valueref, cmpf);
    return (node == NULL ? NULL : node->value);
}

/**
 *	remove the given node from the btree
 */
void * btree_remove_node(t_btree * tree, t_btree_node *node)
{
    if (node == NULL) {
        return (NULL);
    }

    if (node->left == NULL) {
        tree->head = node->right;   
    }
    else if (node->right == NULL) {
        tree->head = node->left;
    } else {
        t_btree_node *tmp = node->left;
        while (tmp->right != NULL) {
            tmp = tmp->right;
        }
        tmp->right = node->right;
        tree->head = tmp;
    }

    void * value = node->value;
    free(node);
    tree->size--;
    return (value);
}

/**
 *  remove the node if the test with node's value and given value return 0
 */
void * btree_remove_if(t_btree * tree, void * valueref, t_cmp_function cmpf) {
    t_btree_node *node = _btree_search(tree->head, valueref, cmpf);
	return (btree_remove_node(tree, node));
}

/**
 *  remove the node which contains the given value, and return it value address
 */
void * btree_remove(t_btree * tree, void * valueref) {
    return (btree_remove_if(tree, valueref, tree->cmpf));
}

/*
int main() {
	t_btree * btree = btree_new((t_cmpf)strcmp);
	
	btree_insert(btree, strdup("8")); 
	btree_insert(btree, strdup("E")); 

	BTREE_ITER_START(btree, char *, str) {
		printf("%s\n", str);
	}
	BTREE_ITER_END(&btree, char *, str)

    btree_delete(btree);

	return (0);
}
*/
