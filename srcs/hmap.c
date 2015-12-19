/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#include "hmap.h"

/**
 *	Create a new hashmap:
 *
 *	capacity : capacity of the hashmap (number of binary tree boxes in memory)
 *	hashf    : hash function to use on inserted elements
 *	keycmpf  : comparison function to use when searching a data
 */
t_hmap hmap_new(unsigned long int capacity, t_hash_function hashf, t_cmp_function keycmpf)
{
    // set the hmap capacity to the closest power of two
    unsigned long int c = 1;
    while (c < capacity)
    {
        c = c << 1;
    }

	unsigned long int size = sizeof(t_btree) * c;
    void *values = malloc(size);
	memset(values, 0, size);
	
	t_hmap hmap = {values, c, 0, hashf, keycmpf};

    return (hmap);
}

/**
 *	Delete the hashmap from the heap
 *
 *	hmap	:	hash map
 *	freef	:	function which will be called on node data and node key on node being freed.
				i.e :	'NULL' if data shouldnt be free, 'free' if the data was allocated with a malloc,
						'myfree' if this is structure which contains multiple allocated fields
 */
void hmap_delete(t_hmap *hmap, t_function datafreef, t_function keyfreef)
{
	unsigned long int i = 0;
	while (i < hmap->capacity)
	{
		t_btree *btree = hmap->_values + i;
		if (btree->size)
		{
			ARRAY_LIST_ITER_START(btree->values, t_hmap_node *, node, j)
			{
				if (datafreef)
				{
					datafreef(node->data);
				}
				
				if (keyfreef)
				{
					keyfreef(node->key);
				}
				
				free(node);
			}
			ARRAY_LIST_ITER_END(btree->values, t_hmap_node *, node, j)

			btree_delete(btree);
		}
		++i;
	}
}

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
void const *hmap_insert(t_hmap *hmap, void const *data, void const *key)
{
	unsigned long int hash = hmap->hashf(key); //get the hash for this key
	unsigned long int addr = hash & hmap->capacity; //get the binary tree from the hash
	
	t_hmap_node *nodeaddr = (t_hmap_node*)malloc(sizeof(t_hmap_node)); //create a new node
	if (nodeaddr == NULL) //if allocation failed, return NULL
	{
		return (NULL);
	}

	t_hmap_node node = {hash, data, key}; //set the node data
	memcpy(nodeaddr, &node, sizeof(t_hmap_node));
	
	t_btree *btree = hmap->_values + addr; //get the binary tree from it address
	if (btree->values.data == NULL) //if the btree hasnt already been initialized
	{
		printf("New btree was set: %p\n", btree);
		*btree = btree_new(NULL); //initialize it
	}

	//TODO : insert the node to the btree

	hmap->size++;
	return (data); //return the data
}

/**
 *	Get data from the hashmap
 *
 *	hmap : hash map
 *	key  : the node's key to find
 */
void *hmap_get(t_hmap *hmap, void const *key)
{
	unsigned long int hash = hmap->hashf(key);
	unsigned long int addr = hash & hmap->capacity;
	
	t_btree *btree = hmap->_values + addr;
	if (btree->size == 0)
	{
		return (0);
	}
	if (btree->size == 1)
	{
		return (btree->head->value);
	}
	
	//TODO : here are collision, get the data from the tree which match exactly with the key
		
		
	return (NULL);
}

/**
 *	default string hash function
 */
unsigned long int strhash(char const *str)
{
    if (str == NULL)
    {
        return (0);
    }
    unsigned long int hash = 5381;
    int c;
    while ((c = *str) != '\0')
    {
        hash = ((hash << 5) + hash) + c;
        str++;
    }
    return (hash);
}

/**
 *	Default hash for an integer
 */
unsigned long int inthash(int const value)
{
	return (value);
}

int main()
{
    t_hmap hmap = hmap_new(1024, (t_hf)strhash, (t_cmpf)strcmp);
	hmap_insert(&hmap, strdup("Hello world"), strdup("ima key"));
	
	char *str = hmap_get(&hmap, strdup("ima key"));
	printf("size : %lu : %s\n", hmap.size, str);
	
	hmap_delete(&hmap, free, free);
	return (0);
}
