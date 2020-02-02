#ifndef ARRAY_H
#define ARRAY_H
#include "m_utils.h"
#include <stdarg.h>
#include <stdlib.h>

typedef __UINT32_TYPE__ uint32_t;
typedef enum {
	FLOAT,
	INT,
	UINT,
	VOID
} TYPE;

typedef struct array{
	void * v;
	float * f;
	int * i;
	unsigned int * ui;
	size_t size;
	size_t len;
	TYPE type;
} array;


typedef struct ArrayUtil{
	array(*array)(TYPE type, size_t len);
	void(*copy)(array *, const void * src, size_t lenght);
	void(*init)(array *, ...);
	void(*del)(array *);
} ArrayUtil;

array ArrayUtil_Array(TYPE type, size_t len){
	array ret;
	if(type == FLOAT){
		ret.v = (void*)m_array(len, float);
		ret.size = len * FSIZE;
	}
	if(type == INT){
		ret.v = (void*)m_array(len, int);
		ret.size = len * ISIZE;
	}
	if(type == UINT){
		ret.v = (void*)m_array(len, unsigned int);
		ret.size = len * UISIZE;
	}

	ret.len = len;
	ret.f = (float*)ret.v;
	ret.i = (int*)ret.v;
	ret.ui = (unsigned int*)ret.v;
	ret.type = type;
	return ret;
}

void ArrayUtil_Del(array * arr){
	free(arr->v);
	arr->len = 0;
	arr->size = 0;
	arr->type = VOID;
}

void ArrayUtil_Copy(array * dest, const void * src, size_t length){
	unsigned int i;
	for(i = 0; i < length; i++){
		switch(dest->type){
			case FLOAT:
				{
					dest->f[i] = ((float*)src)[i];
				}
				break;
			case INT:
				{
					dest->i[i] = ((int*)src)[i];
				}
				break;
			case UINT:
				{
					dest->ui[i] = ((unsigned int*)src)[i];
				}
				break;
			default:
				break;
		}
	}
}

void ArrayUtil_Init(array * dest, ...){
	va_list args;
	va_start(args, dest);
	unsigned int i;
	if(dest->type == FLOAT){
		for(i = 0; i < dest->len; i++){
			dest->f[i] = va_arg( args, double );
		}
	}
	if(dest->type == INT){
		for(i = 0; i < dest->len; i++){
			dest->i[i] = va_arg( args, int );
		}
	}
	if(dest->type == UINT){
		for(i = 0; i < dest->len; i++){
			dest->ui[i] = va_arg( args, unsigned int );
		}
	}
	va_end(args);
}


ArrayUtil createArrayUtil(){
	ArrayUtil ret;
	ret.array = ArrayUtil_Array;
	ret.copy = ArrayUtil_Copy;
	ret.init = ArrayUtil_Init;
	ret.del = ArrayUtil_Del;
	return ret;
}

#endif
