/**
 *  This file is part of https://github.com/toss-dev/C_data_structures
 *
 *  It is under a GNU GENERAL PUBLIC LICENSE
 *
 *  This library is still in development, so please, if you find any issue, let me know about it on github.com
 *  PEREIRA Romain
 */

#ifndef ARRAY_LIST_H
# define ARRAY_LIST_H

# include "common.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct  s_array_list {
    char                * data;
    unsigned long int   capacity;
    unsigned long int   size;
    unsigned int        elem_size;
    unsigned int        default_capacity;
}               t_array_list;

/**
 * Create a new array list
 * nb : number of elements which the array can hold on first allocation
 * elem_size : size of an elements
 *
 * e.g: t_array_list array = array_list_new(16, sizeof(int));
 */
t_array_list * array_list_new(unsigned long int nb, unsigned int elem_size);

/**
 *  Add an element at the end of the list
 */
int array_list_add(t_array_list * array, void * data);

/**
 *  Clear the list (remove every data, and resize it to the default capacity)
 */
void array_list_clear(t_array_list * array);

/**
 *  Delete DEFINETELY the list from memory
 */
void array_list_delete(t_array_list * array);

/**
 *  remove the element at given index
 */
void array_list_remove(t_array_list * array, unsigned int idx);

/**
 *  Sort the array list using std quicksort algorythm
 *
 *  e.g:    t_array_list array = array_list_new(16, sizeof(char) * 2);
 *          array_list_push(&array, "d");
 *          array_list_push(&array, "a");
 *          array_list_push(&array, "f");
 *          [...]
 *          array_list_sort(&array, (t_cmp_function)strcmp);
 */
void array_list_sort(t_array_list * array, t_cmp_function cmpf);

/**
 *  Add every elements the end of the list
 *  this function is faster than calling multiples 'array_list_add()'
 *  so consider using it :)
 */
void array_list_add_all(t_array_list * array, void * buffer, unsigned long int nb);

/**
 *  Get raw data of your array list
 *  (buffer of every data)
 *  You should really not use this function
 */
void * array_list_raw(t_array_list * array);

/**
 * get item by index
 */
void * array_list_get(t_array_list * array, unsigned int idx);

/**
 * Iterate on the array list using a macro
 *
 * i.e :    t_array_list array;
 *
 *          [...] //push strings to the list
 *
 *          // print every string which the array list holds
 *          ARRAY_LIST_ITER_START(array, char *, str, i)
 *          {
 *              puts(str);
 *          }
 *          ARRAY_LIST_ITER_END(array, char *, str, i);
 */
# define ARRAY_LIST_ITER_START(L, T, X, I)\
 {\
    unsigned long int I = 0;\
    while (I < (L)->size) {\
        T X = ((T)(L)->data) + I;
# define ARRAY_LIST_ITER_END(L, T, X, I)\
       ++I;\
    }\
}

#endif
