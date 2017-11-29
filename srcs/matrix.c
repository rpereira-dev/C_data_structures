#include "matrix.h"

/**
 *  create a new matrix
 */
t_matrix * matrix_new(size_t n, size_t m) {
	t_matrix * matrix = (t_matrix *)malloc(sizeof(t_matrix) + sizeof(T) * n * m);
	if (matrix == NULL) {
		return (NULL);
	}
	matrix->n = n;
	matrix->m = m;
	matrix_identity(matrix);
	return (matrix);
}

/**
 *  delete the matrix from the heap
 */
void matrix_delete(t_matrix * matrix) {
	free(matrix);
}

/** get element address */
T * matrix_node(t_matrix * matrix, size_t i, size_t j) {
	T * values = (T *)(matrix + 1);
	return (values + (i * matrix->m + j));
}

/**
 *  get the matrix value
 */
T matrix_get(t_matrix * matrix, size_t i, size_t j) {
	return (*(matrix_node(matrix, i, j)));
}

/**
 * set the matrix value
 */
void matrix_set(t_matrix * matrix, size_t i, size_t j, T value) {
	*(matrix_node(matrix, i, j)) = value;
}

/**
 * print the formatted matrix, on the standart output (fd 1)
 */
void matrix_print(t_matrix * matrix, void (*printElement)(t_matrix *, size_t, size_t)) {
	size_t i, j;
	for (i = 0 ; i < matrix->n ; i++) {
		for (j = 0 ; j < matrix->m - 1 ; j++) {
			printElement(matrix, i, j);
			printf("\t");
		}
		printElement(matrix, i, matrix->m - 1);
		printf("\n");
	}
}

/**
 * set the matrix to identity
 */
void matrix_identity(t_matrix * matrix) {
	memset(matrix + 1, 0, sizeof(T) * matrix->n * matrix->m);
	size_t end = matrix->n < matrix->m ? matrix->n : matrix->m;
	size_t i;
	for (i = 0 ; i < end ; i++) {
		matrix_set(matrix, i, i, 1);
	}
}

/**
 * generete a random matrix
 */
void matrix_rand(t_matrix * dst, T (*rng)()) {
	size_t i, j;
	for (i = 0 ; i < dst->n ; i++) {
		for (j = 0 ; j < dst->m ; j++) {
			matrix_set(dst, i, j, rng());
		}
	}
}

/**
 * matrix addition
 */
t_matrix * matrix_add(t_matrix * left, t_matrix * right, T (* addElement)(T, T), t_matrix * dst) {
	if (left->n != right->n || left->m != right->m) {
		return (NULL);
	}
	if (dst == NULL) {
		dst = (t_matrix *)matrix_new(left->n, left->m);
		if (dst == NULL) {
			return (NULL);
		}
	} else if (dst->n != left->n || dst->m != left->m) {
		return (NULL);
	}
	size_t i, j;
	for (i = 0 ; i < dst->n ; i++) {
		for (j = 0 ; j < dst->n ; j++) {
			T l = matrix_get(left, i, j);
			T r = matrix_get(right, i, j);
			matrix_set(dst, i, j, addElement(l, r));
		}
	}
	return (dst);
}

/**
 * matrix substraction
 */
t_matrix * matrix_sub(t_matrix * left, t_matrix * right, T (* subElement)(T, T), t_matrix * dst) {
	if (left->n != right->n || left->m != right->m) {
		return (NULL);
	}
	if (dst == NULL) {
		dst = (t_matrix *)matrix_new(left->n, left->m);
		if (dst == NULL) {
			return (NULL);
		}
	} else if (dst->n != left->n || dst->m != left->m) {
		return (NULL);
	}
	size_t i, j;
	for (i = 0 ; i < dst->n ; i++) {
		for (j = 0 ; j < dst->n ; j++) {
			T l = matrix_get(left, i, j);
			T r = matrix_get(right, i, j);
			matrix_set(dst, i, j, subElement(l, r));
		}
	}
	return (dst);
}

/**
 * matrix multiplication: if dst is NULL, it is allocated and returned,
 * if dst doesn't match sizes, the multiplication is cancelled
 */
t_matrix * matrix_mult(t_matrix * left, t_matrix * right, T (*addElement)(T, T), T (*multElement)(T, T), t_matrix * dst) {
	if (left->m != right->n) {
		return (NULL);
	}
	if (dst == NULL) {
		dst = (t_matrix *)matrix_new(left->n, right->m);
		if (dst == NULL) {
			return (NULL);
		}
	} else if (dst->n != left->n || dst->m != right->m) {
		return (NULL);
	}

	size_t i, j, k;
	for (i = 0 ; i < dst->n ; i++) {
		for (j = 0 ; j < dst->m ; j++) {
			T sum = (T) 0;
			for (k = 0 ; k < left->m ; k++) {
				T l = matrix_get(left, i, k);
				T r = matrix_get(right, k, j);
				sum = addElement(sum, multElement(l, r));
			}
			matrix_set(dst, i, j, sum);
		}
	}
	return (dst);
}

/**
 * create the transpose of the given matrix
 */
t_matrix * matrix_transpose(t_matrix * matrix, t_matrix * dst) {
	if (dst == NULL) {
		dst = (t_matrix *)matrix_new(matrix->m, matrix->n);
		if (dst == NULL) {
			return (NULL);
		}
	} else if (matrix->n != dst->m || matrix->m != dst->n) {
		return (NULL);
	}

	if (matrix == dst) {
		size_t i, j;
		for (i = 0 ; i < matrix->n ; i++) {
			for (j = 0 ; j <= i ; j++) {
				T tmp = matrix_get(matrix, i, j);
				matrix_set(matrix, i, j, matrix_get(matrix, j, i));
				matrix_set(matrix, j, i, tmp);
			}
		}

	} else {
		size_t i, j;
		for (i = 0 ; i < matrix->n ; i++) {
			for (j = 0 ; j < matrix->m ; j++) {
				matrix_set(dst, j, i, matrix_get(matrix, i, j));
			}
		}
	}
	return (dst);
}

/**
 * get the matrix trace
 */
T matrix_trace(t_matrix * matrix, T (*addElement)(T, T)) {
	size_t i;
	size_t end = matrix->n < matrix->m ? matrix->n : matrix->m;
	T trace = (T)0;
	for (i = 0 ; i < end ; i++) {
		trace = addElement(trace, matrix_get(matrix, i, i));
	}
	return (trace);
}

/**
void printElement(t_matrix * matrix, size_t i, size_t j) {
	printf("%d", matrix_get(matrix, i, j));
}

void printElementAddr(t_matrix * matrix, size_t i, size_t j) {
	printf("%p", matrix_node(matrix, i, j));
}

int generateRandomNumber() {
	int r = rand() % 64;
	return (r < 0 ? -r : r);
}

int addInt(int l, int r) {
	return (l + r);	
}

int multInt(int l, int r) {
	return (l * r);
}

int main() {
	t_matrix * m = matrix_new(4, 4);
	matrix_print(m, printElement);
	puts("");
	matrix_print(m, printElementAddr);
	puts("");
	srand(time(NULL));
	matrix_rand(m, generateRandomNumber);
	matrix_print(m, printElement);
	puts("");
	matrix_delete(m);

	t_matrix * l = matrix_new(4, 4);
	t_matrix * r = matrix_new(4, 4);
	matrix_rand(l, generateRandomNumber);
	matrix_rand(r, generateRandomNumber);
	matrix_print(l, printElement);
	puts("");
	matrix_print(r, printElement);
	puts("");
	t_matrix * dst = matrix_add(l, r, addInt, NULL);
	matrix_print(dst, printElement);
	puts("");
	matrix_delete(l);
	matrix_delete(r);
	matrix_delete(dst);

	l = matrix_new(2, 2);
	r = matrix_new(2, 2);
	matrix_rand(l, generateRandomNumber);
	matrix_rand(r, generateRandomNumber);
	dst = matrix_mult(l, r, addInt, multInt, NULL);
	matrix_print(l, printElement);
	puts("");
	matrix_print(r, printElement);
	puts("");
	matrix_print(dst, printElement);
	puts("");
	matrix_delete(l);
	matrix_delete(r);
	matrix_delete(dst);


	m = matrix_new(4, 4);
	matrix_rand(m, generateRandomNumber);
	matrix_print(m, printElement);
	puts("");
	matrix_transpose(m, m);
	matrix_print(m, printElement);
	puts("");
	matrix_delete(m);

	m = matrix_new(6, 3);
	matrix_rand(m, generateRandomNumber);
	matrix_print(m, printElement);
	puts("");
	dst = matrix_transpose(m, NULL);
	matrix_print(dst, printElement);
	puts("");
	matrix_delete(m);
	matrix_delete(dst);



	return (0);
}

*/
