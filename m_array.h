#ifndef ARRAY_H
#define ARRAY_H
#include "m_utils.h"
#include <stdlib.h>

typedef struct array{
	float * element;
	size_t size;
	size_t len;
} array;

typedef struct arrayu{
	unsigned int * element;
	size_t size;
	size_t len;
} arrayu;

array Array(size_t elems){
	array ret;
	ret.element = (float*)calloc(elems, FSIZE);
	ret.size = elems * FSIZE;
	ret.len = elems;
	return ret;
}


#define ArrayUtil_delete( array ) \
	free(array.element); \
	array.element = NULL;\
	array.size = 0;

#endif
