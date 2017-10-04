/**
 *  This file is part of https://github.com/toss-dev/C_data_structures
 *
 *  It is under a GNU GENERAL PUBLIC LICENSE
 *
 *  This library is still in development, so please, if you find any issue, let me know about it on github.com
 *  PEREIRA Romain
 */

#ifndef GRAPH_H
# define GRAPH_H

# include "common.h"
# include "array_list.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct  s_graph {
	t_array_list	* nodes;
	t_array_list	* edges;
}               t_graph;



/**
 *	Create a new graph on the heap
 *	elem_size : size of a node
 *
 *	e.g: t_graph = graph_new(sizeof(int));
 */
t_graph * graph_new(unsigned int node_size);


/**
 *	Delete the given graph from the heap
 */
void graph_delete(t_graph * graph);

#endif
