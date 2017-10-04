/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#include "array_list.h"

/**
 * Create a new array list
 * nb : number of elements which the array can hold on first allocation
 * elem_size : size of an elements
 *
 * e.g: t_array_list array = array_list_new(16, sizeof(int));
 */
t_array_list * array_list_new(unsigned long int nb, unsigned int elem_size) {
	t_array_list * array = (t_array_list *)malloc(sizeof(t_array_list));
	if (array == NULL) {
		return (NULL);
	}

	array->data = calloc(nb, elem_size);
	array->capacity = nb;
	array->elem_size = elem_size;
	array->size = 0;
	array->default_capacity = nb;
	return (array);
}

/**
 * resize array list
 */
static void array_list_resize(t_array_list * array, unsigned size) {
	array->data = realloc(array->data, size * array->elem_size);
	array->capacity = size;
	if (array->size > size) {
		array->size = size;
	}
}

static void array_list_expand(t_array_list * array) {
	unsigned long int size = array->capacity == 0 ? 1 : array->capacity * 2;
	array_list_resize(array, size);
}

/**
 *  Add an element at the end of the list
 */
int array_list_add(t_array_list * array, void * data) {
	if (array->size == array->capacity) {
		array_list_expand(array);
	}
	memcpy(array->data + array->size * array->elem_size, data, array->elem_size);
	array->size++;
	return (array->size);
}

/**
 *  Add every elements the end of the list
 *  this function is faster than calling multiples 'array_list_add()'
 *  so consider using it :)
 */
void array_list_add_all(t_array_list * array, void * buffer, unsigned long int nb) {
	unsigned int array_idx = array->size * array->elem_size;
	while (nb) {
		unsigned int copy_nb = array->capacity - array->size;
		if (copy_nb > nb) {
			copy_nb = nb;
		}
		if (copy_nb == 0) {
			array_list_expand(array);
			continue ;
		}
		unsigned int copy_size = copy_nb * array->elem_size;
		memcpy(array->data + array_idx, buffer, copy_size);
		nb -= copy_nb;
		array->size += copy_nb;
		buffer += copy_size;
		array_idx += copy_size;
	}
}

/**
 * get item by index
 */
void * array_list_get(t_array_list * array, unsigned int idx) {
	return (array->data + idx * array->elem_size);
}

/**
 *  remove the element at given index
 */
void array_list_remove(t_array_list * array, unsigned int idx) {
	if (array->size == 0 || idx >= array->size) {
		return ;
	}

	unsigned int begin = idx * array->elem_size;
	unsigned int end = (array->size - 1) * array->elem_size;    
	memmove(array->data + begin, array->data + begin + array->elem_size, end - begin);

	array->size--;
}

/**
 *  Clear the list (remove every data, and resize it to the default capacity)
 */
void array_list_clear(t_array_list * array) {
	array->size = 0;
	array_list_resize(array, array->default_capacity);
}

/**
 *  Delete DEFINETELY the list from memory
 */
void array_list_delete(t_array_list * array) {
	free(array->data);
}

/**
 *  Sort the array list using std quicksort algorythm
 *
 *  e.g:    t_array_list array = array_list_new(16, sizeof(char) * 2);
 *          array_list_add(&array, "d");
 *          array_list_add(&array, "a");
 *          array_list_add(&array, "f");
 *          [...]
 *          array_list_sort(&array, (t_cmp_function)strcmp);
 */
void array_list_sort(t_array_list * array, t_cmp_function cmpf) {
	qsort(array->data, array->size, array->elem_size, cmpf);
}

/**
 *  Get raw data of your array list
 *  (buffer of every data)
 *  You should really not use this function
 */
void * array_list_raw(t_array_list * array) {
	return (array->data);
}



//TESTS
/*
   int main()
   {
   puts("\tARRAY LIST TESTS STARTED");
   t_array_list * array = array_list_new(16, sizeof(char));

   unsigned long int i = 0;
   unsigned long int max = 10000000;
   unsigned long int t1;
   unsigned long int t2;
   unsigned long int t;

   MICROSEC(t1);
   while (i < max) {
   array_list_add(array, "a");
   ++i;
   }
   MICROSEC(t2);
   t = t2 - t1;

   printf("\t\t%-30s%lu\n", "elements added : ", max);
   printf("\t\t%-30s%lu\n", "array number of elements : ", array->size);
   printf("\t\t%-30s%lu\n", "array capacity now : ", array->capacity);
   printf("\t\t%-30s%lf s\n", "time taken: ", t / 1000000.0f);

   {
   printf("\n\tIterating on array...\n");
   MICROSEC(t1);
   ARRAY_LIST_ITER_START(array, char *, item, iterator) {
   char c = *item;
   if (c != 'a') {
   fprintf(stderr, "ARRAY LIST ITER ERROR!!!!!");
   }
   (void)c;
   }
   ARRAY_LIST_ITER_END(array, char *, item, iterator);
   MICROSEC(t2);
   t = t2 - t1;
   printf("\t\t%-30s%lf s\n", "time taken: ", t / 1000000.0f);
   }

   {
   unsigned long int toremove = max / 1000;
   printf("\n\tRemoving %lu last elements ...\n", toremove);
   MICROSEC(t1);
   while (toremove) {
   array_list_remove(array, array->size - 1);
   --toremove;
   }
   MICROSEC(t2);
   t = t2 - t1;
   printf("\t\t%-30s%lf s\n", "time taken: ", t / 1000000.0f);
   }

   {
   unsigned long int toremove = max / 1000;
   printf("\n\tRemoving %lu first elements ...\n", toremove);
   MICROSEC(t1);
   while (toremove) {
   array_list_remove(array, 0);
   --toremove;
   }
   MICROSEC(t2);
   t = t2 - t1;
   printf("\t\t%-30s%lf s\n", "time taken: ", t / 1000000.0f);
   }



   {
   unsigned long int toremove = max / 1000;
unsigned long int middle = (max - toremove) / 2;
printf("\n\tRemoving %lu middle elements ...\n", toremove);
MICROSEC(t1);
while (toremove) {
	array_list_remove(array, middle + toremove);
	--toremove;
}
MICROSEC(t2);
t = t2 - t1;
printf("\t\t%-30s%lf s\n", "time taken: ", t / 1000000.0f);
}

{
	printf("\n\tDeleting array...\n");
	MICROSEC(t1);
	array_list_delete(array);
	MICROSEC(t2);
	t = t2 - t1;
	printf("\t\t%-30s%lu\n", "array number of elements : ", array->size);
	printf("\t\t%-30s%lu\n", "array capacity now : ", array->capacity);
	printf("\t\t%-30s%lf s\n", "time taken: ", t / 1000000.0f);
}

puts("\tARRAY LIST TESTS PASSED");
return (1);
}
*/
