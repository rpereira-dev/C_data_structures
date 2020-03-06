# include "tests.h"

/**
 *	\internal	Une fonction interne qui permet de généré
 *			une suite de test simplement.
 */
static void add_suite(char * name,
			void (*test_suite)(CU_pSuite),
			int (*test_suite_init)(void),
			int (*test_suite_deinit)(void)) {
	CU_pSuite pSuite = CU_add_suite(name, test_suite_init, test_suite_deinit);
	if (pSuite == NULL) {
		fprintf(stderr, "Couldn't create test suite: %s (error: %d)\n",
				name, CU_get_error());
		CU_cleanup_registry();
		return ;
	}
	test_suite(pSuite);
}

int main(void) {
	/** initialisation of CUnit */
	if (CU_initialize_registry() != CUE_SUCCESS) {
		fprintf(stderr, "tests error 'CU_initialize_registry()' %d\n",
				CU_get_error());
		return (EXIT_FAILURE);
	}

	/** les tests sont ajoutés ici: */
	add_suite("list.c",    test_list,    test_init_list,    test_deinit_list);
	add_suite("array.c",   test_array,   test_init_array,   test_deinit_array);

	/** de-initialisation of CUnit */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return (EXIT_SUCCESS);
}
