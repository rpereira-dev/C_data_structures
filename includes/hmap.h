/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain 1973
*/

#ifndef HMAP_H
# define HMAP_H

# include "common.h"
# include "btree.h"

/**
 *	Generic hash map implementation in C89:
 *
 *	ABOUT THE IMPLEMENTATION:
 *		- given pointer address are saved for values. No copy their data are done. (same for keys)
 *		- const where used where on constant data (well...), so you dont mess up the hash map :)
 *
 * 
 *	example for a string hashmap:
 *
 *		t_hmap map = hmap_new(1024, (t_hf)strhash, (t_cmpf)strcmp);
 *		hmap_insert(&map, strdup("hello world"), strdup("ima key"), strlen("Hello world") + 1);
 *		char *helloworld = hmap_get(&map, "ima key"); //now contains "Hello world"
*/

typedef struct	s_hmap_node
{
	unsigned long int const hash; //hash of the key
	void const *data; //the data holds
	void const *key; //the key used	
}				t_hmap_node;

typedef struct	s_hmap
{
	t_btree	*_values; //a buffer of btrees which will holds every values (to handle collision and to keep elements searching fast)
	unsigned long int const capacity; //number of btrees
	unsigned long int size; //number of value set
	t_hash_function const hashf; //hash function
	t_cmp_function const keycmpf; //key comparison function, where node keys are sent as parameters
}				t_hmap;

/**
 *	Create a new hashmap:
 *
 *	capacity : capacity of the hashmap (number of binary tree boxes in memory)
 *	hashf    : hash function to use on inserted elements
 *	cmpf     : comparison function to use when searching a data
*/
t_hmap hmap_new(unsigned long int const capacity, t_hash_function hashf, t_cmp_function keycmpf);

/**
 *	Delete the hashmap from the heap
 *
 *	hmap : hash map
 *	datafreef : function which will be called on node data before the node being freed.
 *				i.e :	'NULL' if data shouldnt be free, 'free' if the data was allocated with a malloc,
 *						'myfree' if this is structure which contains multiple allocated fields ...
 *	keyfreef : same for the node key
 */
void hmap_delete(t_hmap *hmap, t_function datafreef, t_function keyfreef);

/**
 *	Insert a value into the hashmap:
 *
 *	map  : hmap
 *	data : value to insert
 *	key  : key reference for this data
 *  size : size of the data (i.e, 'sizeof(t_data_structure)', 'strlen(str) + 1')
 *
 *	return the given data if it was inserted properly, NULL elseway
*/
void const *hmap_insert(t_hmap *hmap, void const *data, void const *key);

/**
 *	Get data from the hashmap
 *
 *	hmap : hash map
 *	key  : the node's key to find
 */
void *hmap_get(t_hmap *hmap, void const *key);

/**
 *	Some simple builtin hashes functions, useful for tests.
 *
 *	String hash is based on : http://www.cse.yorku.ca/~oz/hash.html
*/
unsigned long int strhash(char const *str);
unsigned long int inthash(int const value);


#endif
