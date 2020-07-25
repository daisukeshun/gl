#include "../math/vertex.h"
#include "../math/matrix.h"
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


typedef struct Object
{
	GLboolean loaded;
	GLuint vao, vbo, ebo, programID;
	GLfloat * rotation;
	GLfloat * position;
	GLchar * name;
	GLfloat * vrts;
	GLfloat * clrs;
	GLfloat * txtr;
	GLsizei v_size, c_size, t_size;
	struct Object * next;
	GLsizei index;
} Object;


typedef struct ShaderGroup
{
	GLchar * name;
	GLchar * vs_source;
	GLchar * fs_source;
	GLuint programID;
	GLsizei memberCount;
	Object * member;
} ShaderGroup;


void setName(GLchar ** dest, const GLchar * string);

ShaderGroup setShaderGroup(const GLchar * vssource, const GLchar * fssource, GLsizei count);
void deleteShaderGroup(ShaderGroup * group);

Object setObject(GLsizei vsize, GLsizei csize, GLsizei tsize);
void loadObject(Object * objct);
void deleteObject(Object * objct);

void print_objct(Object * objct);
