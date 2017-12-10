/**
 *  This file is part of https://github.com/toss-dev/C_data_structures
 *
 *  It is under a GNU GENERAL PUBLIC LICENSE
 *
 *  This library is still in development, so please, if you find any issue, let me know about it on github.com
 *  PEREIRA Romain
 */

#ifndef BITMAP_H
# define BITMAP_H

# include "common.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

/**
 * the primordial type to be used as unit of the bit representation.
  	When dealing with huge bitmap, better use a large type like 'size_t',
	if dealing with small bitmaps, use 'BYTE'
*/
# ifndef BITMAP_UNIT
# 	define BITMAP_UNIT size_t
# endif
# define BITS_PER_UNIT (sizeof(BITMAP_UNIT) * 8)

typedef struct	s_bitmap {
	size_t	size;
}		t_bitmap;

/**
 * Create a new bitmap
 *
 * e.g: t_bitmap = image_new(16);
 * e.g: t_bitmap = image_new2(16, 16);
 * e.g: t_bitmap = image_new3(16, 16, 16);
 */
t_bitmap * bitmap_new(size_t width);
t_bitmap * bitmap_new2(size_t width, size_t height);
t_bitmap * bitmap_new3(size_t width, size_t height, size_t depth);

/**
 * get a copy of the bitmap, should be de-allocated using 'bitmap_delete()'
 */
t_bitmap * bitmap_clone(t_bitmap * image);

/**
 *  Delete DEFINETELY the bitmap from memory
 */
void bitmap_delete(t_bitmap * bitmap);


/**
 * get the bit, 1 if bit is set, 0 else
 */
BIT bitmap_get(t_bitmap * bitmap, size_t x);
BIT bitmap_get2(t_bitmap * bitmap, size_t x, size_t y, size_t sizeX);
BIT bitmap_get3(t_bitmap * bitmap, size_t x, size_t y, size_t z, size_t sizeX, size_t sizeY);

/**
 * set the bit
 */
void bitmap_set(t_bitmap * bitmap, size_t x);
void bitmap_set2(t_bitmap * bitmap, size_t x, size_t y, size_t sizeX);
void bitmap_set3(t_bitmap * bitmap, size_t x, size_t y, size_t z, size_t sizeX, size_t sizeY);

/**
 * unset the bit
 */
void bitmap_unset(t_bitmap * bitmap, size_t x);
void bitmap_unset2(t_bitmap * bitmap, size_t x, size_t y, size_t sizeX);
void bitmap_unset3(t_bitmap * bitmap, size_t x, size_t y, size_t z, size_t sizeX, size_t sizeY);

/**
 * bitmap or : returns (a | b) stored in 'dst', if 'dst' is NULL, 'dst' is allocated and returned
 */
t_bitmap * bitmap_or(t_bitmap * a, t_bitmap * b, t_bitmap * dst);

/**
 * bitmap and : returns (a & b) stored in 'dst', if 'dst' is NULL, 'dst' is allocated and returned
 */
t_bitmap * bitmap_and(t_bitmap * a, t_bitmap * b, t_bitmap * dst);

/**
 * bitmap xor : returns (a ^ b) stored in 'dst', if 'dst' is NULL, 'dst' is allocated and returned
 */
t_bitmap * bitmap_xor(t_bitmap * a, t_bitmap * b, t_bitmap * dst);

/**
 * bitmap not : returns !a processed on each BIT, stored in 'dst', if 'dst' is NULL, 'dst' is allocated and returned
 */
t_bitmap * bitmap_not(t_bitmap * a, t_bitmap * dst);

/** write the bitmap on the given flux */
void bitmap_printf(t_bitmap * bitmap, FILE * fd);

/** write the bitmap on the given file description with a buffer size of size 'bufsize' */
void bitmap_write(t_bitmap * bitmap, int fd, size_t bufsize);

# define BITMAP_ITER_START(B, V, I, J)\
	BITMAP_UNIT * __bits = (BITMAP_UNIT *) (B + 1);\
	size_t I;\
	for (I = 0 ; I < B->size ; I++) {\
		size_t J;\
		for (J = 0 ; J < BITS_PER_UNIT ; J++) {\
			BIT V = __bits[I] & (1 << J);
# define BITMAP_ITER_END(B, V, I, J)\
		}\
	}


# endif