/**
 *  This file is part of https://github.com/toss-dev/C_data_structures
 *
 *  It is under a GNU GENERAL PUBLIC LICENSE
 *
 *  This library is still in development, so please, if you find any issue, let me know about it on github.com
 *  PEREIRA Romain
 */

# include "image.h"


extern BYTE g_bpp[];
extern BYTE g_components[4][4];

/**
 * Create a new image
 * width 	: image width
 * height	: image width
 * format	: image format
 *
 * e.g: t_image = image_new(16, 16, IMAGE_RGBA);
 */
t_image * image_new(size_t width, size_t height, BYTE format) {
	size_t size = sizeof(t_image) + width * height * g_bpp[format] * sizeof(BYTE);
	t_image * image = (t_image *) malloc(size);
	if (image == NULL) {
		return (NULL);
	}
	image->width = width;
	image->height = height;
	image->format = format;
	return (image);
}

/**
 * get a copy of the image an the pixels, should be de-allocated using 'image_delete()'
 */
t_image * image_clone(t_image * img) {
	size_t size = sizeof(t_image) + img->width * img->height * g_bpp[img->format] * sizeof(BYTE);
	t_image * copy = (t_image *) malloc(size);
	if (copy == NULL) {
		return (NULL);
	}
	memcpy(copy, img, size);
	return (copy);
}

/**
 * get raw pixels of the image
 */
BYTE * image_get(t_image * image) {
	return ((BYTE *) (image + 1));
}

/**
 *  Delete DEFINETELY the image from memory
 */
void image_delete(t_image * image) {
	image->width = 0;
	image->height = 0;
	free(image);
}

/** address of the component */
static BYTE * image_component(t_image * image, size_t x, size_t y, BYTE component) {
	BYTE * values = (BYTE *) (image + 1);
	size_t addr = (y * image->width + x) * g_bpp[image->format] + g_components[component][image->format];
	return (values + addr);
}

/**
 *  get the red component from the image, at pixel (x, y)
 */
unsigned int image_get_r(t_image * image, size_t x, size_t y) {
	return (*(image_component(image, x, y, IMAGE_COMPONENT_R)));
}

/**
 *  get the green component from the image, at pixel (x, y)
 */
unsigned int image_get_g(t_image * image, size_t x, size_t y) {
	return (*(image_component(image, x, y, IMAGE_COMPONENT_G)));
}

/**
 *  get the blue component from the image, at pixel (x, y)
 */
unsigned int image_get_b(t_image * image, size_t x, size_t y) {
	return (*(image_component(image, x, y, IMAGE_COMPONENT_B)));
}

/**
 *  get the alpha component from the image, at pixel (x, y)
 */
unsigned int image_get_a(t_image * image, size_t x, size_t y) {
	return (*(image_component(image, x, y, IMAGE_COMPONENT_A)));
}

/**
 *  set the red component from the image, at pixel (x, y)
 */
void image_set_r(t_image * image, size_t x, size_t y, BYTE value) {
	*(image_component(image, x, y, IMAGE_COMPONENT_R)) = value;
}

/**
 *  get the green component from the image, at pixel (x, y)
 */
void image_set_g(t_image * image, size_t x, size_t y, BYTE value) {
	*(image_component(image, x, y, IMAGE_COMPONENT_G)) = value;
}

/**
 *  get the green component from the image, at pixel (x, y)
 */
void image_set_b(t_image * image, size_t x, size_t y, BYTE value) {
	*(image_component(image, x, y, IMAGE_COMPONENT_B)) = value;
}

/**
 *  get the green component from the image, at pixel (x, y)
 */
void image_set_a(t_image * image, size_t x, size_t y, BYTE value) {
	*(image_component(image, x, y, IMAGE_COMPONENT_A)) = value;
}

/**
 * square blur effect
 *	'src':
 *	'dst': can be NULL
 *	'depth': square of 2 * depth + 1 size
 *
 */
t_image * image_blur(t_image * image, t_image * dst, size_t depth) {
	if (dst == NULL) {
		dst = image_new(image->width, image->height, image->format);
	} else if (dst->width != image->width || dst->height != image->height) {
		return (NULL);
	}
	BYTE allocated = 0;
	if (image == dst) {
		dst = image_new(image->width, image->height, image->format);
		allocated = 1;
	}

	size_t x, y, dx, dy;
	size_t total = (2 * depth + 1) * (2 * depth + 1);
	for (y = 0 ; y < image->height ; y++) {
		for (x = 0 ; x < image->width ; x++) {
			unsigned short sum = 0;
			for (dx = -depth ; dx <= depth ; dx++) {
				for (dy = -depth ; dy <= depth ; dy++) {
					//TODO : depending on format
				}
			}
			BYTE value = (BYTE) (sum / total);
			(void)value;
			//TODO : set pixel
		}
	}

	if (allocated) {
		image_delete(dst);
		return (image);
	}
	return (dst);
}
/*
int main() {
	t_image * img = image_new(2, 2, IMAGE_RGBA);
	image_set_r(img, 0, 0, 255);
	image_set_g(img, 0, 0, 255);
	image_set_b(img, 0, 0, 255);
	image_set_a(img, 0, 0, 255);
	IMAGE_ITER_START(img, x, y, pixel) {
		printf("%hhu:%hhu:%hhu:%hhu\n", pixel[0], pixel[1], pixel[2], pixel[3]);
	}
	IMAGE_ITER_END(img, x, y, pixel);

	image_delete(img);
}
*/
