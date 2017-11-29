/**
 *	This file is part of https://github.com/toss-dev/C_data_structures
 *
 *	It is under a GNU GENERAL PUBLIC LICENSE
 *
 *	This library is still in development, so please, if you find any issue, let me know about it on github.com
 *	PEREIRA Romain
 */

#ifndef MATRIX_H
# define MATRIX_H

# include "common.h"

# define T int

typedef struct  s_matrix {
	size_t n;
	size_t m;
}               t_matrix;

/**
 *  create a new matrix
 */
t_matrix * matrix_new(size_t n, size_t m);

/**
 *  delete the matrix from the heap
 */
void matrix_delete(t_matrix * matrix);

/** get element address */
T * matrix_node(t_matrix * matrix, size_t i, size_t j);

/**
 *  get the matrix value
 */
T matrix_get(t_matrix * matrix, size_t i, size_t j);

/**
 * set the matrix value
 */
void matrix_set(t_matrix * matrix, size_t i, size_t j, T value);

/**
 * print the formatted matrix, on the standart output (fd 1)
 */
void matrix_print(t_matrix * matrix, void (*printElement)(t_matrix *, size_t, size_t));


/**
 * set the matrix to identity
 */
void matrix_identity(t_matrix * matrix);

/**
 * generete a random matrix
 */
void matrix_rand(t_matrix * dst, T (*rng)());

/**
 * matrix addition
 */
t_matrix * matrix_add(t_matrix * left, t_matrix * right, T (* addElement)(T, T), t_matrix * dst);	

/**
 * matrix substraction
 */
t_matrix * matrix_sub(t_matrix * left, t_matrix * right, T (* subElement)(T, T), t_matrix * dst);	

/**
 * matrix multiplication: if dst is NULL, it is allocated and returned,
 * if dst doesn't match sizes, the multiplication is cancelled
 */
t_matrix * matrix_mult(t_matrix * left, t_matrix * right, T (*addElement)(T, T), T (*multElement)(T, T), t_matrix * dst);

/**
 * create the transpose of the given matrix
 */
t_matrix * matrix_transpose(t_matrix * matrix, t_matrix * dst);

/**
 * get the matrix trace
 */
T matrix_trace(t_matrix * matrix, T (*addElement)(T, T));

#endif
