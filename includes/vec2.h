#ifndef VEC2_H
# define VEC2_H

# include "common.h"

typedef struct	s_vec2
{
	union {
		float x;
		float uvx;
	};

	union {
		float y;
		float uvy;
	};
}				t_vec2;

/** create a new vec2 */
t_vec2 * vec2_new(void);

/** delete the vec2 */
void vec2_delete(t_vec2 * vec);

/** set the vec2 to 0 */
t_vec2 * vec2_zero(t_vec2 * dst);

/** set the vec2 values */
t_vec2 * vec2_set(t_vec2 * dst, float x, float y);
t_vec2 * vec2_set2(t_vec2 * dst, t_vec2 * vec);

/** add two vec2 */
t_vec2 * vec2_add(t_vec2 * dst, t_vec2 * a, t_vec2 * b);

/** sub two vec2 */
t_vec2 * vec2_sub(t_vec2 * dst, t_vec2 * a, t_vec2 * b);

/** mult the vec2 by the given scalar */
t_vec2 * vec2_mult(t_vec2 * dst, t_vec2 * a, float scalar);
t_vec2 * vec2_mult2(t_vec2 * dst, t_vec2 * a, t_vec2 * b);

/** cross product */
t_vec2 * vec2_cross(t_vec2 * dst, t_vec2 * a, t_vec2 * b);

/** scale product */
float vec2_dot_product(t_vec2 * a, t_vec2 * b);

/** length */
float vec2_length_squared(t_vec2 * vec);
float vec2_length(t_vec2 * vec);

/** negate */
t_vec2 * vec2_negate(t_vec2 * dst, t_vec2 * src);

/** angle between two vec */
float vec2_angle(t_vec2 * a, t_vec2 * b);

/** mix the two vectors */
t_vec2 * vec2_mix(t_vec2 * dst, t_vec2 * a, t_vec2 * b, float ratio);

/** comparison */
int vec2_equals(t_vec2 * a, t_vec2 * b);

/** round vec2 */
t_vec2 * vec2_round(t_vec2 * dst, t_vec2 * vec, float decimals);

/** to string: return a string allocated with malloc() */
char * vec2_str(t_vec2 * vec);

#endif