#ifndef COMMON_H
# define COMMON_H

# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

typedef void	(*t_function)();
typedef int		(*t_cmp_function) (void const *a, void const *b);
typedef t_function t_f;
typedef t_cmp_function t_cmpf;

# define MICROSEC(V)    {\
                            struct timeval tv;\
                            gettimeofday(&tv, NULL);\
                            V = 1000000 * tv.tv_sec + tv.tv_usec;\
                        }


#endif
