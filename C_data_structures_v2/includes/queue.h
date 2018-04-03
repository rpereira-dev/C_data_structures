/**
 * 	\file		includes/queue.h
 * 	\authors	Romain PEREIRA
 * 	\brief		Structure de file
 *
 *	Data structure : file (FIFO) : premier entrée, premier sortie
 */

#ifndef STACK_H
# define STACK_H

# include "struct.h"

/**
 *	\struct s_queue_node
 *
 *	Un sommet de la queuee
 */
typedef struct  s_queue_node {
	/** sommet précèdement */
	struct s_queue_node * under;
}               t_queue_node;

/**
 *	\struct s_queue
 *
 *	Une pile
 */
typedef struct	s_queue {
	/** tête de la pile */
	t_queue_node * main;
	/** nombre d'élément inséré dans la pile */
	unsigned long int size;
}		t_queue;

/**
 *	\brief crée une nouvelle pile
 *	\return une nouvelle pile, ou NULL si erreur
 */
t_queue * queue_new(void);

/**
 *	\brief Supprimes tous les éléments de la pile
 *	\param queue: une pile
 */
void queue_clear(t_queue * queue);

/**
 *	\brief Libères la mémoire dedié à la pile
 *	\param queue : une pile alloué via 'queue_new'
 *	\see queue_new
 */
void queue_delete(t_queue * queue);

/**
 *	\brief Recuperes la donnée sur le sommet de la pile
 *	\param queue : la queue
 *	\return la donnée enregistré sur le sommet de la pile
 */
void * queue_next(t_queue * queue);

/**
 *	\brief Supprime la donnée sur le sommet de la pile
 *	\param queue : la queue
 *	\attention : la pile doit être non vide
 */
void queue_pop(t_queue * queue);

#endif
