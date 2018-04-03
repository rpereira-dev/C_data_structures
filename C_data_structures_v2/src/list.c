# include "list.h"

/**
 *	\brief crée une nouvelle liste doublent chainée circulaire
 *	\return une nouvelle liste, ou NULL si erreur
 */
t_list * list_new(void) {
	t_list * lst = (t_list *) malloc(sizeof(t_list));
	if (lst == NULL) {
		return (NULL);
	}
	lst->main = (t_list_node *) malloc(sizeof(t_list_node));
	if (lst->main == NULL) {
		free(lst);
		return (NULL);
	}
	lst->main->next = lst->main;
	lst->main->prev = lst->main;
	lst->size = 0;
	return (lst);

}

/**
 *	\brief Recuperes la donnée sur un sommet
 *	\param node : un sommet
 *	\return la donnée enregistré sur le sommet
 */
void * list_node_data(t_list_node * node) {
	return (node + 1);
}

/**
 *	\brief Ajoutes un nouveau maillon après le maillon passé en paramètre
 *	\param lst : la liste
 *	\param before : le sommet apres lequel le nouveau maillon va être inseré
 *	\content : la donnée
 *	\content_size : la taille de la donnée
 *	\return : l'addresse où la donnée a été copié
 *	\attention :	ne pas appeler cette fonction directement, utiliser plutot
 *			\see list_add_head
 *			\see list_add_tail
 *			\see LIST_ITERATE_ADD_AFTER
 *			\see LIST_ITERATE_ADD_BEFORE
 */
void * list_add_node(t_list * lst, t_list_node * before,
			void const * content, unsigned int content_size) {
	t_list_node * node = (t_list_node *) malloc(sizeof(t_list_node) + content_size);
	if (node == NULL) {
		return (NULL);
	}
	memcpy(node + 1, content, content_size);

	t_list_node * tmp = before->next;

	before->next = node;
	tmp->prev = node;

	node->prev = before;
	node->next = tmp;

	++lst->size;

	return (node + 1);
}

/**
 *	\brief Ajoutes un élement en fin liste
 *	\param lst : une liste
 *	\param content : la donnée à ajouter
 *	\param content_size : la taille de la donnée
 *	\return : l'adresse où la donnée a été copié
 */
void * list_add_head(t_list * lst, void const * content, unsigned int content_size) {
	return (list_add_node(lst, lst->main, content, content_size));
}

/**
 *	\brief Ajoutes un élement en tête de liste
 *	\param lst : une liste
 *	\param content : la donnée à ajouter
 *	\param content_size : la taille de la donnée
 *	\return : l'adresse où la donnée a été copié
 */
void * list_add_tail(t_list * lst, void const * content, unsigned int content_size) {
	return (list_add_node(lst, lst->main->prev, content, content_size));
}

/**
 *	\brief Recuperes la donnée en tête de liste
 *	\param lst : une liste
 *	\return La donnée en tête de liste
 */
void * list_get_head(t_list * lst) {
	if (lst->size == 0) {
		return (NULL);
	}
	return ((void *) (lst->main->next + 1));
}

/**
 *	\brief Recuperes la donnée en fin de liste
 *	\param lst : une liste
 *	\return La donnée en fin de liste
 */
void * list_get_tail(t_list * lst) {
	if (lst->size == 0) {
		return (NULL);
	}
	return ((void *) (lst->main->prev + 1));
}

/**
 *	\brief Supprimes un sommet de la liste
 *	\param lst : une liste
 *	\param node : un sommet de la liste
 */
void list_remove_node(t_list * lst, t_list_node * node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
	lst->size--;
}

/**
 *	\brief Supprimes l'élément en tête de liste
 *	\param lst : une liste
 *	\return 1 si succès, 0 sinon
 */
int list_remove_head(t_list * lst) {
	if (lst->size == 0) {
		return (0);
	}
	list_remove_node(lst, lst->main->next);
	return (1);
}

/**
 *	\brief Supprimes l'élément en fin de liste
 *	\param lst : une liste
 *	\return 1 si succès, 0 sinon
 */
int list_remove_tail(t_list * lst) {
	if (lst->size == 0) {
		return (0);
	}
	list_remove_node(lst, lst->main->prev);
	return (1);
}

/**
 *	\brief Appliques une fonction sur chaque donnée de la liste
 *	\param lst : une liste
 *	\param f : une fonction
 *	\return 1 si succès, 0 sinon
 */
void list_map(t_list * lst, void (*f)(void const * value)) {
	t_list_node * node = lst->main->next;
	while (node != lst->main) {
		f(node + 1);
		node = node->next;
	}
}

/**
 *	\brief Supprimes tous les éléments de la liste
 *	\param lst : une liste
 */
void list_clear(t_list * lst) {
	t_list_node * node = lst->main->next;
	while (node != lst->main) {
		t_list_node * next = node->next;
		free(node);
		node = next;
	}
	lst->size = 0;
}

/**
 *	\brief Libères la mémoire dedié à la liste
 *	\param lst : une liste
 */
void list_delete(t_list * lst) {
	if (lst == NULL) {
		return ;
	}
	if (lst->size > 0) {
		list_clear(lst);
	}
	free(lst->main);
	free(lst);
}
