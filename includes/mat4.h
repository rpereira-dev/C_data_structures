#ifndef MAT4_H
# define MAT4_H

# include "common.h"
# include "vec3.h"
# include "vec4.h"

typedef struct	s_mat4 {
	float m00;
	float m01;
	float m02;
	float m03;

	float m10;
	float m11;
	float m12;
	float m13;

	float m20;
	float m21;
	float m22;
	float m23;

	float m30;
	float m31;
	float m32;
	float m33;
}				t_mat4;

/** create a new matrix */
t_mat4 * mat4_new(void);

/** delete the given matrix */
t_mat4 * mat4_delete(void);

/** copy */
t_mat4 * mat4_copy(t_mat4 * dst, t_mat4 * src);

/** set identity */
t_mat4 * mat4_identity(t_mat4 * dst);

/** set to zero */
t_mat4 * mat4_zero(t_mat4 * dst);

/** transpose */
t_mat4 * mat4_transpose(t_mat4 * dst, t_mat4 * src);

/** scale */
t_mat4 * mat4_scale(t_mat4 * dst, t_mat4 * mat, float f);

/** translate */
t_mat4 * mat4_translate(t_mat4 * dst, t_mat4 * mat, t_vec4 * translate);

/** rotate */
t_mat4 * mat4_rotate(t_mat4 * dst, t_mat4 * src, t_vec3 * axis, t_vec3 * rot);
t_mat4 * mat4_rotateX(t_mat4 * dst, t_mat4 * src, float angle);
t_mat4 * mat4_rotateY(t_mat4 * dst, t_mat4 * src, float angle);
t_mat4 * mat4_rotateZ(t_mat4 * dst, t_mat4 * src, float angle);
t_mat4 * mat4_rotateXYZ(t_mat4 * dst, t_mat4 * src, t_vec3 * rot);

/** transformation matrix */
t_mat4 * mat4_transformation(t_mat4 * dst, t_vec3 * translate, t_vec3 * rot, t_vec3 * scale);

/** determinant */
float mat4_determinant(t_mat4 * mat);

/** invert */
t_mat4 * mat4_invert(t_mat4 * dst, t_mat4 * src);

/** mult */
t_mat4 * mat4_mult(t_mat4 * dst, t_mat4 * left, t_mat4 * right);

/** transform vec4 */
t_vec4 * mat4_transform_vec4(t_vec4 * dst, t_mat4 * left, t_vec4 * right);

/** projections matrix bellow: */

/** orthographic matrix */
t_mat4 * mat4_orthographic(t_mat4 * dst, float left, float right, float bot, float top, float near, float far);

/** perspective matrix */
t_mat4 * mat4_perspective(t_mat4 * dst, float aspect, float fov, float near, float far);

#endif