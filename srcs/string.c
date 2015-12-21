/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#include "str.h"

/**
 * Create a new string
 */
t_str str_new(void const *data)
{
	static char initialized = 0;
	
	if (initialized == 0)
	{
		setlocale(LC_ALL, "");
		initialized = 1;
	}
		
	size_t length = wcslen(data);
	wchar_t *ptr = (wchar_t*)malloc(sizeof(wchar_t) * (length + 1));
	if (ptr == NULL)
	{
		t_str str = {0, 0};
		return (str);
	}
	
	t_str str = {ptr, length};
	memcpy(ptr, data, (length + 1) * sizeof(wchar_t));
	return (str);
}

/**
 *	Delete the string from the heap
 */
void str_delete(t_str *str)
{
	free(str->ptr);
	str->ptr = NULL;
	str->length = 0;
}

/**
 *	Set a char of the string
 */
int str_set_char(t_str *str, wchar_t c, size_t index)
{
	if (index >= str->length)
	{
		return (0);
	}
	str->ptr[index] = c;
	return (1);
}

/**
 *	add a string to another
 */
int str_append(t_str *str, wchar_t *cs)
{
	size_t length = wcslen(cs);
	str->ptr = realloc(str->ptr, (str->length + length + 1) * sizeof(wchar_t));
	if (str->ptr == NULL)
	{
		return (0);
	}
	memcpy(str->ptr + str->length, cs, sizeof(wchar_t) * length);
	str->length = str->length + length;
	str->ptr[str->length] = 0;
	return (1);
}
 
int main()
{
	t_str str = str_new(L"Hello world");
	str_set_char(&str, L'ê', 1);
	str_append(&str, L" dés äccênts");
	printf("%S\n", str.ptr);

	puts("done");
	return (0);
}
