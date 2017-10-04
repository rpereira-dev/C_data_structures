/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#include "graph.h"

/**
 *	Create a new graph on the heap
 *	elem_size : size of a node
 *
 *	e.g: t_graph = graph_new(sizeof(int));
 */
t_graph * graph_new(unsigned int node_size) {
	t_graph * graph = (t_graph *)malloc(sizeof(t_graph));
	if (graph == NULL) {
		return (NULL);
	}
	graph->nodes = array_list_new(1, node_size);
	graph->edges = array_list_new(1, node_size * 2);
	return (graph);
}

/**
 *	Add a node to the graph
 *	node: the node
 *
 *	return : the total number of nodes
 */
unsigned int graph_add_node(t_graph * graph, void * node) {
	return (array_list_add(graph->nodes, node));
}

/**
 *	Add a edge to the graph
 *	node1: first node
 *	node2 : second node
 *
 *	return : the edge
 */
unsigned int graph_add_edge(t_graph * graph, void * node1, void * node2) {
	array_list_add(graph->edges, node1);
	array_list_add(graph->edges, node2);
	return (graph->edges->size / 2);
}

/**
 *	remove a node from the graph (and so the linked edges)
 *	node : the node to compare
 *	cmpf: the comparison function (cf 'strcmp()'), return every matched elements
 *
 *	return : the number of nodes
 */
unsigned int graph_remove_nodes(t_graph * graph, void * node, t_cmpf cmpf) {
	ARRAY_LIST_ITER_START(graph->nodes, void *, other, index) {
		if (cmpf(node, other) == 0) {
			array_list_remove(graph->nodes, index);
			continue ; //continue without incrementing 'index'
		}
	}
	ARRAY_LIST_ITER_END(graph->nodes, void *, other, index);
	return (graph->nodes->size);
}

/**
 *	remove a node from the graph (and so the linked edges)
 *	node : the node to compare
 *	cmpf: the comparison function (cf 'strcmp()'), return first matched element
 *
 *	return : the number of nodes
 */
unsigned int graph_remove_node(t_graph * graph, void * node, t_cmpf cmpf) {
	ARRAY_LIST_ITER_START(graph->nodes, void *, other, index) {
		if (cmpf(node, other) == 0) {
			array_list_remove(graph->nodes, index);
			return (graph->nodes->size);
		}
	}
	ARRAY_LIST_ITER_END(graph->nodes, void *, other, index);
	return (graph->nodes->size);
}

/**
 *	Delete the given graph from the heap
 */
void graph_delete(t_graph * graph) {
	array_list_delete(graph->nodes);
	array_list_delete(graph->edges);
	free(graph);
}

int main() {
	t_graph * graph = graph_new(sizeof(int));
	int a = 1;
	int b = 1;
	graph_add_node(graph, &a);
	graph_add_node(graph, &b);

	graph_add_edge(graph, &a, &b);
	return (0);
}
