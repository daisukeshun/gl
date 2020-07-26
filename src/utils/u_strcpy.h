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

void setName(GLchar ** dest, const GLchar * string);
