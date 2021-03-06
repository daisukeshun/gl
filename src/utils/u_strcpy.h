#ifndef U_STRCPY_H
#define U_STRCPY_H
#include <string.h>
#include <malloc.h>
#include <GL/gl.h>
enum m_type
{
	FLOAT,
	DOUBLE,
	UINT,
	INT,
	SIZE,
	VERTEX,
	BYTE,
	UBYTE,
	MATRIX
};

void u_copyToNewString(GLchar ** dest, const GLchar * string);
#endif
