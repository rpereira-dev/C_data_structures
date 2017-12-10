/**
 *  This file is part of https://github.com/toss-dev/C_data_structures
 *
 *  It is under a GNU GENERAL PUBLIC LICENSE
 *
 *  This library is still in development, so please, if you find any issue, let me know about it on github.com
 *  PEREIRA Romain
 */

# include "bitmap.h"

/**
 * Create a new bitmap
 *
 * e.g: t_bitmap = image_new(16);
 * e.g: t_bitmap = image_new2(16, 16);
 * e.g: t_bitmap = image_new3(16, 16, 16);
 */
t_bitmap * bitmap_new(size_t width) {
	size_t size = width / BITS_PER_UNIT + (width % BITS_PER_UNIT != 0);
	t_bitmap * bitmap = (t_bitmap *)malloc(sizeof(t_bitmap) + size);
	if (bitmap == NULL) {
		return (NULL);
	}
	bitmap->size = size;
	memset(bitmap + 1, 0, size);
	return (bitmap);
}

t_bitmap * bitmap_new2(size_t width, size_t height) {
	return (bitmap_new(width * height));
}

t_bitmap * bitmap_new3(size_t width, size_t height, size_t depth) {
	return (bitmap_new(width * height * depth));
}

/**
 * get a copy of the bitmap, should be de-allocated using 'bitmap_delete()'
 */
t_bitmap * bitmap_clone(t_bitmap * bitmap) {
	t_bitmap * copy = bitmap_new(bitmap->size * BITS_PER_UNIT);
	if (copy == NULL) {
		return (NULL);
	}
	memcpy(copy + 1, bitmap + 1, copy->size);
	return (copy);
}

/**
 *  Delete DEFINETELY the bitmap from memory
 */
void bitmap_delete(t_bitmap * bitmap) {
	bitmap->size = 0;
	free(bitmap);
}
static size_t bitmap_index2(size_t x, size_t y, size_t sizeX) {
	return (y * sizeX + x);
}

static size_t bitmap_index3(size_t x, size_t y, size_t z, size_t sizeX, size_t sizeY) {
	return ((y + z * sizeY) * sizeX + x);
}

/**
 * get the bit, 1 if bit is set, 0 else
 */
BIT bitmap_get(t_bitmap * bitmap, size_t x) {
	BITMAP_UNIT * bits = (BITMAP_UNIT *) (bitmap + 1);
	return (bits[x / BITS_PER_UNIT] & (1 << (x % BITS_PER_UNIT)) ? 1 : 0);
}

BIT bitmap_get2(t_bitmap * bitmap, size_t x, size_t y, size_t sizeX) {
	return (bitmap_get(bitmap, bitmap_index2(x, y, sizeX)));
}

BIT bitmap_get3(t_bitmap * bitmap, size_t x, size_t y, size_t z, size_t sizeX, size_t sizeY) {
	return (bitmap_get(bitmap, bitmap_index3(x, y, z, sizeX, sizeY)));
}

/**
 * set the bit
 */
void bitmap_set(t_bitmap * bitmap, size_t x) {
	BITMAP_UNIT * bits = (BITMAP_UNIT *) (bitmap + 1);
	*(bits + x / BITS_PER_UNIT) |= (1 << (x % BITS_PER_UNIT));
}

void bitmap_set2(t_bitmap * bitmap, size_t x, size_t y, size_t sizeX) {
	bitmap_set(bitmap, y * bitmap_index2(x, y, sizeX));
}

void bitmap_set3(t_bitmap * bitmap, size_t x, size_t y, size_t z, size_t sizeX, size_t sizeY) {
	bitmap_set(bitmap, bitmap_index3(x, y, z, sizeX, sizeY));
}

/**
 * unset the bit
 */
void bitmap_unset(t_bitmap * bitmap, size_t x) {
	BITMAP_UNIT * bits = (BITMAP_UNIT *) (bitmap + 1);
	*(bits + x / BITS_PER_UNIT) &= ~(1 << (x % BITS_PER_UNIT));
}

void bitmap_unset2(t_bitmap * bitmap, size_t x, size_t y, size_t sizeX) {
	bitmap_unset(bitmap, y * bitmap_index2(x, y, sizeX));
}

void bitmap_unset3(t_bitmap * bitmap, size_t x, size_t y, size_t z, size_t sizeX, size_t sizeY) {
	bitmap_unset(bitmap, bitmap_index3(x, y, z, sizeX, sizeY));
}

/**
 * bitmap or : returns (a | b) stored in 'dst', if 'dst' is NULL, 'dst' is allocated and returned
 */
t_bitmap * bitmap_or(t_bitmap * a, t_bitmap * b, t_bitmap * dst) {
	if (a->size != b->size) {
		return (0);
	}
	if (dst == NULL) {
		dst = bitmap_new(a->size * BITS_PER_UNIT);
		if (dst == NULL) {
			return (NULL);
		}
	} else if (dst->size != a->size) {
		return (NULL);
	}
	BITMAP_UNIT * left = (BITMAP_UNIT *) (a + 1);
	BITMAP_UNIT * right = (BITMAP_UNIT *) (b + 1);
	BITMAP_UNIT * res = (BITMAP_UNIT *) (dst + 1);
	size_t i;
	for (i = 0 ; i < a->size; i++) {
		res[i] = left[i] | right[i];
	}
	return (dst);
}

/**
 * bitmap and : returns (a & b) stored in 'dst', if 'dst' is NULL, 'dst' is allocated and returned
 */
t_bitmap * bitmap_and(t_bitmap * a, t_bitmap * b, t_bitmap * dst) {
	if (a->size != b->size) {
		return (0);
	}
	if (dst == NULL) {
		dst = bitmap_new(a->size * BITS_PER_UNIT);
		if (dst == NULL) {
			return (NULL);
		}
	} else if (dst->size != a->size) {
		return (NULL);
	}
	BITMAP_UNIT * left = (BITMAP_UNIT *) (a + 1);
	BITMAP_UNIT * right = (BITMAP_UNIT *) (b + 1);
	BITMAP_UNIT * res = (BITMAP_UNIT *) (dst + 1);
	size_t i;
	for (i = 0 ; i < a->size; i++) {
		res[i] = left[i] & right[i];
	}
	return (dst);
}

/**
 * bitmap xor : returns (a ^ b) stored in 'dst', if 'dst' is NULL, 'dst' is allocated and returned
 */
t_bitmap * bitmap_xor(t_bitmap * a, t_bitmap * b, t_bitmap * dst) {
	if (a->size != b->size) {
		return (0);
	}
	if (dst == NULL) {
		dst = bitmap_new(a->size * BITS_PER_UNIT);
		if (dst == NULL) {
			return (NULL);
		}
	} else if (dst->size != a->size) {
		return (NULL);
	}
	BITMAP_UNIT * left = (BITMAP_UNIT *) (a + 1);
	BITMAP_UNIT * right = (BITMAP_UNIT *) (b + 1);
	BITMAP_UNIT * res = (BITMAP_UNIT *) (dst + 1);
	size_t i;
	for (i = 0 ; i < a->size; i++) {
		res[i] = left[i] ^ right[i];
	}
	return (dst);
}

/**
 * bitmap not : returns !a processed on each BIT, stored in 'dst', if 'dst' is NULL, 'dst' is allocated and returned
 */
t_bitmap * bitmap_not(t_bitmap * a, t_bitmap * dst) {
	if (dst == NULL) {
		dst = bitmap_new(a->size * BITS_PER_UNIT);
		if (dst == NULL) {
			return (NULL);
		}
	} else if (dst->size != a->size) {
		return (NULL);
	}
	BITMAP_UNIT * bytes = (BITMAP_UNIT *) (a + 1);
	BITMAP_UNIT * res = (BITMAP_UNIT *) (dst + 1);
	size_t i;
	BITMAP_UNIT ones = ~(0);
	for (i = 0 ; i < a->size; i++) {
		res[i] = bytes[i] ^ ones;
	}
	return (dst);
}
/** write the bitmap on the given flux */
void bitmap_printf(t_bitmap * bitmap, FILE * fd) {
	BITMAP_ITER_START(bitmap, bit, i, j) {
		fprintf(fd, "%c", bit ? '1' : '0');
	}
	BITMAP_ITER_END(bitmap, bit, i, j);
}

/** write the bitmap on the given file description with a buffer size of size 'bufsize' */
void bitmap_write(t_bitmap * bitmap, int fd, size_t bufsize) {
	char buf[bufsize];
	size_t k = 0;
	BITMAP_ITER_START(bitmap, bit, i, j) {
		buf[k++] = bit ? '1' : '0';
		if (k >= bufsize) {
			write(fd, buf, bufsize);
			k = 0;
		}
	}
	BITMAP_ITER_END(bitmap, bit, i, j);
}





/*
int main() {
	t_bitmap * bitmap = bitmap_new(16);
	bitmap_set(bitmap, 1);
	bitmap_write(bitmap, 1, 16);
	bitmap_delete(bitmap);
	return (0);
}*/
