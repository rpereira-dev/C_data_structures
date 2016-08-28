#ifndef VEC4_H
# define VEC4_H

# include "common.h"

typedef struct	s_vec4
{
	union {
		float x;
		float r;
	};

	union {
		float y;
		float g;
	};

	union {
		float z;
		float b;
	};

	union {
		float w;
		float a;
	};
}				t_vec4;

/** create a new vec4 */
t_vec4 * vec4_new(void);

/** delete the vec4 */
void vec4_delete(t_vec4 * vec);

/** set the vec4 to 0 */
t_vec4 * vec4_zero(t_vec4 * dst);

/** set the vec4 values */
t_vec4 * vec4_set(t_vec4 * dst, float x, float y, float z, float w);
t_vec4 * vec4_set4(t_vec4 * dst, t_vec4 * vec);

/** add two vec4 */
t_vec4 * vec4_add(t_vec4 * dst, t_vec4 * a, t_vec4 * b);

/** sub two vec4 */
t_vec4 * vec4_sub(t_vec4 * dst, t_vec4 * a, t_vec4 * b);

/** mult the vec4 by the given scalar */
t_vec4 * vec4_mult(t_vec4 * dst, t_vec4 * a, float scalar);
t_vec4 * vec4_mult3(t_vec4 * dst, t_vec4 * a, t_vec4 * b);

/** cross product */
t_vec4 * vec4_cross(t_vec4 * dst, t_vec4 * a, t_vec4 * b);

/** scale product */
float vec4_dot_product(t_vec4 * a, t_vec4 * b);

/** length */
float vec4_length_squared(t_vec4 * vec);
float vec4_length(t_vec4 * vec);

/** negate */
t_vec4 * vec4_negate(t_vec4 * dst, t_vec4 * src);

/** angle between two vec */
float vec4_angle(t_vec4 * a, t_vec4 * b);

/** mix the two vectors */
t_vec4 * vec4_mix(t_vec4 * dst, t_vec4 * a, t_vec4 * b, float ratio);

/** comparison */
int vec4_equals(t_vec4 * a, t_vec4 * b);

/** round vec4 */
t_vec4 * vec4_round(t_vec4 * dst, t_vec4 * vec, float decimals);

/** to string: return a string allocated with malloc() */
char * vec4_str(t_vec4 * vec);

#endif