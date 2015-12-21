/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#ifndef STR_H
# define STR_H

# include "common.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <wchar.h>
# include <locale.h>

typedef struct	s_str
{
	wchar_t *ptr;
	size_t length;
}				t_str;

/**
 *	create a new string.
 */
t_str	str_new(void const *data);

/**
 *	Delete the string from the heap
 */
void	str_delete(t_str *str);

#endif
