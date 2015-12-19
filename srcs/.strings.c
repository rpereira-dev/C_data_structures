/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
*/

#include "strings.h"

/**
 * split the given string following the given delimiter, to an array of string
 * e.g: ("a, simple, test", ",") == ["a", " simple", " test", NULL, "a\0simple\0test\0"]
 */
char **strsplit(char *str, char *delimiter)
{
    int s_length = strlen(str);
    int d_length = strlen(delimiter);
 
    int itemcount = 0;
    int delimiter_count = 0;
    
    char *tmp = str;
    while (*tmp)
    { 
        while (strncmp(tmp, delimiter, d_length) == 0)
        {
            tmp += d_length;
            delimiter_count++;
        }
        while (*tmp && strncmp(tmp, delimiter, d_length) != 0)
        {
            ++tmp;
        }
        itemcount++;
    }

    int array_length = sizeof(char*) * (itemcount + 1);
    int data_length = s_length - d_length * delimiter_count + itemcount;
    char **split = (char**)malloc(array_length + data_length);
    split[itemcount] = NULL;
    char *data = (char*)split + array_length;
    char *begin;
    int length;
    int i = 0;
    tmp = str;

    while (*tmp)
    {
        while (strncmp(tmp, delimiter, d_length) == 0)
        {
            tmp += d_length;
        }
        if (*tmp == 0)
        {
            break ;
        }
        begin = tmp;
        while (*tmp && strncmp(tmp, delimiter, d_length) != 0)
        {
            ++tmp;
        }
        length = tmp - begin;
        memcpy(data, begin, length);
        data[length] = 0;
        split[i] = data;
        ++i;
        data = data + length + 1;
    }
    return (split);
}

char *strrev(char *str)
{
    int length = strlen(str);
    int i = 0;
    int size = length / 2;
    char c;

    while (i < size)
    {
        c = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = c;
        ++i;
    }
    return (str);
}

/**
 * convert the given int to the given base,
 * and store the result at the given char address
 * return the address on success, or NULL on error
*/
char *to_base(int value, char *charset, char *dst)
{
    int i = 0;
    int base = strlen(charset);
    
    if (base == 0)
    {
        return (NULL);
    }

    do
    {
        dst[i] = charset[(value % base)];
        value /= base;
        ++i;
    }
    while (value);
    dst[i] = 0;
    return (strrev(dst));
}

/**
 * trim the given string, and store the result to the given address.
 * If given address is NULL, a new address is allocated using malloc()
 */ 
char *strtrim(char *str)
{
    unsigned int len = strlen(str) - 1;
    unsigned int i = 0;

    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
    {
        i++;
    }
    while (len > 0 && (str[len] == '\n' || str[len] == ' ' || str[len] == '\t'))
    {
        len--;
    }
    len = len - i + 1;
    memmove(str, str + i, len);
    str[len] = 0;
    return (str);
}

static int _tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return (c + ('a' - 'A'));
    }
    return (c);
}

int match(char *s1, char *s2)
{
    if (*s1 && _tolower(*s1) == _tolower(*s2) && *s1 != '*')
    {
        return (match(s1 + 1, s2 + 1));
    }
    else if (*s1 && *s2 == '*')
    {
        return (match(s1, s2 + 1) || match(s1 + 1, s2));
    }
    else if (*s2 == '*')
    {
        return (match(s1, s2 + 1));
    }
    else if (*s1 == 0 && *s2 == 0)
    {
        return (1);
    }
    return (0);
}

/**
 * remove every mutliple white space from the given string
 * e.g : ("hello   how       are   you?     ") => ("hello how are you?")
 */
char *strepur(char *str)
{
    int i = 0;
    int j = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
    {
        i++;
    }
    while (str[i])
    {
        while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
        {
            str[j] = str[i];
            ++i;
            ++j;
        }
        while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            i++;
        }
        if (str[i])
        {
            str[j] = ' ';
            ++j;
        }
    }
    str[j] = 0;
    return (str);
}

