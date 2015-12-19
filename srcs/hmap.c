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
t_hmap hmap_new(unsigned long int const capacity,
				t_hash_function hashf, t_cmp_function keycmpf,
				t_function keyfreef, t_function datafreef)
{
    // set the hmap capacity to the closest power of two
    unsigned long int c = 1;
    while (c < capacity)
    {
        c = c << 1;
    }

	unsigned long int size = sizeof(t_array_list) * c;
    void *values = malloc(size);
	memset(values, 0, size);
	
	t_hmap hmap = {values, c, 0, hashf, keycmpf, datafreef, keyfreef};

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
void hmap_delete(t_hmap *hmap)
{
	unsigned long int i = 0;
	while (i < hmap->capacity)
	{
		t_array_list *array = hmap->values + i;
		if (array->data)
		{
			ARRAY_LIST_ITER_START(array, t_hmap_node *, node, j)
			{
				if (hmap->datafreef)
				{
					hmap->datafreef(node->data);
				}
				
				if (hmap->keyfreef)
				{
					hmap->keyfreef(node->key);
				}				
			}
			ARRAY_LIST_ITER_END(array, t_hmap_node *, node, j)

			array_list_delete(array);
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
	unsigned long int addr = hash & (hmap->capacity - 1); //get the array list from the hash

	t_hmap_node node = {hash, data, key}; //set the node buffer

	t_array_list *array = hmap->values + addr; //get the array list from it address
	if (array->data == NULL) //if the array list hasnt already been initialized
	{
		*array = array_list_new(4, sizeof(t_hmap_node)); //initialize it				
	}
	array_list_push(array, &node); //add the node to the list

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
	unsigned long int hash = hmap->hashf(key); //get the hash for this key
	unsigned long int addr = hash & (hmap->capacity - 1); //get the array list from the hash

	t_array_list *array = hmap->values + addr; //array of collision for this key hash
	
	if (array->size == 0)
	{
		return (NULL);
	}
	
	ARRAY_LIST_ITER_START(array, t_hmap_node *, node, i) //so compare the exact key to find the wanted data
	{
		printf("Comparing %s and %s\n", (char*)key, (char*)node->key);
		if (hmap->keycmpf(key, node->key) == 0)
		{
			return ((void*)node->data);
		}
	}
	ARRAY_LIST_ITER_END(array, t_hmap_node *, node, i)

	return (NULL);
}

/**
 *	Remove the data pointer from the hash map
 *	return 1 if the element was removed, 0 elseway
 *	hmap : the hash map
 *	data : pointer to the data
 */
int hmap_remove_data(t_hmap *hmap, void const *data)
{
	unsigned long int i = 0;
	while (i < hmap->capacity)
	{
		t_array_list *array = hmap->values + i;
		ARRAY_LIST_ITER_START(array, t_hmap_node *, node, index)
		{
			if (node->data == data)
			{
				array_list_remove(array, index);
				hmap->size--;
				
				if (hmap->datafreef)
				{
					hmap->datafreef(node->key);
				}
				
				if (hmap->keyfreef)
				{
					hmap->keyfreef(node->key);
				}
				
				free(node);
				return (1);
			}
		}
		ARRAY_LIST_ITER_END(array, t_hmap_node *, node, index)
		++i;
	}
	return (0);
}

/**
 *	Remove the data which match with the given key from the hash map
 *	return 1 if the element was removed, 0 elseway
 *
 *	hmap : the hash map
 *	key  : pointer to the key
 */
int hmap_remove_key(t_hmap *hmap, void const *key)
{
	unsigned long int hash = hmap->hashf(key); //get the hash for this key
	unsigned long int addr = hash & (hmap->capacity - 1); //get the array list from the hash
	
	t_array_list *array = hmap->values + addr; //array of collision for this key hash
	
	if (array->size == 0)
	{
		return (0);
	}
	
	ARRAY_LIST_ITER_START(array, t_hmap_node *, node, index) //so compare the exact key to find the wanted data
	{
		if (hmap->keycmpf(key, node->key) == 0)
		{
			array_list_remove(array, index);
			
			if (hmap->datafreef)
			{
				hmap->datafreef(node->key);
			}
			
			if (hmap->keyfreef)
			{
				hmap->keyfreef(node->key);
			}
			
			free(node);
				
			return (1);
		}
	}
	ARRAY_LIST_ITER_END(array, t_hmap_node *, node, index)

	return (0);
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
    t_hmap hmap = hmap_new(1024, (t_hf)strhash, (t_cmpf)strcmp, free, free);
	hmap_insert(&hmap, strdup("Hello world"), strdup("ima key"));
	
	char *key = strdup("ima key");
	char *str = hmap_get(&hmap, key);
	
	printf("{%s} from key {%s}\n", str, key);
	
	hmap_delete(&hmap);
	free(key);
	return (0);
}
