#ifndef MATH3D_H
#define MATH3D_H
#include <math.h>
#include <malloc.h>
#include <GL/glew.h>


typedef enum m3dType
{
	MAT4,
	MAT3,
	MAT2,
	VEC4,
	VEC3,
	VEC2,
} m3dType;

typedef struct const_size_arrays
{
	GLfloat vec4[4];
	GLfloat vec3[3];
	GLfloat vec2[2];
	GLfloat mat4[16];
	GLfloat mat3[9];
	GLfloat mat2[4];
	m3dType type;
} const_size_arrays;

static inline GLfloat radians(GLfloat deg) {return deg * 0.0174533f;};
static inline GLfloat degrees(GLfloat rad) {return rad * 57.2958f;};
static inline GLfloat sqr(GLfloat n) {return n * n;};

typedef struct mat4_t
{
	GLfloat m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33;
	m3dType type;
	GLint size;
} mat4_t;

typedef struct mat3_t
{
	GLfloat m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22;
	m3dType type;
	GLint size;
} mat3_t;

typedef struct mat2_t
{
	GLfloat m00, m01,
			m10, m11;
	m3dType type;
	GLint size;
			
} mat2_t;

typedef struct vec4_t {
	GLfloat x, y, z, w;
	m3dType type;
} vec4_t;

typedef struct vec3_t {
	GLfloat x, y, z;
	m3dType type;
} vec3_t;

typedef struct vec2_t {
	GLfloat x, y;
	m3dType type;
} vec2_t;

static inline vec4_t vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) { return (vec4_t){x, y, z, w, VEC4}; };
static inline vec3_t vec3(GLfloat x, GLfloat y, GLfloat z) { return (vec3_t){x, y, z, VEC3}; };
static inline vec2_t vec2(GLfloat x, GLfloat y) { return (vec2_t){x, y, VEC2}; };

static inline GLfloat v4_length(vec4_t vec) { return sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.w*vec.w); };
static inline GLfloat v3_length(vec3_t vec) { return sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);};
static inline GLfloat v2_length(vec2_t vec) { return sqrtf(vec.x*vec.x + vec.y*vec.y);};

static inline vec4_t v4_add(vec4_t a, vec4_t b) { return (vec4_t){a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w, VEC4};};
static inline vec3_t v3_add(vec3_t a, vec3_t b) { return (vec3_t){a.x+b.x, a.y+b.y, a.z+b.z, VEC3};};
static inline vec2_t v2_add(vec2_t a, vec2_t b) { return (vec2_t){a.x+b.x, a.y+b.y, VEC2};};

static inline vec4_t v4_sub(vec4_t a, vec4_t b) { return (vec4_t){a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w, VEC4};};
static inline vec3_t v3_sub(vec3_t a, vec3_t b) { return (vec3_t){a.x-b.x, a.y-b.y, a.z-b.z, VEC3};};
static inline vec2_t v2_sub(vec2_t a, vec2_t b) { return (vec2_t){a.x-b.x, a.y-b.y, VEC2};};

static inline vec4_t v4_mul(vec4_t a, vec4_t b) { return (vec4_t){a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w, VEC4};};
static inline vec3_t v3_mul(vec3_t a, vec3_t b) { return (vec3_t){a.x*b.x, a.y*b.y, a.z*b.z, VEC3};};
static inline vec2_t v2_mul(vec2_t a, vec2_t b) { return (vec2_t){a.x*b.x, a.y*b.y, VEC2};};

static inline vec4_t v4_div(vec4_t a, vec4_t b) { return (vec4_t){a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w, VEC4};};
static inline vec3_t v3_div(vec3_t a, vec3_t b) { return (vec3_t){a.x/b.x, a.y/b.y, a.z/b.z, VEC3};};
static inline vec2_t v2_div(vec2_t a, vec2_t b) { return (vec2_t){a.x/b.x, a.y/b.y, VEC2};};

static inline vec4_t v4_adds(vec4_t a, GLfloat b) { return (vec4_t){a.x+b, a.y+b, a.z+b, a.w+b, VEC4};};
static inline vec3_t v3_adds(vec3_t a, GLfloat b) { return (vec3_t){a.x+b, a.y+b, a.z+b, VEC3};};
static inline vec2_t v2_adds(vec2_t a, GLfloat b) { return (vec2_t){a.x+b, a.y+b, VEC2};};

static inline vec4_t v4_subs(vec4_t a, GLfloat b) { return (vec4_t){a.x-b, a.y-b, a.z-b, a.w-b, VEC4};};
static inline vec3_t v3_subs(vec3_t a, GLfloat b) { return (vec3_t){a.x-b, a.y-b, a.z-b, VEC3};};
static inline vec2_t v2_subs(vec2_t a, GLfloat b) { return (vec2_t){a.x-b, a.y-b, VEC2};};

static inline vec4_t v4_muls(vec4_t a, GLfloat b) { return (vec4_t){a.x*b, a.y*b, a.z*b, a.w*b, VEC4};};
static inline vec3_t v3_muls(vec3_t a, GLfloat b) { return (vec3_t){a.x*b, a.y*b, a.z*b, VEC3};};
static inline vec2_t v2_muls(vec2_t a, GLfloat b) { return (vec2_t){a.x*b, a.y*b, VEC2};};

static inline vec4_t v4_divs(vec4_t a, GLfloat b) { return (vec4_t){a.x/b, a.y/b, a.z/b, a.w/b, VEC4};};
static inline vec3_t v3_divs(vec3_t a, GLfloat b) { return (vec3_t){a.x/b, a.y/b, a.z/b, VEC3};};
static inline vec2_t v2_divs(vec2_t a, GLfloat b) { return (vec2_t){a.x/b, a.y/b, VEC2};};

static inline vec4_t v4_norm(vec4_t a) { return (vec4_t){a.x/v4_length(a), a.y/v4_length(a), a.z/v4_length(a), a.w/v4_length(a), VEC4};};
static inline vec3_t v3_norm(vec3_t a) { return (vec3_t){a.x/v3_length(a), a.y/v3_length(a), a.z/v3_length(a), VEC3};};
static inline vec2_t v2_norm(vec2_t a) { return (vec2_t){a.x/v2_length(a), a.y/v2_length(a), VEC2};};

static inline const_size_arrays v4_array(vec4_t a) 
{
	const_size_arrays ret;
	ret.type = a.type;
	ret.vec4[0] = a.x;
	ret.vec4[1] = a.y;
	ret.vec4[2] = a.z;
	ret.vec4[3] = a.w;
	return ret;
};

static inline const_size_arrays v3_array(vec3_t a) 
{
	const_size_arrays ret;
	ret.type = a.type;
	ret.vec3[0] = a.x;
	ret.vec3[1] = a.y;
	ret.vec3[2] = a.z;
	return ret;
};

static inline const_size_arrays v2_array(vec2_t a) 
{
	const_size_arrays ret;
	ret.type = a.type;
	ret.vec2[0] = a.x;
	ret.vec2[1] = a.y;
	return ret;
};

static inline GLfloat v4_dot(vec4_t a, vec4_t b) { return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w; };
static inline GLfloat v3_dot(vec3_t a, vec3_t b) { return a.x*b.x+a.y*b.y+a.z*b.z; };
static inline GLfloat v2_dot(vec2_t a, vec2_t b) { return a.x*b.x+a.y*b.y; };

static inline vec4_t v4_cross(vec4_t a, vec4_t b) 
{
	return (vec4_t){ a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x, 1.0, VEC4 };
};
static inline vec3_t v3_cross(vec3_t a, vec3_t b) 
{
	/*
	 *|	i	j	k |
	 *|	x1	y1	z1|		|y1	z1|		|x1	z1|		|x1	y1|
	 *|	x2	y2	z2|	=	|y2	z2|	-	|x2	z2|	+	|x2	y2|
	 */
	return (vec3_t){ a.y*b.z-a.z*b.y, -( a.x*b.z-a.z*b.x), a.x*b.y-a.y*b.x, VEC3};
};

static inline vec2_t v2_cross(vec2_t a) 
{
	return (vec2_t){a.y, -a.x, VEC2};
};

static inline mat4_t mat4(GLfloat a)
{
	return (mat4_t){
		a, 0, 0, 0,
		0, a, 0, 0,
		0, 0, a, 0,
		0, 0, 0, 1.f,
		MAT4,
		16*sizeof(GLfloat)
	};
}

static inline mat3_t mat3(GLfloat a)
{
	return (mat3_t){
		a, 0, 0,
		0, a, 0,
		0, 0, a,
		MAT3,
		9*sizeof(GLfloat)
	};
}

static inline mat2_t mat2(GLfloat a)
{
	return (mat2_t){
		a, 0,
		0, a,
		MAT2,
		4*sizeof(GLfloat)
	};
}

static inline mat4_t m4_mul(mat4_t a, mat4_t b)
{
	return (mat4_t){

		a.m00*b.m00 + a.m01*b.m10 + a.m02*b.m20 + a.m03*b.m30, 
		a.m00*b.m01 + a.m01*b.m11 + a.m02*b.m21 + a.m03*b.m31, 
		a.m00*b.m02 + a.m01*b.m12 + a.m02*b.m22 + a.m03*b.m32, 
		a.m00*b.m03 + a.m01*b.m13 + a.m02*b.m23 + a.m03*b.m33, 


		a.m10*b.m00 + a.m11*b.m10 + a.m12*b.m20 + a.m13*b.m30, 
		a.m10*b.m01 + a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31, 
		a.m10*b.m02 + a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32, 
		a.m10*b.m03 + a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33, 


		a.m20*b.m00 + a.m21*b.m10 + a.m22*b.m20 + a.m23*b.m30, 
		a.m20*b.m01 + a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31, 
		a.m20*b.m02 + a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32, 
		a.m20*b.m03 + a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33, 


		a.m30*b.m00 + a.m31*b.m10 + a.m32*b.m20 + a.m33*b.m30, 
		a.m30*b.m01 + a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31, 
		a.m30*b.m02 + a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32, 
		a.m30*b.m03 + a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33, 

		MAT4,
		16*sizeof(GLfloat)
	};
}

static inline mat3_t m3_mul(mat3_t a, mat3_t b)
{
	return (mat3_t){

		a.m00*b.m00 + a.m01*b.m10 + a.m02*b.m20, 
		a.m00*b.m01 + a.m01*b.m11 + a.m02*b.m21, 
		a.m00*b.m02 + a.m01*b.m12 + a.m02*b.m22, 


		a.m10*b.m00 + a.m11*b.m10 + a.m12*b.m20, 
		a.m10*b.m01 + a.m11*b.m11 + a.m12*b.m21, 
		a.m10*b.m02 + a.m11*b.m12 + a.m12*b.m22, 


		a.m20*b.m00 + a.m21*b.m10 + a.m22*b.m20, 
		a.m20*b.m01 + a.m21*b.m11 + a.m22*b.m21, 
		a.m20*b.m02 + a.m21*b.m12 + a.m22*b.m22, 

		MAT3,
		9*sizeof(GLfloat)
	};
}

static inline mat2_t m2_mul(mat2_t a, mat2_t b)
{
	return (mat2_t){

		a.m00*b.m00 + a.m01*b.m10, 
		a.m00*b.m01 + a.m01*b.m11, 

		a.m10*b.m00 + a.m11*b.m10, 
		a.m10*b.m01 + a.m11*b.m11, 

		MAT2,
		4*sizeof(GLfloat)
	};
}

static inline const_size_arrays m4_array(mat4_t a) 
{
	const_size_arrays ret;
	ret.type = a.type;
	ret.mat4[0]		= a.m00;
	ret.mat4[1]		= a.m01;
	ret.mat4[2]		= a.m02;
	ret.mat4[3]		= a.m03;

	ret.mat4[4]		= a.m10;
	ret.mat4[5]		= a.m11;
	ret.mat4[6]		= a.m12;
	ret.mat4[7]		= a.m13;

	ret.mat4[8]		= a.m20;
	ret.mat4[9]		= a.m21;
	ret.mat4[10]	= a.m22;
	ret.mat4[11]	= a.m23;
	
	ret.mat4[12]	= a.m30;
	ret.mat4[13]	= a.m31;
	ret.mat4[14]	= a.m32;
	ret.mat4[15]	= a.m33;
	return ret;
};

static inline const_size_arrays m3_array(mat3_t a) 
{
	const_size_arrays ret;
	ret.type = a.type;
	ret.mat3[0]		= a.m00;
	ret.mat3[1]		= a.m01;
	ret.mat3[2]		= a.m02;

	ret.mat3[3]		= a.m10;
	ret.mat3[4]		= a.m11;
	ret.mat3[5]		= a.m12;

	ret.mat3[6]		= a.m20;
	ret.mat3[7]		= a.m21;
	ret.mat3[8]		= a.m22;
	return ret;
};

static inline const_size_arrays m2_array(mat2_t a) 
{
	const_size_arrays ret;
	ret.type = a.type;
	ret.mat2[0]		= a.m00;
	ret.mat2[1]		= a.m01;

	ret.mat2[2]		= a.m10;
	ret.mat2[3]		= a.m11;
	return ret;
};

static inline mat4_t m4_translate(vec3_t a);
static inline mat4_t m4_lookAt(vec3_t eye, vec3_t center, vec3_t up);
static inline mat4_t m4_projection(GLfloat fov, GLfloat aspect, GLfloat zNear, GLfloat zFar);
static inline mat4_t m4_rotate(GLfloat angle, const vec3_t axis);
static inline mat4_t m4_scale(vec3_t a);

static inline mat4_t m4_lookAt(vec3_t eye, vec3_t center, vec3_t up)
{
	vec3_t F = v3_sub(center, eye);
	vec3_t f = v3_norm(F);
	vec3_t UP = v3_norm(up);
	vec3_t s = v3_cross(f, UP);
	vec3_t u = v3_cross(v3_norm(s), f);

	mat4_t ret = {
		s.x, s.y, s.z, 0,
		u.x, u.y, u.z, 0,
		-f.x, -f.y, -f.z, 0,
		0, 0, 0, 1.f
	};

	ret = m4_mul(mat4(1.0), ret);
	ret = m4_mul(ret, m4_translate(vec3(-eye.x, -eye.y, -eye.z)));
	return ret;
}

static inline mat4_t m4_projection(GLfloat fov, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
	return (mat4_t){
		1/(aspect*tanf(fov/2)), 0, 0, 0,
		0, 1/tanf(fov/2), 0, 0,
		0, 0, - (zFar + zNear) / (zFar - zNear), - 2 * zFar * zNear / (zFar - zNear),
		0, 0, -1.f, 0,
		MAT4,
		16*sizeof(GLfloat)
	};
}

static inline mat4_t m4_translate(vec3_t a)
{
	return (mat4_t){
		1, 0, 0, a.x,
		0, 1, 0, a.y,
		0, 0, 1, a.z,
		0, 0, 0, 1,
		MAT4,
		16*sizeof(GLfloat)
	};
}

static inline mat4_t m4_rotate(GLfloat angle, const vec3_t axis)
{
	GLfloat c = cosf(angle);
	GLfloat s = sinf(angle);

	return (mat4_t){
c + sqr(axis.x)*(1-c), axis.x*axis.y*(1-c) - axis.z*s, axis.x*axis.z*(1-c) + axis.y*s, 0,
axis.y*axis.x*(1-c) + axis.z*s, c + sqr(axis.y)*(1-c), axis.y*axis.z*(1-c) - axis.x*s, 0,
axis.z*axis.x*(1-c) - axis.y*s, axis.z*axis.y*(1-c) + axis.x*s, c + sqr(axis.z)*(1-c), 0,
		0, 0, 0, 1.f,
		MAT4,
		16*sizeof(GLfloat)
	};
}

static inline mat4_t m4_scale(vec3_t a)
{
	return (mat4_t){
		a.x, 0, 0, 0,
		0, a.y, 0, 0,
		0, 0, a.z, 0,
		0, 0, 0, 1.f,
		MAT4,
		16*sizeof(GLfloat)
	};
}

static inline mat4_t m4_transpose(mat4_t m)
{
	return (mat4_t)
	{
		m.m00, m.m10, m.m20, m.m30,
		m.m01, m.m11, m.m21, m.m31,
		m.m02, m.m12, m.m22, m.m32,
		m.m03, m.m13, m.m23, m.m33,
		MAT4,
		16*sizeof(GLfloat)
	};
	
}


#endif
