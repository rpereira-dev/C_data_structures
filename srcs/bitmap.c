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
 * set every bits to zero
 */
void bitmap_zeroes(t_bitmap * bitmap) {
	memset(bitmap + 1, 0, bitmap->size * sizeof(BITMAP_UNIT));
}

/**
 * Create a new bitmap
 *
 * e.g: t_bitmap = bitmap_new(16);
 * e.g: t_bitmap = bitmap_new2(16, 16);
 * e.g: t_bitmap = bitmap_new3(16, 16, 16);
 */
t_bitmap * bitmap_new(size_t sizeX) {
	size_t size = sizeX / BITS_PER_UNIT + (sizeX % BITS_PER_UNIT != 0);
	t_bitmap * bitmap = (t_bitmap *)malloc(sizeof(t_bitmap) + size * sizeof(BITMAP_UNIT));
	if (bitmap == NULL) {
		return (NULL);
	}
	bitmap->size = size;
	return (bitmap);
}

t_bitmap * bitmap_new2(size_t sizeX, size_t sizeY) {
	return (bitmap_new(sizeX * sizeY));
}

t_bitmap * bitmap_new3(size_t sizeX, size_t sizeY, size_t sizeZ) {
	return (bitmap_new(sizeX * sizeY * sizeZ));
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
	return (bits[x / BITS_PER_UNIT] & ((BITMAP_UNIT)1 << (x % BITS_PER_UNIT)) ? (BIT)1 : (BIT)0);
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
	*(bits + x / BITS_PER_UNIT) |= ((BITMAP_UNIT)1 << (x % BITS_PER_UNIT));
}

void bitmap_set2(t_bitmap * bitmap, size_t x, size_t y, size_t sizeX) {
	bitmap_set(bitmap, bitmap_index2(x, y, sizeX));
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
	bitmap_unset(bitmap, bitmap_index2(x, y, sizeX));
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
void bitmap_printf(t_bitmap * bitmap, char set, char unset, FILE * fd) {
	BITMAP_ITER_START(bitmap, bit, i, j) {
		fprintf(fd, "%c", bit ? set : unset);
	}
	BITMAP_ITER_END(bitmap, bit, i, j);
}

void bitmap_printf2(t_bitmap * bitmap, char set, char unset, FILE * fd, size_t sizeX) {
	size_t countX = 0;
	BITMAP_ITER_START(bitmap, bit, i, j) {
		fprintf(fd, "%c", bit ? set : unset);
		if (++countX % sizeX == 0) {
			fprintf(fd, "\n");
			countX = 0;
		}
	}
	BITMAP_ITER_END(bitmap, bit, i, j);
}

void bitmap_printf3(t_bitmap * bitmap, char set, char unset, FILE * fd, size_t sizeX, size_t sizeY) {
	size_t countX = 0;
	size_t countY = 0;
	BITMAP_ITER_START(bitmap, bit, i, j) {
		fprintf(fd, "%c", bit ? set : unset);
		if (++countX % sizeX == 0) {
			countX = 0;
			fprintf(fd, "\n");
			if (++countY % sizeY == 0) {
				countY = 0;
				fprintf(fd, "\n");
			}
		}
	}
	BITMAP_ITER_END(bitmap, bit, i, j);
}

/** write the bitmap on the given file description with a buffer size of size 'bufsize' */
int bitmap_write(t_bitmap * bitmap, char set, char unset, int fd, size_t bufsize) {
	if (bufsize == 0) {
		return (-1);
	}
	char buf[bufsize];
	size_t k = 0;
	BITMAP_ITER_START(bitmap, bit, i, j) {
		buf[k++] = bit ? set : unset;
		if (k == bufsize) {
			if (write(fd, buf, bufsize)  < 0) {
				return (-1);
			}
			k = 0;
		}
	}
	BITMAP_ITER_END(bitmap, bit, i, j);
	buf[k++] = '\n';
	if (k > 0) {
		if (write(fd, buf, k) < 0) {
			return (-1);
		}
	}
	return (1);
}

int bitmap_write2(t_bitmap * bitmap, char set, char unset, int fd, size_t bufsize, size_t sizeX) {
	if (bufsize == 0) {
		return (-1);
	}
	char buf[bufsize];
	size_t k = 0;
	size_t countX = 0;
	BITMAP_ITER_START(bitmap, bit, i, j) {
		buf[k++] = bit ? set : unset;
		if (k == bufsize) {
			if (write(fd, buf, bufsize)  < 0) {
				return (-1);
			}
			k = 0;
		}
		if (++countX % sizeX == 0) {
			countX = 0;
			buf[k++] = '\n';
			if (k == bufsize) {
				if (write(fd, buf, bufsize)  < 0) {
					return (-1);
				}
				k = 0;
			}
		}
	}
	BITMAP_ITER_END(bitmap, bit, i, j);
	if (k > 0) {
		if (write(fd, buf, k) < 0) {
			return (-1);
		}
	}
	return (1);
}

int bitmap_write3(t_bitmap * bitmap, char set, char unset, int fd, size_t bufsize, size_t sizeX, size_t sizeY) {
	if (bufsize == 0) {
		return (-1);
	}
	char buf[bufsize];
	size_t k = 0;
	size_t countX = 0;
	size_t countY = 0;
	BITMAP_ITER_START(bitmap, bit, i, j) {
		buf[k++] = bit ? set : unset;
		if (k == bufsize) {
			if (write(fd, buf, bufsize)  < 0) {
				return (-1);
			}
			k = 0;
		}
		if (++countX % sizeX == 0) {
			countX = 0;
			buf[k++] = '\n';
			if (k == bufsize) {
				if (write(fd, buf, bufsize)  < 0) {
					return (-1);
				}
				k = 0;
			}
			if (++countY % sizeY == 0) {
				countY = 0;
				buf[k++] = '\n';
				if (k == bufsize) {
					if (write(fd, buf, bufsize)  < 0) {
						return (-1);
					}
					k = 0;
				}
			}
		}
	}
	BITMAP_ITER_END(bitmap, bit, i, j);
	if (k > 0) {
		if (write(fd, buf, k) < 0) {
			return (-1);
		}
	}
	return (1);
}


t_bitmap * bitmap_conway(t_bitmap * bitmap, t_bitmap * dst) {
	size_t x;
	
	if (bitmap == dst || dst == NULL) {
		dst = bitmap_new(bitmap->size * BITS_PER_UNIT);
	} else if (bitmap->size != dst->size) {
		return (NULL);
	}
	bitmap_zeroes(dst);
	size_t end = bitmap->size * BITS_PER_UNIT - 1;
	for (x = 1 ; x < end ; x++) {
		if (bitmap_get(bitmap, x - 1) ^ bitmap_get(bitmap, x + 1)) {
			bitmap_set(dst, x);
		}
	}
	return (dst);
}

t_bitmap * bitmap_conway2(t_bitmap * bitmap, t_bitmap * dst, size_t width, size_t height) {
	if (bitmap == dst || dst == NULL) {
		dst = bitmap_new(bitmap->size * BITS_PER_UNIT);
	} else if (bitmap->size != dst->size) {
		return (NULL);
	}
	bitmap_zeroes(dst);

	size_t x, y;
	size_t endx = width - 1;
	size_t endy = height - 1;
	for (x = 1 ; x < endx ; x++) {
		for (y = 1 ; y < endy ; y++) {
			int dx, dy;
			int c = 0;
			for (dx = -1; dx <= 1 ; dx++) {
				for (dy = -1; dy <= 1 ; dy++) {
					if (dx == 0 && dy == 0) {
						continue ;
					}
					c += bitmap_get2(bitmap, x + dx, y + dy, width);
				}
			}
			if (c == 2) {
				if (bitmap_get2(bitmap, x, y, width)) {
					bitmap_set2(dst, x, y, width);
				}
			} else if (c >= 3) {
				bitmap_set2(dst, x, y, width);
			} else {
				bitmap_unset2(dst, x, y, width);
			}
		}
	}
	return (dst);
}
/*
void clear_screen() {
	system("clear");
} 
int main() {

	{
		//the code bellow generate a serpinsky fractal with a height of 96
		size_t h = 96;
		size_t w = h * 2;
		size_t x = w / 2 - 1;
		size_t bufsize = 2048;
		char set = 'x';
		char unset = '.';
		t_bitmap * bitmap = bitmap_new(w);
		bitmap_set(bitmap, x);
	
		size_t i;
		bitmap_write(bitmap, set, unset, 1, bufsize);
		t_bitmap * swap = bitmap_clone(bitmap);
		for (i = 0 ; i < h ; i++) {
			if (i % 2 == 0) {
				bitmap_conway(bitmap, swap);
				bitmap_write(swap, set, unset, 1, bufsize);
			} else {
				bitmap_conway(swap, bitmap);
				bitmap_write(bitmap, set, unset, 1, bufsize);
			}
		}

		bitmap_delete(bitmap);
		puts("\n");
	}


	{
		//the code bellow is a simulation of original conway game of life
		size_t w = 32;
		size_t h = 32;
		size_t bufsize = 2048;
		char set = 'x';
		char unset = '.';
		t_bitmap * bitmap = bitmap_new2(w, h);
		
		size_t cx = w / 2;
		size_t cy = h / 2;
		bitmap_set2(bitmap, cx, cy, w);
		bitmap_set2(bitmap, cx - 1, cy, w);
		bitmap_set2(bitmap, cx + 1, cy, w);
		bitmap_set2(bitmap, cx, cy - 1, w);
		bitmap_set2(bitmap, cx, cy + 1, w);

		size_t i = 0;
		bitmap_write2(bitmap, set, unset, 1, bufsize, w);
		t_bitmap * swap = bitmap_clone(bitmap);
		do {
			clear_screen();
			if (i % 2 == 0) {
				bitmap_conway2(bitmap, swap, w, h);
				bitmap_write2(swap, set, unset, 1, bufsize, w);
			} else {
				bitmap_conway2(swap, bitmap, w, h);
				bitmap_write2(bitmap, set, unset, 1, bufsize, w);
			}
			++i;
			usleep(100000);
		} while (i < h);
		bitmap_delete(bitmap);
		puts("\n");
	}	

	return (0);
}*/
