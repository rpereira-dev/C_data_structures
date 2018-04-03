/**
 * 	\file		includes/stack.h
 * 	\authors	Romain PEREIRA
 * 	\brief		Structure de pile
 *
 *	Data structure : pile (LIFO) : dernier entrée, premier sortie
 */

#ifndef STACK_H
# define STACK_H

# include "struct.h"

/**
 *	\struct s_stack_node
 *
 *	Un sommet de la stacke
 */
typedef struct  s_stack_node {
	/** sommet précèdement */
	struct s_stack_node * under;
}               t_stack_node;

/**
 *	\struct s_stack
 *
 *	Une pile
 */
typedef struct	s_stack {
	/** tête de la pile */
	t_stack_node * main;
	/** nombre d'élément inséré dans la pile */
	unsigned long int size;
}		t_stack;

/**
 *	\brief crée une nouvelle pile
 *	\return une nouvelle pile, ou NULL si erreur
 */
t_stack * stack_new(void);

/**
 *	\brief Supprimes tous les éléments de la pile
 *	\param stack: une pile
 */
void stack_clear(t_stack * stack);

/**
 *	\brief Libères la mémoire dedié à la pile
 *	\param stack : une pile alloué via 'stack_new'
 *	\see stack_new
 */
void stack_delete(t_stack * stack);

/**
 *	\brief Recuperes la donnée sur le sommet de la pile
 *	\param stack : la stack
 *	\return la donnée enregistré sur le sommet de la pile
 */
void * stack_peek(t_stack * stack);

/**
 *	\brief Supprime la donnée sur le sommet de la pile
 *	\param stack : la stack
 *	\attention : la pile doit être non vide
 */
void stack_pop(t_stack * stack);

#endif
