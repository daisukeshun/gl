#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

char ShaderCreate(GLuint *id, GLenum shaderType, const char * source);
char ShaderProgramCreate(GLuint * id, GLuint *vshader, GLuint *fshader);

char setUniformMatrix(GLuint id, const GLchar * uniform, GLsizei count, GLboolean transpose, const GLfloat * value);

