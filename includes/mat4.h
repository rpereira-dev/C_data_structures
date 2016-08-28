#ifndef MAT4_H
# define MAT4_H

# include "common.h"

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

#endif