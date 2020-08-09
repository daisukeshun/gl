#ifndef MATH3D_H
#define MATH3D_H
#include <math.h>
#include <malloc.h>
#include <GL/glew.h>


static inline GLfloat radians(GLfloat deg) {return deg * 0.0174533f;};
static inline GLfloat degrees(GLfloat rad) {return rad * 57.2958f;};

typedef struct mat4_t
{
	GLint size;
	GLfloat * raw;
} mat4_t;

typedef struct mat3_t
{
	GLint size;
	GLfloat * raw;
} mat3_t;

typedef struct mat2_t
{
	GLint size;
	GLfloat * raw;
} mat2_t;

typedef struct vec4_t {
	GLfloat x, y, z, w,
			a, b, c, d;
	GLfloat * raw;
} vec4_t;

typedef struct vec3_t {
	GLfloat x, y, z,
			a, b, c;
	GLfloat * raw;
} vec3_t;

typedef struct vec2_t {
	GLfloat x, y,
			a, b;
	GLfloat * raw;
} vec2_t;

static inline vec4_t vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) 
{ 
	vec4_t ret = {x, y, z, w, x, y, z, w, NULL};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
};

static inline vec4_t* svec4(vec4_t *v, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	v->raw[0] = v->x = v->a = x;
	v->raw[1] = v->y = v->b = y;
	v->raw[2] = v->z = v->c = z;
	v->raw[3] = v->w = v->d = w;
	return v;
}

static inline vec3_t* svec3(vec3_t *v, GLfloat x, GLfloat y, GLfloat z)
{
	v->raw[0] = v->x = v->a = x;
	v->raw[1] = v->y = v->b = y;
	v->raw[2] = v->z = v->c = z;
	return v;
}

static inline vec2_t* svec2(vec2_t *v, GLfloat x, GLfloat y)
{
	v->raw[0] = v->x = v->a = x;
	v->raw[1] = v->y = v->b = y;
	return v;
}

static inline vec3_t vec3(GLfloat x, GLfloat y, GLfloat z) 
{ 
	vec3_t ret = { x, y, z, x, y, z, NULL};
	ret.raw = (GLfloat*)calloc(3, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
};

static inline vec2_t vec2(GLfloat x, GLfloat y) 
{ 
	vec2_t ret = { x, y, x, y, NULL};
	ret.raw = (GLfloat*)calloc(3, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
};

static inline vec4_t v4_add(vec4_t a, vec4_t b)
{ 
	vec4_t ret = { 
		a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w,
		a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w,
		NULL
	};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
}

static inline vec4_t * sv4_add(vec4_t * s, vec4_t a, vec4_t b)
{ 
	return 
		svec4(s,
		a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
static inline vec4_t * sv4_adds(vec4_t * sv, vec4_t a, float s) 
{
	return 
		svec4(sv, 
		a.x + s,   a.y + s,   a.z + s,	a.w + s);
}

static inline vec4_t v4_adds(vec4_t a, float s) 
{ 
	vec4_t ret = { 
		a.x + s,   a.y + s,   a.z + s,	a.w + s,
		a.x + s,   a.y + s,   a.z + s,  a.w + s,
		NULL
	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
}

static inline vec4_t * sv4_sub(vec4_t * s, vec4_t a, vec4_t b)
{ 
	return 
		svec4(s,
		a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); 
}

static inline vec4_t v4_sub(vec4_t a, vec4_t b)
{ 
	vec4_t ret = { 
		a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w,
		a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w,
		NULL
	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
}
static inline vec4_t * sv4_subs(vec4_t * sv, vec4_t a, float s) 
{
	return svec4(sv, a.x - s, a.y - s, a.z - s,	a.w - s);
}

static inline vec4_t v4_subs(vec4_t a, float s) 
{ 
	vec4_t ret = { 
		a.x - s,   a.y - s,   a.z - s,	a.w - s,
		a.x - s,   a.y - s,   a.z - s,  a.w - s,
		NULL
	};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
} 
static inline vec4_t * sv4_mul(vec4_t * s, vec4_t a, vec4_t b)
{
	return 
		svec4(s,
		a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

static inline vec4_t v4_mul(vec4_t a, vec4_t b)
{ 
	vec4_t ret = { 
		a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w,
		a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w,
		NULL
   	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
}

static inline vec4_t * sv4_muls(vec4_t * sv, vec4_t a, float s) 
{
	return 
		svec4(sv,
		a.x * s,   a.y * s,   a.z * s,	a.w * s);
}

static inline vec4_t v4_muls(vec4_t a, float s) 
{ 
	vec4_t ret = { 
		a.x * s,   a.y * s,   a.z * s,	a.w * s,
		a.x * s,   a.y * s,   a.z * s,  a.w * s, 
		NULL
	};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
}

static inline vec4_t * sv4_div(vec4_t * s, vec4_t a, vec4_t b)
{
	return 
		svec4(s,
		a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

static inline vec4_t v4_div(vec4_t a, vec4_t b)
{ 
	vec4_t ret = { 
		a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w,
		a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w,
		NULL
   	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
}

static inline vec4_t * sv4_divs(vec4_t * sv, vec4_t a, float s)
{
	return 
		svec4(sv,
		a.x / s,   a.y / s,   a.z / s,	a.w / s);
}

static inline vec4_t v4_divs(vec4_t a, float s) 
{ 
	vec4_t ret = { 
		a.x / s,   a.y / s,   a.z / s,	a.w / s,
		a.x / s,   a.y / s,   a.z / s,  a.w / s, 
		NULL};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
}
static inline float  v4_length(vec4_t v) 
{ 
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);          
}

static inline float  v4_dot(vec4_t a, vec4_t b)
{ 
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

static inline vec4_t v4_norm(vec4_t v);
static inline vec4_t v4_proj(vec4_t v, vec4_t onto);
static inline vec4_t v4_cross(vec4_t a, vec4_t b);
static inline float  v4_angle_between(vec4_t a, vec4_t b);

static inline vec4_t * sv4_norm(vec4_t* v) {
	float len = v4_length(*v);
	
	if (len > 0)
	{
		return 
			svec4(v,
			v->x / len, v->y / len, v->z / len, v->w / len);
	}
	else 
	{
		return
			svec4(v,
			0, 0, 0, 1);
	}
}

static inline vec4_t v4_norm(vec4_t v) {
	float len = v4_length(v);
	if (len > 0)
	{
		vec4_t ret = {	
			v.x / len, v.y / len, v.z / len, v.w / len, 
			v.x / len, v.y / len, v.z / len, v.w / len, 
			NULL }; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
	}
	else 
	{
		vec4_t ret = { 
			0, 0, 0, 1, 
			0, 0, 0, 1, 
			NULL };
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
	}
}

static inline vec4_t v4_proj(vec4_t v, vec4_t onto) {
	 return v4_muls(onto, v4_dot(v, onto) / v4_dot(onto, onto));
}

static inline vec4_t v4_cross(vec4_t a, vec4_t b) {
	 vec4_t ret = {
				a.y * b.z - a.z * b.y,
			    a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x,
				1.0,
				a.y * b.z - a.z * b.y,
			    a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x,
				1.0,
				NULL
	 };
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	ret.raw[3] = ret.w;
	return ret;
}

static inline float v4_angle_between(vec4_t a, vec4_t b) {
	 return acosf( v4_dot(a, b) / (v4_length(a) * v4_length(b)) );
}

static inline vec3_t * sv3_add(vec3_t * s, vec3_t a, vec3_t b)
{ 
	return 
		svec3(s,
		a.x + b.x, a.y + b.y, a.z + b.z);
}
static inline vec3_t * sv3_adds(vec3_t * sv, vec3_t a, float s) 
{
	return 
		svec3(sv, 
		a.x + s,   a.y + s,   a.z + s);
}

static inline vec3_t v3_adds(vec3_t a, float s) 
{ 
	vec3_t ret = { 
		a.x + s,   a.y + s,   a.z + s,
		a.x + s,   a.y + s,   a.z + s,
		NULL
	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
}

static inline vec3_t * sv3_sub(vec3_t * s, vec3_t a, vec3_t b)
{ 
	return 
		svec3(s,
		a.x - b.x, a.y - b.y, a.z - b.z); 
}

static inline vec3_t v3_sub(vec3_t a, vec3_t b)
{ 
	vec3_t ret = { 
		a.x - b.x, a.y - b.y, a.z - b.z,
		a.x - b.x, a.y - b.y, a.z - b.z,
		NULL
	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
}
static inline vec3_t * sv3_subs(vec3_t * sv, vec3_t a, float s) 
{
	return svec3(sv, a.x - s, a.y - s, a.z - s);
}

static inline vec3_t v3_subs(vec3_t a, float s) 
{ 
	vec3_t ret = { 
		a.x - s,   a.y - s,   a.z - s,
		a.x - s,   a.y - s,   a.z - s,
		NULL
	};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
} 
static inline vec3_t * sv3_mul(vec3_t * s, vec3_t a, vec3_t b)
{
	return 
		svec3(s,
		a.x * b.x, a.y * b.y, a.z * b.z);
}

static inline vec3_t v3_mul(vec3_t a, vec3_t b)
{ 
	vec3_t ret = { 
		a.x * b.x, a.y * b.y, a.z * b.z,
		a.x * b.x, a.y * b.y, a.z * b.z,
		NULL
   	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
}

static inline vec3_t * sv3_muls(vec3_t * sv, vec3_t a, float s) 
{
	return 
		svec3(sv,
		a.x * s,   a.y * s,   a.z * s);
}

static inline vec3_t v3_muls(vec3_t a, float s) 
{ 
	vec3_t ret = { 
		a.x * s,   a.y * s,   a.z * s,
		a.x * s,   a.y * s,   a.z * s,
		NULL
	};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
}

static inline vec3_t * sv3_div(vec3_t * s, vec3_t a, vec3_t b)
{
	return 
		svec3(s,
		a.x / b.x, a.y / b.y, a.z / b.z);
}

static inline vec3_t v3_div(vec3_t a, vec3_t b)
{ 
	vec3_t ret = { 
		a.x / b.x, a.y / b.y, a.z / b.z,
		a.x / b.x, a.y / b.y, a.z / b.z,
		NULL
   	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
}

static inline vec3_t * sv3_divs(vec3_t * sv, vec3_t a, float s)
{
	return 
		svec3(sv,
		a.x / s,   a.y / s,   a.z / s);
}

static inline vec3_t v3_divs(vec3_t a, float s) 
{ 
	vec3_t ret = { 
		a.x / s,   a.y / s,   a.z / s,
		a.x / s,   a.y / s,   a.z / s,
		NULL};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
}
static inline float  v3_length(vec3_t v) 
{ 
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);          
}

static inline float  v3_dot(vec3_t a, vec3_t b)
{ 
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

static inline vec3_t v3_norm(vec3_t v);
static inline vec3_t v3_proj(vec3_t v, vec3_t onto);
static inline vec3_t v3_cross(vec3_t a, vec3_t b);
static inline float  v3_angle_between(vec3_t a, vec3_t b);

static inline vec3_t * sv3_norm(vec3_t* v) {
	float len = v3_length(*v);
	
	if (len > 0)
	{
		return 
			svec3(v,
			v->x / len, v->y / len, v->z / len);
	}
	else 
	{
		return
			svec3(v,
			0, 0, 0);
	}
}

static inline vec3_t v3_norm(vec3_t v) {
	float len = v3_length(v);
	if (len > 0)
	{
		vec3_t ret = {	
			v.x / len, v.y / len, v.z / len,
			v.x / len, v.y / len, v.z / len,
			NULL }; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
	}
	else 
	{
		vec3_t ret = { 
			0, 0, 0,
			0, 0, 0,
			NULL };
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
	}
}

static inline vec3_t v3_proj(vec3_t v, vec3_t onto) {
	 return v3_muls(onto, v3_dot(v, onto) / v3_dot(onto, onto));
}

static inline vec3_t v3_cross(vec3_t a, vec3_t b) {
	 vec3_t ret = {
				a.y * b.z - a.z * b.y,
			    a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x,
				a.y * b.z - a.z * b.y,
			    a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x,
				NULL
	 };
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	ret.raw[2] = ret.z;
	return ret;
}

static inline float v3_angle_between(vec3_t a, vec3_t b) {
	 return acosf( v3_dot(a, b) / (v3_length(a) * v3_length(b)) );
}

static inline vec2_t * sv2_add(vec2_t * s, vec2_t a, vec2_t b)
{ 
	return 
		svec2(s,
		a.x + b.x, a.y + b.y);
}
static inline vec2_t * sv2_adds(vec2_t * sv, vec2_t a, float s) 
{
	return 
		svec2(sv, 
		a.x + s, a.y + s);
}

static inline vec2_t v2_adds(vec2_t a, float s) 
{ 
	vec2_t ret = { 
		a.x + s,   a.y + s,
		a.x + s,   a.y + s,
		NULL
	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
}

static inline vec2_t * sv2_sub(vec2_t * s, vec2_t a, vec2_t b)
{ 
	return 
		svec2(s,
		a.x - b.x, a.y - b.y); 
}

static inline vec2_t v2_sub(vec2_t a, vec2_t b)
{ 
	vec2_t ret = { 
		a.x - b.x, a.y - b.y,
		a.x - b.x, a.y - b.y,
		NULL
	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
}
static inline vec2_t * sv2_subs(vec2_t * sv, vec2_t a, float s) 
{
	return svec2(sv, a.x - s, a.y - s);
}

static inline vec2_t v2_subs(vec2_t a, float s) 
{ 
	vec2_t ret = { 
		a.x - s,   a.y - s,
		a.x - s,   a.y - s,
		NULL
	};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
} 
static inline vec2_t * sv2_mul(vec2_t * s, vec2_t a, vec2_t b)
{
	return 
		svec2(s,
		a.x * b.x, a.y * b.y);
}

static inline vec2_t v2_mul(vec2_t a, vec2_t b)
{ 
	vec2_t ret = { 
		a.x * b.x, a.y * b.y,
		a.x * b.x, a.y * b.y,
		NULL
   	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
}

static inline vec2_t * sv2_muls(vec2_t * sv, vec2_t a, float s) 
{
	return 
		svec2(sv,
		a.x * s,   a.y * s);
}

static inline vec2_t v2_muls(vec2_t a, float s) 
{ 
	vec2_t ret = { 
		a.x * s,   a.y * s,
		a.x * s,   a.y * s,
		NULL
	};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
}

static inline vec2_t * sv2_div(vec2_t * s, vec2_t a, vec2_t b)
{
	return 
		svec2(s,
		a.x / b.x, a.y / b.y);
}

static inline vec2_t v2_div(vec2_t a, vec2_t b)
{ 
	vec2_t ret = { 
		a.x / b.x, a.y / b.y,
		a.x / b.x, a.y / b.y,
		NULL
   	}; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
}

static inline vec2_t * sv2_divs(vec2_t * sv, vec2_t a, float s)
{
	return 
		svec2(sv,
		a.x / s,   a.y / s);
}

static inline vec2_t v2_divs(vec2_t a, float s) 
{ 
	vec2_t ret = { 
		a.x / s,   a.y / s,
		a.x / s,   a.y / s,
		NULL};
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
}
static inline float  v2_length(vec2_t v) 
{ 
	return sqrtf(v.x*v.x + v.y*v.y);          
}

static inline float  v2_dot(vec2_t a, vec2_t b)
{ 
	return a.x*b.x + a.y*b.y;
}

static inline vec2_t v2_norm(vec2_t v);
static inline vec2_t v2_proj(vec2_t v, vec2_t onto);
static inline vec2_t v2_cross(vec2_t a, vec2_t b);
static inline float  v2_angle_between(vec2_t a, vec2_t b);

static inline vec2_t * sv2_norm(vec2_t* v) {
	float len = v2_length(*v);
	
	if (len > 0)
	{
		return 
			svec2(v,
			v->x / len, v->y / len);
	}
	else 
	{
		return
			svec2(v,
			0, 0);
	}
}

static inline vec2_t v2_norm(vec2_t v) {
	float len = v2_length(v);
	if (len > 0)
	{
		vec2_t ret = {	
			v.x / len, v.y / len,
			v.x / len, v.y / len,
			NULL }; 
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
	}
	else 
	{
		vec2_t ret = { 
			0, 0,
			0, 0,
			NULL };
	ret.raw = (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0] = ret.x;
	ret.raw[1] = ret.y;
	return ret;
	}
}

static inline vec2_t v2_proj(vec2_t v, vec2_t onto) {
	 return v2_muls(onto, v2_dot(v, onto) / v2_dot(onto, onto));
}

static inline float v2_angle_between(vec2_t a, vec2_t b) {
	 return acosf( v2_dot(a, b) / (v2_length(a) * v2_length(b)) );
}

static inline float v4_distance_between(vec4_t a, vec4_t b)
{
	return sqrtf(
			(a.x - b.x) * (a.x - b.x) +
			(a.y - b.y) * (a.y - b.y) +
			(a.z - b.z) * (a.z - b.z) +
			(a.w - b.w) * (a.w - b.w));
}

static inline float v3_distance_between(vec3_t a, vec3_t b)
{
	return sqrtf(
			(a.x - b.x) * (a.x - b.x) +
			(a.y - b.y) * (a.y - b.y) +
			(a.z - b.z) * (a.z - b.z));
}

static inline float v2_distance_between(vec2_t a, vec2_t b)
{
	return sqrtf(
			(a.x - b.x) * (a.x - b.x) +
			(a.y - b.y) * (a.y - b.y));
}


static inline mat4_t mat4(GLfloat s)
{
	mat4_t ret;
	ret.size	= sizeof(GLfloat) * 16;
	ret.raw		= (GLfloat*)calloc(16, sizeof(GLfloat));
	ret.raw[0]	= s;
	ret.raw[5]	= s;
	ret.raw[10]	= s;
	ret.raw[15]	= 1.f;
}

static inline mat4_t * smat4(mat4_t * dest, GLfloat s)
{
	dest->raw[0]	= s;
	dest->raw[5]	= s;
	dest->raw[10]	= s;
	dest->raw[15]	= 1.f;
	return dest;
}

static inline mat3_t mat3(GLfloat s)
{
	mat3_t ret;
	ret.size	= sizeof(GLfloat) * 9;
	ret.raw		= (GLfloat*)calloc(9, sizeof(GLfloat));
	ret.raw[0]	= s;
	ret.raw[4]	= s;
	ret.raw[8]	= s;
}

static inline mat3_t * smat3(mat3_t * dest, GLfloat s)
{
	dest->raw[0]	= s;
	dest->raw[4]	= s;
	dest->raw[8]	= s;
	return dest;
}

static inline mat2_t mat2(GLfloat s)
{
	mat3_t ret;
	ret.size	= sizeof(GLfloat) * 4;
	ret.raw		= (GLfloat*)calloc(4, sizeof(GLfloat));
	ret.raw[0]	= s;
	ret.raw[3]	= s;
}

static inline mat2_t * smat2(mat2_t * dest, GLfloat s)
{
	dest->raw[0]	= s;
	dest->raw[3]	= s;
	return dest;
}

static inline mat4_t m4_identity()
{
	return mat4(1.f);
}

static inline mat4_t * sm4_identity(mat4_t * m)
{
	return smat4(m, 1.f);
}

static inline mat3_t m3_identity()
{
	return mat3(1.f);
}

static inline mat3_t * sm3_identity(mat3_t * m)
{
	return smat3(m, 1.f);
}

static inline mat2_t m2_identity()
{
	return mat2(1.f);
}

static inline mat2_t * sm2_identity(mat2_t * m)
{
	return smat2(m, 1.f);
}



#endif
