/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#ifndef COMMON_H
# define COMMON_H

# include <sys/time.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# ifndef BYTE
# 	define BYTE unsigned char
# endif

# ifndef BIT
# 	define BIT BYTE
# endif

typedef void (*t_function)();
typedef int	(*t_cmp_function) (void const * a, void const * b);
typedef unsigned long int (*t_hash_function) (void const * v);


typedef t_function t_f;
typedef t_cmp_function t_cmpf;
typedef t_hash_function t_hf;

# define MICROSEC(V)    {\
    struct timeval tv;\
    gettimeofday(&tv, NULL);\
    V = 1000000 * tv.tv_sec + tv.tv_usec;\
}


#endif
