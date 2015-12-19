/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#ifndef STRINGS_H
# define STRINGS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>

char **strsplit(char *str, char *delimiter);
char *strrev(char *str);
char *strepur(char *str);
char *strtrim(char *str);
char *to_base(int value, char *charset, char *dst);
int match(char *s1, char *s2);

#endif
