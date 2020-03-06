/**
 *  This file is part of https://github.com/toss-dev/C_data_structures
 *
 *  It is under a GNU GENERAL PUBLIC LICENSE
 *
 *  This library is still in development, so please, if you find any issue, let me know about it on github.com
 *  PEREIRA Romain
 */

#ifndef ARRAY_H
# define ARRAY_H

# include <stdio.h> /* printf */
# include <stdlib.h> /* malloc */
# include <string.h> /* memmove */

# ifndef BYTE
#	define BYTE unsigned char
# endif

/**
 *	Structure de donnée: tableau dynamique ("Array list")
 */
typedef struct  s_array {
	BYTE             * values;	/* les valeurs du tableau */
	unsigned int    capacity;	/* capacité mémoire du tableau 'values' */
	unsigned int    size;		/* nombre d'element dans le tableau 'values' */
	unsigned int	elemSize;	/* taille d'un element du tableau */
}               t_array;

/**
 *	@require : la capacité de départ du tableau dynamique
 *	@ensure  : alloue en mémoire un tableau dynamique
 *	@assign  : ------------------
 */
t_array * array_new(unsigned int defaultCapacity, unsigned int elemSize);

/**
 *	@require : 'array': tableau dynamique alloué via 'array_new()'
 *	@ensure  : désalloue de la mémoire le tableau 'array()'
 *	@assign  : ------------------
 */
void array_delete(t_array * array);

/**
 *	@require : un tableau 'array' et un index
 *	@ensure  : renvoie la valeur à l'index 'index' du tableau
 *			ou NULL si erreur
 *	@assign  : -----------
 */
void * array_get(t_array * array, unsigned int index);

/**
 *	@require : un tableau 'array', un index, et une valeur 'value'
 *	@ensure  : ajoutes la valeur 'value' a l'index donnée dans le tableau
 *			renvoie -1 si erreur, sinon l'index ou l'élément a été inséré
 *	@assign  : grossit la capacité du tableau si necessaire
 */
int array_set(t_array * array, unsigned int index, void * value);

/**
 *	@require : un tableau 'array' et une valeur 'value'
 *	@ensure  : modifie la capacité du tableau.
 *			renvoie -1 si erreur, 0 sinon
 *	@assign  : 'array->values' peut être modifié par 'realloc()'
 */
int array_grow(t_array * array, unsigned int capacity);

/**
 *	@require : un tableau 'array' et une capacité 'capacity'
 *	@ensure  : assure que le tableau puisse accueillir au moins 'capacity' entrée
 *			renvoie -1 si erreur, 0 sinon
 *	@assign  : @see array_grow()
 */
int array_ensure_capacity(t_array * array, unsigned int capacity);
	
/**
 *	@require : un tableau 'array' et une valeur 'value'
 *	@ensure  : ajoutes la valeur 'value' en bout de tableau 'array'
 *			return -1 si erreur, 0 sinon
 *	@assign  : modifie les valeurs du tableau
 */
int array_add(t_array * array, void * value);

/**
 *	@require : un tableau 'array' une valeur 'value', et un entier 'n'
 *	@ensure  : ajoutes n fois la valeur 'value' en bout de tableau 'array'
 *			return -1 si erreur, 0 sinon
 *	@assign  : modifie les valeurs du tableau
 */
int array_addn(t_array * array, void * value, unsigned int n);

/**
 *	@require : un tableau 'array', et un entier 'n'
 *	@ensure  : ajoutes n valeur non initialisé dans le tableau (allocation)
 *			return -1 si erreur, 0 sinon
 *	@assign  : modifie array->size
 */
int array_addempty(t_array * array, unsigned int n);

/**
 *	@require : un tableau 'array', un tableau de valeur 'values',
 *			et la taille de 'values'
 *	@ensure  : ajoutes les valeurs 'values' en bout de tableau 'array'
 *			return -1 si erreur, 0 sinon
 *	@assign  : modifie les valeurs du tableau
 */
int array_add_all(t_array * array, void * values, unsigned int count);

/**
 *	@require : un tableau 'array'
 *	@ensure  : vide le tableau
 *	@assign  : array.size mis à 0
 */
void array_clear(t_array * array);

/**
 *	@require : un tableau 'array'
 *	@ensure  : reduit le plus possible la taille mémoire utilisé par le tableau
 *			en gardant tous les éléments inserés en mémoire
 *	@assign  : array->capacity peut être changé
 */
void array_trim(t_array * array);

/**
 *	@require : un tableau 'array' et un index du tableau
 *	@ensure  : supprime l'élément à l'index donné
 *	@assign  : les index des éléments suivant sont décalés pour éviter la fragmentation
 */
void array_remove(t_array * array, unsigned int index);

/**
 *	@require : un tableau 'array'
 *	@ensure  : supprime le dernier élément du tableau
 *	@assign  : ----
 */
void array_removelast(t_array * array);

/**
 *	@require : un tableau 'array' et une fonction de comparaison (voir strcmp())
 *	@ensure  : tri le tableau dans l'ordre croissant de la fonction de comparaison
 *	@assign  : modifie les index des elements du tableau (en triant les elements)
 */
void array_sort(t_array * array, int (*cmpf)(const void * left, const void * right));

/**
 *	@require : un tableau 'array'
 *	@ensure  : inverse l'ordre des elements du tableau
 *	@assign  : -------------------------
 */
void array_reverse(t_array * array);

/**
 *	Macro pour iterer de manière efficace dans le tableau dynamique
 *
 *		A : un tableau
 *		T : le type contenu dans le tableau
 *		X : le nom de la variable d'iteration
 *		I : l'index dans le tableau de 'X'
 *
 *	exemple d'utilisation:
 *
 *	------------------------------------------------------------
 *		t_array * array = array_new(16, sizeof(char *));
 *
 *		array_add(array, strdup("Hello"));
 *		array_add(array, strdup("World"));
 *
 *		ARRAY_ITER_START(array, char *, str, i) {
 *			printf("%d : %s\n", i, str);
 *		}
 *		ARRAY_ITER_END(array, char *, str, i);
 *	------------------------------------------------------------
 *
 *	ce code affiche:
 *		> 0 : Hello
 *		> 1 : World
 */
# define ARRAY_ITERATE_START(A, T, X, I)\
	{\
		if (A != NULL) {\
			size_t I;\
			for (I = 0 ; I < (A)->size ; I++) {\
				T X = ((T)(A)->values) + I;
# define ARRAY_ITERATE_STOP(A, T, X, I)\
			}\
		}\
	}

# endif
