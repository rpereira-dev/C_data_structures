#ifndef TESTS_H
# define TESTS_H

# include <stdio.h>
# include <string.h>
# include "CUnit/CUnit.h"
# include "CUnit/Basic.h"
# include "struct.h"


/** list.c tests */
void test_list(CU_pSuite suite);
int test_init_list(void);
int test_deinit_list(void);

/** array.c tests */
void test_array(CU_pSuite suite);
int test_init_array(void);
int test_deinit_array(void);

#endif
