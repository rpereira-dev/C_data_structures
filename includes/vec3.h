#ifndef VEC3_H
# define VEC3_H

# include "common.h"

/**
*	Implementation by PEREIRA Romain.
*
*	N.B:
*		- When a 't_vec3 * dst' parameter is required, it mean that the result will
*		  be stored at the 'dst' address
*		  If 'dst' is NULL, then a new vec3 is allocated and returned.
*/

typedef struct	s_vec3
{
	union {
		float x;
		float r;
		float pitch;
	};

	union {
		float y;
		float g;
		float yaw;
	};

	union {
		float z;
		float b;
		float roll;
	};
}				t_vec3;

/** create a new vec3 */
t_vec3 * vec3_new(void);

/** delete the vec3 */
void vec3_delete(t_vec3 * vec);

/** set the vec3 to 0 */
t_vec3 * vec3_zero(t_vec3 * dst);

/** set the vec3 values */
t_vec3 * vec3_set(t_vec3 * dst, float x, float y, float z);
t_vec3 * vec3_set3(t_vec3 * dst, t_vec3 * vec);

/** add two vec3 */
t_vec3 * vec3_add(t_vec3 * dst, t_vec3 * a, t_vec3 * b);

/** sub two vec3 */
t_vec3 * vec3_sub(t_vec3 * dst, t_vec3 * a, t_vec3 * b);

/** mult the vec3 by the given scalar */
t_vec3 * vec3_mult(t_vec3 * dst, t_vec3 * a, float scalar);
t_vec3 * vec3_mult3(t_vec3 * dst, t_vec3 * a, t_vec3 * b);

/** cross product */
t_vec3 * vec3_cross(t_vec3 * dst, t_vec3 * a, t_vec3 * b);

/** scale product */
float vec3_dot_product(t_vec3 * a, t_vec3 * b);

/** length */
float vec3_length_squared(t_vec3 * vec);
float vec3_length(t_vec3 * vec);

/** negate */
t_vec3 * vec3_negate(t_vec3 * dst, t_vec3 * src);

/** angle between two vec */
float vec3_angle(t_vec3 * a, t_vec3 * b);

/** mix the two vectors */
t_vec3 * vec3_mix(t_vec3 * dst, t_vec3 * a, t_vec3 * b, float ratio);

/** comparison */
int vec3_equals(t_vec3 * a, t_vec3 * b);

/** round vec3 */
t_vec3 * vec3_round(t_vec3 * dst, t_vec3 * vec, float decimals);

/** to string: return a string allocated with malloc() */
char * vec3_str(t_vec3 * vec);

#endif