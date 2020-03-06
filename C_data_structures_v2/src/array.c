# include "array.h"

/**
 *	@require : la capacité de départ du tableau dynamique
 *	@ensure  : alloue en mémoire un tableau dynamique
 *	@assign  : ------------------
 */
t_array * array_new(unsigned int defaultCapacity, unsigned int elemSize) {
	t_array * array = (t_array *) malloc(sizeof(t_array));
	if (array == NULL) {
		/* pas assez de mémoire */
		return (NULL);
	}
	size_t size = defaultCapacity * elemSize;
	array->values = (BYTE *) malloc(size);
	if (array->values == NULL) {
		/* pas assez de mémoire */
		free(array);
		return (NULL);
	}
	array->capacity = defaultCapacity;
	array->size = 0;
	array->elemSize = elemSize;
	return (array);
}

/**
 *	@require : 'array': tableau dynamique alloué via 'array_new()'
 *	@ensure  : désalloue de la mémoire le tableau 'array()'
 *	@assign  : ------------------
 */
void array_delete(t_array * array) {
	if (array == NULL) {
		return ;
	}
	free(array->values);
	free(array);
}

/**
 *	@require : un tableau 'array' et un index
 *	@ensure  : renvoie la valeur à l'index 'index' du tableau,
 *			ou NULL si erreur
 *	@assign  : -----------
 */
void * array_get(t_array * array, unsigned int index) {
	if (index >= array->size) {
		return (NULL);
	}
	return (array->values + index * array->elemSize);
}

/**
 *	@require : un tableau 'array' et une valeur 'value'
 *	@ensure  : modifie la capacité du tableau.
 *			renvoie -1 si erreur, 0 sinon
 *	@assign  : 'array->values' peut être modifié par 'realloc()'
 */
int array_grow(t_array * array, unsigned int capacity) {
	if (capacity == 0) {
		free(array->values);
		array->values = NULL;
	} else {
		array->values = realloc(array->values, capacity * array->elemSize);
		if (array->values == NULL) {
			return (-1);
		}
	}
	array->capacity = capacity;
	return (0);
}

/**
 *	@require : un tableau 'array' et une capacité 'capacity'
 *	@ensure  : assure que le tableau puisse accueillir au moins 'capacity' entrée
 *			renvoie -1 si erreur, 0 sinon
 *	@assign  : @see array_grow()
 */
int array_ensure_capacity(t_array * array, unsigned int capacity) {
	if (array->capacity > capacity) {
		return (0);
	}
	unsigned int c = (capacity + 1) / 2 * 3;
	if (array_grow(array, c) == -1) {
		return (-1);
	}
	return (0);
}

/**
 *	@require : un tableau 'array', un index, et une valeur 'value'
 *	@ensure  : ajoutes la valeur 'value' a l'index donnée dans le tableau
 *			renvoie -1 en cas d'erreur, sinon l'index où l'élément a été inséré
 *	@assign  : grossit la capacité du tableau si necessaire
 */
int array_set(t_array * array, unsigned int index, void * value) {
	if (index > array->size) {
		index = array->size;
	}
	if (array_ensure_capacity(array, index) == -1) {
		return (-1);
	}
	memcpy(array->values + index * array->elemSize, value, array->elemSize);
	if (index >= array->size) {
		array->size = index + 1;
	}
	return (index);
}

/**
 *	@require : un tableau 'array' et une valeur 'value'
 *	@ensure  : ajoutes la valeur 'value' en bout de tableau 'array'
 *			renvoie -1 en cas d'erreur, sinon l'index du nouvel élément
 *	@assign  : modifie les valeurs du tableau
 */
int array_add(t_array * array, void * value) {
	return (array_set(array, array->size, value));
}

/**
 *	@require : un tableau 'array' une valeur 'value', et un entier 'n'
 *	@ensure  : ajoutes n fois la valeur 'value' en bout de tableau 'array'
 *			return -1 si erreur, 0 sinon
 *	@assign  : modifie les valeurs du tableau
 */
int array_addn(t_array * array, void * value, unsigned int n) {
	if (array_ensure_capacity(array, array->size + n) == -1) {
		return (-1);
	}
	unsigned int i;
	for (i = 0 ; i < n ; i++) {
		BYTE * addr = array->values + (array->size + i) * array->elemSize;
		memcpy(addr, value, array->elemSize);
	}
	int idx = array->size;
	array->size += n;
	return (idx);
}

/**
 *	@require : un tableau 'array', et un entier 'n'
 *	@ensure  : ajoutes n valeur non initialisé dans le tableau (allocation)
 *			return -1 si erreur, 0 sinon
 *	@assign  : modifie array->size
 */
int array_addempty(t_array * array, unsigned int n) {
	if (array_ensure_capacity(array, array->size + n) == -1) {
		return (-1);
	}
	int idx = array->size;
	array->size += n;
	return (idx);
}

/**
 *	@require : un tableau 'array', un tableau de valeur 'values',
 *			et la taille de 'values'
 *	@ensure  : ajoutes les valeurs 'values' en bout de tableau 'array'
 *			return -1 si erreur, l'index du 1er element inseré sinon
 *	@assign  : modifie les valeurs du tableau
 */
int array_add_all(t_array * array, void * values, unsigned int count) {
	if (array_ensure_capacity(array, array->size + count) == -1) {
		/* pas assez de mémoire */
		return (-1);
	}
	memcpy(array->values + array->size, values, count * array->elemSize);
	unsigned int index = array->size;
	array->size += count;
	return ((int)index); 
}

/**
 *	@require : un tableau 'array'
 *	@ensure  : vide le tableau
 *	@assign  : array.size mis à 0
 */
void array_clear(t_array * array) {
	array->size = 0;
}

/**
 *	@require : un tableau 'array'
 *	@ensure  : reduit le plus possible la taille mémoire utilisé par le tableau
 *			en gardant tous les éléments inserés en mémoire
 *	@assign  : array->capacity peut être changé
 */
void array_trim(t_array * array) {
	array->capacity = array->size;
	array->values = (BYTE *)realloc(array->values, array->size * array->elemSize);
}

/**
 *	@require : un tableau 'array' et un index du tableau
 *	@ensure  : supprime l'élément à l'index donné
 *	@assign  : les index des éléments suivant sont décalés pour éviter la fragmentation
 */
void array_remove(t_array * array, unsigned int index) {
	if (index >= array->size) {
		return ;
	}

	unsigned int begin = index * array->elemSize;
	unsigned int end = (array->size - 1) * array->elemSize;
	unsigned int offset = end - begin;
	if (offset != 0) {
		BYTE * left = array->values + begin;
		BYTE * right = array->values + begin + array->elemSize;
		memmove(left, right, offset);
	}
	--array->size;
}

/**
 *	@require : un tableau 'array'
 *	@ensure  : supprime le dernier élément du tableau
 *	@assign  : ----
 */
void array_removelast(t_array * array) {
	if (array->size == 0) {
		return ;
	}
	--array->size;
}
	
/**
 *	@require : un tableau 'array' et une fonction de comparaison (voir strcmp())
 *	@ensure  : tri le tableau dans l'ordre croissant de la fonction de comparaison
 *	@assign  : modifie les index des elements du tableau (en triant les elements)
 */
void array_sort(t_array * array, int (*cmpf)(const void * left, const void * right)) {
	qsort(array->values, array->size, array->elemSize, cmpf);
}

/**
 *	@require : un tableau 'array'
 *	@ensure  : inverse l'ordre des elements du tableau
 *	@assign  : -------------------------
 */
void array_reverse(t_array * array) {
	BYTE * buffer = (BYTE *) malloc(array->elemSize);
	if (buffer == NULL) {
		return ;
	}
	size_t elemSize = array->elemSize;
	size_t i;
	for (i = 0 ; i < array->size / 2 ; i++) {
		size_t j = array->size - 1 - i;
		memcpy(buffer,				array->values + i * elemSize, 	elemSize);
		memcpy(array->values + i * elemSize,	array->values + j * elemSize, 	elemSize);
		memcpy(array->values + j * elemSize,	buffer,				elemSize);
	}
	free(buffer);
}

