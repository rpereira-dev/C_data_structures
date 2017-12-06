/**
 *  This file is part of https://github.com/toss-dev/C_data_structures
 *
 *  It is under a GNU GENERAL PUBLIC LICENSE
 *
 *  This library is still in development, so please, if you find any issue, let me know about it on github.com
 *  PEREIRA Romain
 */

#ifndef IMAGE_H
# define IMAGE_H

# include "common.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define IMAGE_RGBA (0)
# define IMAGE_ARGB (1)
# define IMAGE_RGB  (2)
# define IMAGE_BGR  (3)

# define IMAGE_COMPONENT_R (0)
# define IMAGE_COMPONENT_G (1)
# define IMAGE_COMPONENT_B (2)
# define IMAGE_COMPONENT_A (3)

BYTE g_bpp[] = {
	4, 4, 3, 3
};

/**
 *	RGBA
 *	ARGB
 *	RGB
 *	BGR
 */
BYTE g_components[4][4] = {
	{0, 1, 0, 2}, 	// r
	{1, 2, 1, 1},	// g
	{2, 3, 2, 0},	// b
	{3, 0, -1, -1}	// a
};

/** aliases */
# define IMAGE_RVB (IMAGE_RGB)
# define IMAGE_BVR (IMAGE_BGR)

typedef struct  s_image {
	size_t	width;
	size_t	height;
	BYTE 	format;
}               t_image;

/**
 * Create a new image
 * width 	: image width
 * height	: image width
 * format	: image format
 *
 * e.g: t_image = image_new(16, 16, IMAGE_RGBA);
 */
t_image * image_new(size_t width, size_t height, BYTE format);

/**
 * get raw pixels of the image
 */
BYTE * image_get(t_image * image);

/**
 * get a copy of the image an the pixels, should be de-allocated using 'image_delete()'
 */
t_image * image_clone(t_image * image);

/**
 *  Delete DEFINETELY the image from memory
 */
void image_delete(t_image * image);

/**
 *  get the red component from the image, at pixel (x, y)
 */
unsigned int image_get_r(t_image * image, size_t x, size_t y);

/**
 *  get the green component from the image, at pixel (x, y)
 */
unsigned int image_get_g(t_image * image, size_t x, size_t y);

/**
 *  get the blue component from the image, at pixel (x, y)
 */
unsigned int image_get_b(t_image * image, size_t x, size_t y);

/**
 *  get the alpha component from the image, at pixel (x, y)
 */
unsigned int image_get_a(t_image * image, size_t x, size_t y);

/**
 *  set the red component from the image, at pixel (x, y)
 */
void image_set_r(t_image * image, size_t x, size_t y, BYTE value);

/**
 *  set the green component from the image, at pixel (x, y)
 */
void image_set_g(t_image * image, size_t x, size_t y, BYTE value);

/**
 *  set the blue component from the image, at pixel (x, y)
 */
void image_set_b(t_image * image, size_t x, size_t y, BYTE value);

/**
 *  set the alpha component from the image, at pixel (x, y)
 */
void image_set_a(t_image * image, size_t x, size_t y, BYTE value);

# define IMAGE_ITER_START(I, X, Y, V)\
 {\
	BYTE * V = (BYTE *)(I + 1);\
	size_t X;\
	size_t Y;\
	for (Y = 0 ; Y < I->height ; Y++) {\
		for (X = 0 ; X < I->width ; X++) {
# define IMAGE_ITER_END(I, X, Y, V)\
			V += g_bpp[I->format];\
	}\
    }\
}

# endif
